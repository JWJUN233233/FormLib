#include "Size.h"
using namespace DG_CoreLib;
Size::Size(int w, int h)
{
	_w = w;
	_h = h;
}

Size::Size(){
	_w = 0;
	_h = 0;
}

int Size::GetW(){
	return _w;
}

int Size::GetH(){
	return _h;
}

void Size::SetSize(int w, int h){
	_w = w;
	_h = h;
}
