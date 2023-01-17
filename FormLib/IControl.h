#pragma once
#pragma warning(suppress : 4996)
#include "pch.h"
#include "Point.h"
#include "Size.h"
#include <Windows.h>
#include <string>
using namespace DG_CoreLib;
extern int NextControlid;
namespace FormLib {
	class Form;
	class IEvent;
	class ButtonClickEvent;
	class ButtonDoubleClickEvent;
	class CursorEnteringEvent;
	class CursorLeavingEvent;
	class MenuClickEvent;
	class CheckBoxClickEvent;
	class DisableEvent;
	class EnableEvent;
	class FormMoveEvent;
	class ShowingEvent;
	class HidingEvent;
	typedef void (*EventHandler)(IEvent*);
	typedef void (*ButtonClickEventHandler)(ButtonClickEvent*);
	typedef void (*ButtonDoubleClickEventHandler)(ButtonDoubleClickEvent*);
	typedef void (*CursorEnteringEventHandler)(CursorEnteringEvent*);
	typedef void (*CursorLeavingEventHandler)(CursorLeavingEvent*);
	typedef void (*MenuClickEventHandler)(MenuClickEvent*);
	typedef void (*CheckBoxClickEventHandler)(CheckBoxClickEvent*);
	typedef void (*CheckBoxClickEventHandler)(CheckBoxClickEvent*);
	typedef void (*DisableEventHandler)(DisableEvent*);
	typedef void (*EnableEventHandler)(EnableEvent*);
	typedef void (*FormMoveEventHandler)(FormMoveEvent*);
	typedef void (*ShowingEventHandler)(ShowingEvent*);
	typedef void (*HidingEventHandler)(HidingEvent*);

	enum EventType {
		None,
		Custom,
		ButtonClick,
		ButtonDoubleClick,
		CursorEntering,
		CursorLeaving,
		MenuClick,
		CheckBoxClick,
		Disable,
		Enable,
		FormMove,
		Showing,
		Hiding
	};
	class MenuItem;
	class IMenu {
		friend class Form;
	public:
		virtual HMENU getHMENU() = 0;
		virtual MenuItem* addMenu(Achar* Text, DWORD sytle = MF_STRING) = 0;
		virtual MenuItem* insertMenu(Achar* Text, int location, DWORD sytle = MF_STRING) = 0;
		virtual void removeMenu(MenuItem* node) = 0;
		virtual void removeMenu(int id) = 0;
		virtual MenuItem* getNode(int id) = 0;
		virtual Form* getOwner() = 0;
		virtual void setEventListener(EventHandler Listener) = 0;
	private:
		virtual void setOwner(Form* owner) = 0;
		virtual void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) = 0;
	};
	class IControl
	{
		friend class Form;
	public:
		IControl() { owner = 0; };
		Form* getOwner();
		virtual void onCreate(HWND hwnd) = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void setText(Achar* Text) = 0;
		virtual void getText(Achar* out) = 0;
		virtual void setEnable(bool enable) = 0;
		virtual bool isEnable() = 0;
		virtual int getID() = 0;
		virtual HWND getHWND() = 0;
		virtual DWORD getSytle() = 0;
		virtual void setSytle(DWORD sytle) = 0;
		void setPoint(Point point);
		void setSize(Size size);
		Point getPoint();
		Size getSize();
	private:
		virtual void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) = 0;
		virtual void destroy() = 0;
		void setOwner(Form* _owner);
		Form* owner;
		Point _point;
		Size _size;
	};
	class ICancelable {
	public:
		ICancelable() {
			Cancel = false;
		};
		void setCancel(bool cancel);
		bool isCancel();
	private:
		bool Cancel;
	};
	class IEvent {
	public:
		IEvent() {

		};
		virtual EventType getEventType() = 0;
		virtual bool isCancelable() {
			return false;
		};
	};
	class ButtonClickEvent : public IEvent {
	public:
		ButtonClickEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			Point tmp = Owner->getPoint();
			CursorONButton = Point(CursorONForm.GetX() - tmp.GetX(), CursorONForm.GetY() - tmp.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::ButtonClick;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		Point getCursorONButton();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		Point CursorONButton;
		IControl* owner;
	};
	class ButtonDoubleClickEvent : public IEvent {
	public:
		ButtonDoubleClickEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			Point tmp = Owner->getPoint();
			CursorONButton = Point(CursorONForm.GetX() - tmp.GetX(), CursorONForm.GetY() - tmp.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::ButtonDoubleClick;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		Point getCursorONButton();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		Point CursorONButton;
		IControl* owner;
	};
	class CursorEnteringEvent : public IEvent {
	public:
		CursorEnteringEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			Point tmp = Owner->getPoint();
			CursorONButton = Point(CursorONForm.GetX() - tmp.GetX(), CursorONForm.GetY() - tmp.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::CursorEntering;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		Point getCursorONButton();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		Point CursorONButton;
		IControl* owner;
	};
	class CursorLeavingEvent : public IEvent {
	public:
		CursorLeavingEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::CursorLeaving;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class MenuClickEvent : public IEvent, public ICancelable {
	public:
		MenuClickEvent(HWND Hwnd, IMenu* Owner, int Id) {
			hwnd = Hwnd;
			owner = Owner;
			id = Id;
		};
		EventType getEventType() {
			return EventType::MenuClick;
		};
		bool isCancelable() {
			return true;
		};
		int getId();
		IMenu* getOwner();
		MenuItem* getNode();
	private:
		HWND hwnd;
		IMenu* owner;
		int id;
	};
	class CheckBoxClickEvent : public IEvent, public ICancelable{
	public:
		CheckBoxClickEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			Point tmp = Owner->getPoint();
			CursorONCheckBox = Point(CursorONForm.GetX() - tmp.GetX(), CursorONForm.GetY() - tmp.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::CheckBoxClick;
		};
		bool isCancelable() {
			return true;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		Point getCursorONCheckBox();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		Point CursorONCheckBox;
		IControl* owner;
	};
	class DisableEvent : public IEvent, public ICancelable{
	public:
		DisableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::Disable;
		};
		bool isCancelable() {
			return true;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class EnableEvent : public IEvent, public ICancelable {
	public:
		EnableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		EventType getEventType() {
			return EventType::Enable;
		};
		bool isCancelable() {
			return true;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class FormMoveEvent : public IEvent{
	public:
		FormMoveEvent(Form* Form, Point newFormPoint, Size newFormSize) {
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - NewFormPoint.GetX(), p.y - NewFormPoint.GetY());
			NewFormPoint = newFormPoint;
			NewFormSize = newFormSize;
			form = Form;
		};
		EventType getEventType() {
			return EventType::FormMove;
		};
		bool isCancelable() {
			return false;
		};
		Point getCursorPoint();
		Point getCursorONForm();
		Point getNewFormPoint();
		Size getNewFormSize();
		Form* getForm();
	private:
		Form* form;
		Point CursorPoint;
		Point CursorONForm;
		Point NewFormPoint;
		Size NewFormSize;
	};
	class ShowingEvent : public IEvent, public ICancelable{
	public:
		ShowingEvent(void* sender) {
			owner = sender;
		}
		EventType getEventType() {
			return EventType::Showing;
		};
		bool isCancelable() {
			return true;
		};
		void* getOwner();

	private:
		void* owner;
	};
	class HidingEvent : public IEvent, public ICancelable {
	public:
		HidingEvent(void* sender) {
			owner = sender;
		}
		EventType getEventType() {
			return EventType::Hiding;
		};
		bool isCancelable() {
			return true;
		};
		void* getOwner();
	private:
		void* owner;
	};
}