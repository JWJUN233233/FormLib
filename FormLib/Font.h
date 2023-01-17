#pragma once
#include "pch.h"
#include <Windows.h>
#include<set>
namespace DG_CoreLib {
	const int STOP_FIND = 0;
	const int CONTINUE_FIND = 1;
	std::set<Astring>* buffer;
	int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX* lpelfe, NEWTEXTMETRICEX* lpntme, int FontType, LPARAM lParam)
	{
		if (NULL == lpelfe)
		{
			return STOP_FIND;        // 返回0停止遍历
		}
		buffer->insert(lpelfe->elfFullName);  // 将遍历中得到的字体存入容器保存
		return CONTINUE_FIND;        // 返回1 代表继续进行下一轮遍历
	}
	class Font
	{
	public:
		Font(int Height = 20,
			int Width = NULL,
			int Escapement = NULL,
			int Weight = NULL,
			int Orientation = NULL,
			bool IsItalic = false,
			bool IsUnderLine = false,
			bool IsStrikeOut = false,
			DWORD CharSet = DEFAULT_CHARSET,
			DWORD OutputPrecision = OUT_DEFAULT_PRECIS,
			DWORD ClipPrecision = CLIP_DEFAULT_PRECIS,
			DWORD Quality = DEFAULT_QUALITY,
			DWORD PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE,
			Achar* FontName = (Achar*)_T("微软雅黑")
			) {
			hFont = CreateFont(Height, Width, Escapement, Orientation, Weight, IsItalic, IsUnderLine, IsStrikeOut, CharSet, OutputPrecision, ClipPrecision, Quality, PitchAndFamily, FontName);
		}
		~Font() {
			DeleteObject(hFont);
		}
		HFONT getHFONT() {
			return hFont;
		}
		static std::set<Astring>* getFonts() {
			HDC hdc = GetDC(NULL);
			buffer = new std::set<Astring>();
			LOGFONT logFont = { 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"" };
			::EnumFontFamiliesEx(hdc, &logFont, (FONTENUMPROC)EnumFontFamiliesExProc, 0, 0);
			::ReleaseDC(NULL, hdc);
			return buffer;
		}
	private:
		HFONT hFont;
	};
}
