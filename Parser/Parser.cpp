#include "Parser.h"

Parser::Parser()
// :imp(NULL)
{
	//todo： 根据具体平台和优化参数 选择不同的实现器
	//
}

Parser::~Parser()
{

}

// @function PushString 压入字符串
// @param string s 字符串
void Parser::PushString( std::string s)
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @funciton PushWord 压入单词
// @param sting w 词
void Parser::PushWord( std::string  w)
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @function PushNumber 压入数字
// @param int iNum 整数
void Parser::PushNumber( int iNum)
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @function PushNumber 压入数字
// @param double  dNum 双精度数字
void Parser::PushNumber( double dNum)
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @function PushPunct 压入标点
// @param char c 一个标点字符
void Parser::PushPunct( char c)
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @function End 压入文件结束符
void Parser::End()
{
	// if (this->imp != NULL)
	// {
		// todo something
	// }
}

// @function Disabled 模块初始化状态
// @return bool  true:初始化良好， false 等待初始化
bool Disabled()
{
	return false;
}
