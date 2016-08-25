/*
 * 词法分析
 * Email: jazzzzaj@hotmail.co.jp
 */

#ifndef LEXICAL_H

#define LEXICAL_H

#include "..\Exception\exception.h"
#include "..\Parser\Parser.h"

class Lexical : private Parser {
	char escape(char) throw(Error);
	enum {
		normal,
		in_linenotes,
		in_string,
		in_string_escape,
		in_string_escape_x,
		in_string_escape_x_h,
		in_string_escape_o,
		in_string_escape_o_o,
		in_zero,
		point,
		word,
		hex,
		oct,
		dec,
		dec_point,
		dec_point_e,
		dec_point_e_sign,
		dec_point_e_sign_digit,
		error,
		end,
	} state = normal;
	char delay = 0;
	int num = 0;
	double fnum = .0, dfnum = .0;
	std::string str;
	unsigned int line = 0, col = 0;
public:
	virtual void Push(char c) throw(Error);
	virtual void End() throw(Error);
	virtual unsigned int Line();
	virtual unsigned int Col();
	virtual bool Disabled();
};


#endif

