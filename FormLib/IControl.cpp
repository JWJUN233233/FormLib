#include "IControl.h"
int NextControlid = 100;
namespace FormLib {
	int IControl::getOwner()
	{
		return owner;
	}
	void IControl::setOwner(int Owner)
	{
		owner = Owner;
	}
}