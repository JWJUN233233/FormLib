#include "IColorfulOut.h"
#pragma warning(disable : 4996)
#pragma once
IColorfulOut::IColorfulOut(WORD Color)
{
	color = Color;
}
IColorfulOut::IColorfulOut()
{
	color = 7;
}
IColorfulOut IColorfulOut::operator<<(const char* p)
{
	Write((char*)p, color);
	return *this;
}

IColorfulOut IColorfulOut::operator<<(const char p)
{
	char buffer[] = { p };
	Write(buffer, color);
	return *this;
}

IColorfulOut IColorfulOut::operator<<(const int p)
{
	char buffer[32];
	_ltoa(p, buffer, 10);
	Write(buffer, color);
	return *this;
}

IColorfulOut IColorfulOut::operator<<(const short p)
{
	char buffer[128];
	_ltoa(p, buffer, 10);
	Write(buffer, color);
	return IColorfulOut();
}

IColorfulOut IColorfulOut::operator<<(const float p)
{
	std::string buffer = std::to_string(p);
	Write((char*) buffer.c_str(), color);
	return IColorfulOut();
}

IColorfulOut IColorfulOut::operator<<(const double p)
{
	std::string buffer = std::to_string(p);
	Write((char*)buffer.c_str(), color);
	return IColorfulOut();
}

IColorfulOut IColorfulOut::operator<<(const long double p)
{
	std::string buffer = std::to_string(p);
	Write((char*)buffer.c_str(), color);
	return IColorfulOut();
}

IColorfulOut IColorfulOut::operator<<(const bool p)
{
	if (p) {
		Write((char*)"true", color);
	}
	else {
		Write((char*)"false", color);
	}
	return IColorfulOut();
}

IColorfulOut IColorfulOut::operator<<(const long long p)
{
	char buffer[] = "";
	_i64toa(p, buffer, 10);
	Write(buffer, color);
	return *this;
}

IColorfulOut IColorfulOut::operator<<(const wchar_t* p)
{
	Write((wchar_t*)p, color);
	return *this;
}

IColorfulOut IColorfulOut::operator<<(const wchar_t p)
{
	Write((wchar_t*)p, color);
	return *this;
}

IColorfulOut RedOut(FOREGROUND_RED | FOREGROUND_INTENSITY);
IColorfulOut GreenOut(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
IColorfulOut BlueOut(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
IColorfulOut YellowOut(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
IColorfulOut PurpleOut(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
IColorfulOut CyanOut(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
IColorfulOut GrayOut(FOREGROUND_INTENSITY);
IColorfulOut WhiteOut(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
IColorfulOut HighWhiteOut(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
IColorfulOut BlackOut(0);
const char endl[] = "\n";