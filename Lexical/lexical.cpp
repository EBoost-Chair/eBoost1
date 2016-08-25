/*
 * 词法分析
 * Email: jazzzzaj@hotmail.co.jp
 */

#include "lexical.h"
#include <ctype.h>
#include <string>
#include <math.h>

char Lexical::escape(char c) {
	switch (c) {
	case 'a':
		return '\a';
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	case '\\':
		return '\\';
	case '\'':
		return '\'';
	case '"':
		return '"';
	case '?':
		return '?';
	default:
		state = error;
		throw ErrorSyntaxInStringEscape();
	}
	return c;
}

void Lexical::Push(char c) {
	if (Disabled()) return;
	if (state == end) {
		state = error;
		throw Error();
	}
	col++;
	if (delay) {
		delay = 0;
		col--;
	}
	switch (state) {
	case normal:
		switch (c) {
		case '\n':
			line++;
			col = 0;
			break;
		case ' ':
		case '\t':
			break;
		case '\"':
			str = "";
			state = in_string;
			break;
		case '#':
			state = in_linenotes;
			break;
		case '.':
			state = point;
			break;
		case '=':
			Parser::PushPunct('=');
			break;
		case ';':
			Parser::PushPunct(';');
			break;
		case '*':
			Parser::PushPunct('*');
			break;
		case '/':
			Parser::PushPunct('/');
			break;
		case ',':
			Parser::PushPunct(',');
			break;
		case '{':
			Parser::PushPunct('{');
			break;
		case '}':
			Parser::PushPunct('}');
			break;
		case '(':
			Parser::PushPunct('(');
			break;
		case ')':
			Parser::PushPunct(')');
			break;
		case '[':
			Parser::PushPunct('[');
			break;
		case ']':
			Parser::PushPunct(']');
			break;
		case '0':
			state = in_zero;
			break;
		default:
			if (c >= '1' && c <= '9') {
				num = c - '0';
				state = dec;
			}
			else if (isalpha(c) || c == '_') {
				str = c;
				state = word;
			}
			else {
				state = error;
				throw ErrorSyntaxUnknownChar();
			}
		}
		break;
	case in_linenotes:
		switch (c) {
		case '\n':
			line++;
			col = 0;
			state = normal;
			break;
		default:;
		}
		break;
	case in_string:
		switch (c) {
		case '"':
			Parser::PushString(str);
			state = normal;
			break;
		case '\\':
			state = in_string_escape;
			break;
		default:
			if (isgraph(c) || c == ' ') str += c;
		}
		break;
	case in_string_escape:
		switch (c) {
		case 'x':
			state = in_string_escape_x;
			break;
		default:
			if (isdigit(c)) {
				num = c - '0';
				state = in_string_escape_o;
			}
			else {
				str += escape(c);
				state = in_string;
			}
		}
		break;
	case in_string_escape_x:
		if (isdigit(c)) num = c - '0';
		else if (c >= 'A' && c <= 'F') num = c - 'A' + 10;
		else if (c >= 'a' && c <= 'f') num = c - 'a' + 10;
		else {
			state = error;
			throw ErrorSyntaxInStringEscape();
		}
		state = in_string_escape_x_h;
		break;
	case in_string_escape_x_h:
		if (isdigit(c)) num = num * 16 + c - '0';
		else if (c >= 'A' && c <= 'F') num = num * 16 + c - 'A' + 10;
		else if (c >= 'a' && c <= 'f') num = num * 16 + c - 'a' + 10;
		else delay = c;
		if (isascii(num)) str += num;
		else {
			state = error;
			throw ErrorSyntaxInStringEscape();
		}
		state = in_string;
		break;
	case in_string_escape_o:
		if (c >= '0' && c <= '7') {
			num = num * 8 + c - '0';
			state = in_string_escape_o_o;
		}
		else {
			delay = c;
			state = in_string;
		}
		if (isascii(num)) str += num;
		else {
			state = error;
			throw ErrorSyntaxInStringEscape();
		}
		break;
	case in_string_escape_o_o:
		if (c >= '0' && c <= '7') num = num * 8 + c - '0';
		else delay = c;
		if (isascii(num)) str += num;
		else {
			state = error;
			throw ErrorSyntaxInStringEscape();
		}
		state = in_string;
		break;
	case in_zero:
		switch (c) {
		case 'x':
		case 'X':
			state = hex;
			break;
		case 'E':
		case 'e':
			fnum = .0;
			num = 0;
			state = dec_point_e;
			break;
		case '.':
			fnum = .0;
			dfnum = 1.0;
			state = dec_point;
			break;
		default:
			if (isdigit(c)) {
				num = c - '0';
				state = oct;
			}
			else {
				state = error;
				throw ErrorSyntaxDigit();
			}
		}
		break;
	case point:
		if (isdigit(c)) {
			fnum = .0;
			dfnum = 1.0;
			state = dec_point;
			delay = c;
		}
		else {
			Parser::PushPunct('.');
			state = normal;
			delay = c;
		}
		break;
	case word:
		if (isalnum(c) || c == '_') str += c;
		else {
			Parser::PushWord(str);
			state = normal;
			delay = c;
		}
		break;
	case hex:
		if (isalnum(c) || c == '_')
			if (isdigit(c)) num = num * 16 + c - '0';
			else if (c >= 'A' && c <= 'F') num = num * 16 + c - 'A' + 10;
			else if (c >= 'a' && c <= 'f') num = num * 16 + c - 'a' + 10;
			else {
				state = error;
				throw ErrorSyntaxDigitHex();
			}
		else {
			Parser::PushNumber(num);
			state = normal;
			delay = c;
		}
		break;
	case oct:
		if (isalnum(c) || c == '_')
			if (c >= '0' && c <= '7') num = num * 8 + c - '0';
			else {
				state = error;
				throw ErrorSyntaxDigitOct();
			}
		else {
			Parser::PushNumber(num);
			state = normal;
			delay = c;
		}
		break;
	case dec:
		if (isalnum(c) || c == '_' || c == '.')
			if (isdigit(c)) num = num * 10 + c - '0';
			else if (c == '.') {
				fnum = num;
				dfnum = 1.0;
				state = dec_point;
			}
			else if (c == 'e' || c == 'E') {
				fnum = num;
				num = 0;
				state = dec_point_e;
			}
			else {
				state = error;
				throw ErrorSyntaxDigitDec();
			}
		else {
			Parser::PushNumber(num);
			state = normal;
			delay = c;
		}
		break;
	case dec_point:
		if (isalnum(c) || c == '_')
			if (isdigit(c)) 
				fnum += (c - '0') * (dfnum /= 10.0);
			else if (c == 'e' || c == 'E')
				state = dec_point_e;
			else {
				state = error;
				throw ErrorSyntaxDightFloat();
			}
		else {
			Parser::PushNumber(fnum);
			state = normal;
			delay = c;
		}
		break;
	case dec_point_e:
		num = 1;
		switch (c) {
		case '+':
			break;
		case '-':
			num = -1;
			break;
		default:
			delay = c;
			break;
		}
		state = dec_point_e_sign;
		break;
	case dec_point_e_sign:
		if (isalnum(c) || c == '_')
			if (c >= '0' && c <= '9') {
				num *= c - '0';
				state = dec_point_e_sign_digit;
			}
			else {
				state = error;
				throw ErrorSyntaxDightFloat();
			}
		else {
			state = error;
			throw ErrorSyntaxDightFloat();
		}
		break;
	case dec_point_e_sign_digit:
		if (isalnum(c) || c == '_')
			if (c >= '0' && c <= '9')
				num = num * 10 + c - '0';
			else {
				state = error;
				throw ErrorSyntaxDightFloat();
			}
		else {
			fnum = fnum * pow(10.0, num);
			Parser::PushNumber(fnum);
			state = normal;
			delay = c;
		}
		break;
	default:
		state = error;
		throw Error();
	}
	if (delay) Push(delay);
}

void Lexical::End() {
	if (Disabled()) return;
	switch (state) {
	case normal:
	case in_linenotes:
	case in_zero:
	case point:
	case word:
	case hex:
	case oct:
	case dec:
	case dec_point:
	case dec_point_e_sign_digit:
		state = end;
		Parser::End();
		break;
	default:
		state = error;
		throw ErrorSyntaxIncomplateness();
	}
}

unsigned int Lexical::Line() {
	return line + 1;
}

unsigned int Lexical::Col() {
	return col + 1;
}

bool Lexical::Disabled() {
	return Parser::Disabled() || state == error;
}
