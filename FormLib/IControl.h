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
	class IControl
	{
		friend class Form;
	public:
		IControl() { owner = 0; };
		Form* getOwner();
		virtual void onCreate(HWND hwnd) = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void setText(achar* Text) = 0;
		virtual void getText(achar* out) = 0;
		virtual void setEnable(bool enable) = 0;
		virtual bool isEnable() = 0;
		virtual int getID() = 0;
		void setPoint(Point point);
		void setSize(Size size);
		Point getPoint();
		Size getSize();
	private:
		virtual void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) = 0;
		virtual void Destroy() = 0;
		void setOwner(Form* _owner);
		Form* owner;
		Point _point;
		Size _size;
	};
	class IEvent {
	public:
		IEvent() {
			Cancel = false;
		};
		virtual void getEventType(char* out) = 0;
		void setCancel(bool cancel);
		bool isCancel();
	private:
		bool Cancel;
	};
	typedef void (*EventProc)(IEvent*);
	class Event : public IEvent {
	public:
		void getEventType(char* out) {
			sprintf_s(out,MAX_PATH, "Event");
		};
	private:
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
		void getEventType(char* out) {
			sprintf_s(out,MAX_PATH, "ButtonClickEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		Point getCuosorONButton();
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
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "ButtonDoubleClickEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		Point getCuosorONButton();
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
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "CursorEnteringEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		Point getCuosorONButton();
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
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "CursorLeavingEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class ButtonDisableEvent : public IEvent {
	public:
		ButtonDisableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "ButtonDisableEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class ButtonEnableEvent : public IEvent {
	public:
		ButtonEnableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "ButtonEnableEvent");
		};
		Point getCursorPoint();
		Point getCuosorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	inline void EmptyEvent(FormLib::IEvent* e) {

	}
}