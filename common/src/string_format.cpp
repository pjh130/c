#include "string_format.h"

StringFormat::StringFormat()
{

}

StringFormat::~StringFormat()
{

}

char* StringFormat::WcharToChar(const wchar_t* wp)
{
    int len= WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),NULL,0,NULL,NULL);
    char *pChar=new char[len+1];
    WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),pChar,len,NULL,NULL);
    pChar[len]='\0';
    return pChar;
}

char* StringFormat::StringToChar(const string& s)
{
    return const_cast<char*>(s.c_str());
}

char* StringFormat::WstringToChar(const wstring& ws)
{
    const wchar_t* wp=ws.c_str();
    return WcharToChar(wp);
}

wchar_t* StringFormat::CharToWchar(const char* c)
{
    int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0);
    wchar_t *pWwchar=new wchar_t[len+1];
    MultiByteToWideChar(CP_ACP,0,c,strlen(c),pWwchar,len);
    pWwchar[len]='\0';
    return pWwchar;
}

wchar_t* StringFormat::WstringToWchar(const wstring& ws)
{
    return const_cast<wchar_t*>(ws.c_str());
}

wchar_t* StringFormat::StringToWchar(const string& s)
{
    const char* p=s.c_str();
    return CharToWchar(p);
}

wstring StringFormat::StringToWstring(const string& s)
{
    wstring ws;
    wchar_t* wp=StringToWchar(s);
    ws.append(wp);
    return ws;
}

string StringFormat::WstringToString(const wstring& ws)
{
    string s;
    char* p=WstringToChar(ws);
    s.append(p);
    return s;
}
