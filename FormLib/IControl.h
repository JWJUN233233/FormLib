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
	class DLL IEvent;
	typedef void (*EventProc)(IEvent*);
	class DLL Form;
	class DLL MenuNode;
	class DLL IMenu {
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
	class DLL IControl
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
	class DLL IEvent {
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
	class DLL Event : public IEvent {
	public:
		void getEventType(char* out) {
			sprintf_s(out,MAX_PATH, "Event");
		};
	private:
	};
	class DLL ButtonClickEvent : public IEvent {
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
	class DLL ButtonDoubleClickEvent : public IEvent {
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
	class DLL CursorEnteringEvent : public IEvent {
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
	class DLL CursorLeavingEvent : public IEvent {
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
		Point getCursorONForm();
		IControl* getOwner();
	private:
		HWND hwnd;
		Point CursorPoint;
		Point CursorONForm;
		IControl* owner;
	};
	class DLL DisableEvent : public IEvent {
	public:
		DisableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "DisableEvent");
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
	class DLL EnableEvent : public IEvent {
	public:
		EnableEvent(HWND Hwnd, Point FormPoint, IControl* Owner) {
			hwnd = Hwnd;
			POINT p;
			GetCursorPos(&p);
			CursorPoint = Point(p.x, p.y);
			CursorONForm = Point(p.x - FormPoint.GetX(), p.y - FormPoint.GetY());
			owner = Owner;
		};
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "EnableEvent");
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
	class DLL MenuClickEvent : public IEvent {
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
	class DLL CheckBoxClickEvent : public IEvent {
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
		void getEventType(char* out) {
			sprintf_s(out, MAX_PATH, "CheckBoxClickEvent");
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
	inline DLL void EmptyEvent(FormLib::IEvent* e) {}
}