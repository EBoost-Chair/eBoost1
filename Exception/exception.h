/*
 * 异常类的临时处理
 * Email: jazzzzaj@hotmail.co.jp
 */

#ifndef EXCEPTION_H

#define EXCEPTION_H

// 错误类异常

class Error {};
class ErrorSyntax : Error {};
class ErrorSyntaxUnknownChar : ErrorSyntax {};
class ErrorSyntaxIncomplateness : ErrorSyntax {};
class ErrorSyntaxInString : ErrorSyntax {};
class ErrorSyntaxInStringEscape : ErrorSyntaxInString {};
class ErrorSyntaxDigit : ErrorSyntax {};
class ErrorSyntaxDigitHex : ErrorSyntaxDigit {};
class ErrorSyntaxDigitOct : ErrorSyntaxDigit {};
class ErrorSyntaxDigitDec : ErrorSyntaxDigit {};
class ErrorSyntaxDightFloat : ErrorSyntaxDigit {};

// 警告类异常

class Warning {};

#endif