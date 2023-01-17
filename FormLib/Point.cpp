#include "Point.h"
using namespace DG_CoreLib;
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

Point::Point(){
	_x = 0;
	_y = 0;
}

Point::~Point()
{
	
}

int Point::GetX()
{
	return _x;
}

int Point::GetY()
{
	return _y;
}

void Point::SetPoint(Point point)
{
	_x = point.GetX();
	_y = point.GetY();
}

void Point::SetPoint(int x,int y)
{
	_x = x;
	_y = y;
}

void Point::PrintPoint()
{
	
}
