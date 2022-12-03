#include "utils.h"
void utf8ToGbk(char utf8String[], char gbkString[])
{
    wchar_t* unicodeStr = NULL;
    size_t nRetLen = 0;
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, NULL, 0);
    //������Ŀ��ַ�����С
    unicodeStr = (wchar_t*)malloc(nRetLen * sizeof(wchar_t));
    nRetLen = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, unicodeStr, nRetLen);
    //��utf-8����ת����unicode����
    if (unicodeStr == NULL) {
        return;
    }
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, NULL, 0, NULL, 0);
    //��ת�������ֽ���
    nRetLen = WideCharToMultiByte(CP_ACP, 0, unicodeStr, -1, gbkString, nRetLen, NULL, 0);
    //unicode����ת����gbk����
    free(unicodeStr);
}
int Char2Wchar(wchar_t* wcharStr, const char* charStr) {
    size_t len = MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), wcharStr, len);
    wcharStr[len] = '\0';
    return len;
}
LPCWSTR toWchar_t(const char str[]) {
    wchar_t* tmp = new wchar_t[1024];
    wchar_t** w_charStr = &tmp;
    Char2Wchar(*w_charStr, str);
    return *w_charStr;
}