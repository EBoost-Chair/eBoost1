/*
 * eboost
 * Email: jazzzzaj@hotmail.co.jp
 */

#ifndef EBOOST_H

#define EBOOST_H

#include "..\Exception\exception.h"
#include "..\Lexical\lexical.h"

class Eboost : private Lexical {
public:
	void Push(char) throw();
	void End() throw();
};

#endif