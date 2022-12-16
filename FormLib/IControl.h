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
	class IEvent;
	typedef void (*EventProc)(IEvent*);
	class Form;
	class MenuNode;
	class IMenu {
		friend class Form;
	public:
		virtual HMENU getHMENU() = 0;
		virtual MenuNode* addMenu(Achar* Text, DWORD sytle = MF_STRING) = 0;
		virtual MenuNode* insertMenu(Achar* Text, int location, DWORD sytle = MF_STRING) = 0;
		virtual void removeMenu(MenuNode* node) = 0;
		virtual void removeMenu(int id) = 0;
		virtual MenuNode* getNode(int id) = 0;
		virtual Form* getOwner() = 0;
		virtual void setEventListener(EventProc Listener) = 0;
	private:
		virtual void setOwner(Form* owner) = 0;
		virtual void onFormCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) = 0;
	};;
	class IControl
	{
		friend class Form;
	public:
		IControl() { owner = 0; };
		Form* getOwner();
		virtual void onCreate(HWND hwnd) = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void setText(Achar* Text) = 0;
		virtual void getText(Achar* out) = 0;
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
	class MenuClickEvent : public IEvent {
	public:
		MenuClickEvent(HWND Hwnd, IMenu* Owner,int Id) {
			hwnd = Hwnd;
			owner = Owner;
			id = Id;
		};
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "MenuClickEvent");
		};
		int getId();
		IMenu* getOwner();
		MenuNode* getNode();
	private:
		HWND hwnd;
		IMenu* owner;
		int id;
	};
	inline void EmptyEvent(FormLib::IEvent* e) {}
}