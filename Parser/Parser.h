/**
 class Parser 该类为语法分析主要入口程序
**/

#include <string>

class Parser
{
public:
	Parser();
	~Parser();
	
	// @function PushString 压入字符串
	// @param string s 字符串
	void PushString( std::string s);

	// @funciton PushWord 压入单词
	// @param sting w 词
	void PushWord( std::string  w);

	// @function PushNumber 压入数字
	// @param int iNum 整数
	void PushNumber( int iNum);

	// @function PushNumber 压入数字
	// @param double  dNum 双精度数字
	void PushNumber( double dNum);

	// @function PushPunct 压入标点
	// @param char c 一个标点字符
	void PushPunct( char c);

	// @function End 压入文件结束符
	void End();

	// @function Disabled 模块初始化状态
	// @return bool  true:初始化良好， false 等待初始化
	bool Disabled();

private:

	// ParserImp* imp;
};