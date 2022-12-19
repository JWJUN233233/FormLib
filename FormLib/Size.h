#pragma once
#include "pch.h"
namespace DG_CoreLib{
class DLL Size
{
	public:
		Size(int w, int h);
		Size();
		int GetW();
		int GetH();
		void SetSize(int w, int h);
	//private:
		int _w;
		int _h;
};
}
