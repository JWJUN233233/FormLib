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
	Point ButtonClickEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonClickEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	Point ButtonClickEvent::getCursorONButton()
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
	Point CursorEnteringEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	Point CursorEnteringEvent::getCursorONButton()
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
	Point CursorLeavingEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	IControl* CursorLeavingEvent::getOwner()
	{
		return owner;
	}
	Point DisableEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point DisableEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	IControl* DisableEvent::getOwner()
	{
		return owner;
	}
	Point EnableEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point EnableEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	IControl* EnableEvent::getOwner()
	{
		return owner;
	}
	Point ButtonDoubleClickEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point ButtonDoubleClickEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	Point ButtonDoubleClickEvent::getCursorONButton()
	{
		return CursorONButton;
	}
	IControl* ButtonDoubleClickEvent::getOwner()
	{
		return owner;
	}
	int MenuClickEvent::getId()
	{
		return id;
	}
	IMenu* MenuClickEvent::getOwner()
	{
		return owner;
	}
	MenuItem* MenuClickEvent::getNode()
	{
		return owner->getNode(id);
	}
	Point CheckBoxClickEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point CheckBoxClickEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	Point CheckBoxClickEvent::getCursorONCheckBox()
	{
		return CursorONCheckBox;
	}
	IControl* CheckBoxClickEvent::getOwner()
	{
		return owner;
	}
	Point FormMoveEvent::getCursorPoint()
	{
		return CursorPoint;
	}
	Point FormMoveEvent::getCursorONForm()
	{
		return CursorONForm;
	}
	Point FormMoveEvent::getNewFormPoint()
	{
		return NewFormPoint;
	}
	Size FormMoveEvent::getNewFormSize()
	{
		return NewFormSize;
	}
	Form* FormMoveEvent::getForm()
	{
		return form;
	}
	void ICancelable::setCancel(bool cancel)
	{
		Cancel = cancel;
	}
	bool ICancelable::isCancel()
	{
		return Cancel;
	}
	void* ShowingEvent::getOwner()
	{
		return owner;
	}
	void* HidingEvent::getOwner()
	{
		return owner;
	}
}