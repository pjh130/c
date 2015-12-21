#ifndef STRINGFORMAT_H
#define STRINGFORMAT_H

/*create by panpan 20151221*/

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

//字符类型        wchar_t     char
//获取字符长度    wcslen()    strlen()
//连接两个字符串  wcscat()    strcat()
//复制字符串      wcscpy()    strcpy()
//比较两个字符串  wcscmp()    strcmp()

class StringFormat
{
public:
    StringFormat();
    ~StringFormat();

public:
    static char* WcharToChar(const wchar_t* wp);
    static char* StringToChar(const string& s);
    static char* WstringToChar(const wstring& ws);
    static wchar_t* CharToWchar(const char* c);
    static wchar_t* WstringToWchar(const wstring& ws);
    static wchar_t* StringToWchar(const string& s);
    static wstring StringToWstring(const string& s);
    static string WstringToString(const wstring& ws);
};

#endif // STRINGFORMAT_H
