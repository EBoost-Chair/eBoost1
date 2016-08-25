/*
 * eboost
 * Email: jazzzzaj@hotmail.co.jp
 */

#include "eboost.h"
#include <iostream>

void Eboost::Push(char c) {
	using namespace std;
	auto head = [&] {
		cout << "[错误]在" << Line() << "行" << Col() << "列: ";
	};
	try {
		Lexical::Push(c);
	}
	catch (Error) {
		head();
		cout << "未知错误" << endl;
	}
	catch (ErrorSyntax) {
		head();
		cout << "语法错误" << endl;
	}
	catch (ErrorSyntaxUnknownChar) {
		head();
		cout << "未知字符" << endl;
	}
	catch (ErrorSyntaxIncomplateness) {
		head();
		cout << "不完整" << endl;
	}
	catch (ErrorSyntaxInString) {
		head();
		cout << "字符串" << endl;
	}
	catch (ErrorSyntaxInStringEscape) {
		head();
		cout << "字符串的转义字符" << endl;
	}
	catch (ErrorSyntaxDigit) {
		head();
		cout << "数字" << endl;
	}
	catch (ErrorSyntaxDigitHex) {
		head();
		cout << "十六进制数字" << endl;
	}
	catch (ErrorSyntaxDigitOct) {
		head();
		cout << "八进制数字" << endl;
	}
	catch (ErrorSyntaxDigitDec) {
		head();
		cout << "十进制数字" << endl;
	}
	catch (ErrorSyntaxDightFloat) {
		head();
		cout << "浮点数" << endl;
	}
}

void Eboost::End() throw() {
	using namespace std;
	auto head = [&] {
		cout << "[错误]在" << Line() << "行" << Col() << "列: ";
	};
	try {
		Lexical::End();
	}
	catch (Error) {
		head();
		cout << "未知错误" << endl;
	}
	catch (ErrorSyntax) {
		head();
		cout << "语法错误" << endl;
	}
	catch (ErrorSyntaxIncomplateness) {
		head();
		cout << "不完整" << endl;
	}
}
