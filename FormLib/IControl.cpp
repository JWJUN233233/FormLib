#include "IControl.h"
int NextControlid = 100;
namespace FormLib {
	Form* IControl::getOwner()
	{
		return owner;
	};
	void IControl::setOwner(Form* Owner)
	{
		owner = Owner;
	};
	void IEvent::setCancel(bool cancel)
	{
		Cancel = cancel;
	};
	bool IEvent::isCancel()
	{
		return Cancel;
	};
	Point ButtonClickEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonClickEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	Point ButtonClickEvent::getCuosorONButton()
	{
		return CursorONButton;
	}
	IControl* ButtonClickEvent::getOwner()
	{
		return owner;
	}
	Point CursorEnteringEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point CursorEnteringEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	Point CursorEnteringEvent::getCuosorONButton()
	{
		return CursorONButton;
	}
	IControl* CursorEnteringEvent::getOwner()
	{
		return owner;
	}
	void IControl::setPoint(Point point)
	{
		_point = point;
	}
	void IControl::setSize(Size size)
	{
		_size = size;
	}
	Point IControl::getPoint()
	{
		return _point;
	}
	Size IControl::getSize()
	{
		return _size;
	}
	Point CursorLeavingEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point CursorLeavingEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	IControl* CursorLeavingEvent::getOwner()
	{
		return owner;
	}
	Point ButtonDisableEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonDisableEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	IControl* ButtonDisableEvent::getOwner()
	{
		return owner;
	}
	Point ButtonEnableEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonEnableEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	IControl* ButtonEnableEvent::getOwner()
	{
		return owner;
	}
	Point ButtonDoubleClickEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonDoubleClickEvent::getCuosorONForm()
	{
		return CursorONForm;
	}
	Point ButtonDoubleClickEvent::getCuosorONButton()
	{
		return CursorONButton;
	}
	IControl* ButtonDoubleClickEvent::getOwner()
	{
		return owner;
	}
}