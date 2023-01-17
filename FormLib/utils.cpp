#include "utils.h"

void utf8ToGbk(char utf8String[], char gbkString[])
{
    wchar_t* unicodeStr = NULL;
    size_t nRetLen = 0;
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, NULL, 0);
    //求需求的宽字符数大小
    unicodeStr = (wchar_t*)malloc(nRetLen * sizeof(wchar_t));
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, unicodeStr, nRetLen);
    //将utf-8编码转换成unicode编码
    if (unicodeStr == NULL) {
        return;
    }
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, NULL, 0, NULL, 0);
    //求转换所需字节数
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, gbkString, nRetLen, NULL, 0);
    //unicode编码转换成gbk编码
    free(unicodeStr);
}
void Char2Wchar(wchar_t* wcharStr, const char* charStr) {
    size_t len = MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), wcharStr, len);
    wcharStr[len] = '\0';
}