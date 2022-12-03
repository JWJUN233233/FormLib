#include "utils.h"
#include <stdio.h>
#pragma warning(disable : 4996)
void utf8ToGbk(char* utf8String, char* gbkString)
{
    wchar_t* unicodeStr = NULL;
    int nRetLen = 0;
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, NULL, 0);
    //������Ŀ��ַ�����С
    unicodeStr = (wchar_t*)malloc(nRetLen * sizeof(wchar_t));
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, unicodeStr, nRetLen);
    //��utf-8����ת����unicode����
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, NULL, 0, NULL, 0);
    //��ת�������ֽ���
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, gbkString, nRetLen, NULL, 0);
    //unicode����ת����gbk����
    free(unicodeStr);
}
void Char2Wchar(wchar_t* wcharStr, char* charStr) {
    size_t len = MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), wcharStr, len);
    wcharStr[len] = '\0';
}
void Wchar2Char(wchar_t* wcharStr, char* charStr) {
    sprintf(charStr, "%ws", wcharStr);
}