#ifndef SIZE_H
#define SIZE_H
namespace DG_CoreLib{
class Size
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
#endif
