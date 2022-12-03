#ifndef ICOLOR_H
#define ICOLOR_H
#include <Windows.h>
#include "Logger.h"
#include <sstream>
class IColorfulOut
{
public:
	WORD color;
	IColorfulOut(WORD color);
	IColorfulOut();
	IColorfulOut operator<<(const char* p);
	IColorfulOut operator<<(const char p);
	IColorfulOut operator<<(const int p);
	IColorfulOut operator<<(const short p);
	IColorfulOut operator<<(const float p);
	IColorfulOut operator<<(const double p);
	IColorfulOut operator<<(const long double p);
	IColorfulOut operator<<(const bool p);
	IColorfulOut operator<<(const long long p);
	IColorfulOut operator<<(const wchar_t* p);
	IColorfulOut operator<<(const wchar_t p);
};
extern IColorfulOut RedOut;
extern IColorfulOut GreenOut;
extern IColorfulOut BlueOut;
extern IColorfulOut YellowOut;
extern IColorfulOut PurpleOut;
extern IColorfulOut CyanOut;
extern IColorfulOut GrayOut;
extern IColorfulOut WhiteOut;
extern IColorfulOut HighWhiteOut;
extern IColorfulOut BlackOut;
extern const char endl[];
#endif