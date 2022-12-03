#ifndef POINT_H
#define POINT_H
namespace DG_CoreLib{
class Point
{
	public:
		Point(int x, int y);
		Point();
		~Point();
		int GetX();
		int GetY();
		void SetPoint(Point point);
		void SetPoint(int x,int y);
		void PrintPoint();
	//private:
		int _x;
		int _y;
};
}
#endif
