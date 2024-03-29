// SimplePaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimplePaint.h"
#include <iostream>
#include <vector>
using namespace std;
#include <windowsX.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

class CShape {
public:
	virtual void Draw(HDC hdc) = 0;
	virtual CShape* Create(int a, int b, int c, int d) = 0;
};

class CLine : public CShape {
private:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}

	CLine(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	CShape* Create(int a, int b, int c, int d) {
		return new CLine(a, b, c, d);
	}

	CLine() {}
};

class CRectangle : public CShape {
private:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Rectangle(hdc, x1, y1, x2, y2);
	}

	CRectangle(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	CShape* Create(int a, int b, int c, int d) {
		return new CRectangle(a, b, c, d);
	}

	CRectangle() {}
};
class CSquare : public CShape {
private:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		int temp = abs(x2 - x1);
		Rectangle(hdc, x1, y1, x1+temp,y1+temp);
	}

	CSquare(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	CShape* Create(int a, int b, int c, int d) {
		return new CSquare(a, b, c, d);
	}

	CSquare() {}
};

class CEllipse : public CShape {
private:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Ellipse(hdc, x1, y1, x2, y2);
	}

	CEllipse(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	CShape* Create(int a, int b, int c, int d) {
		return new CEllipse(a, b, c, d);
	}

	CEllipse() {}
};
class CCircle : public CShape {
private:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		int temp = abs(x2 - x1);
		Ellipse(hdc, x1, y1, x1 + temp, y1 + temp);
	}

	CCircle(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	CShape* Create(int a, int b, int c, int d) {
		return new CCircle(a, b, c, d);
	}

	CCircle() {}
};

vector<CShape*> shapes;
vector<CShape*> prototypes;
int startX;
int startY;
int lastX;
int lastY;
bool isDrawing = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu=GetMenu(hWnd);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		startX = x;
		startY = y;
		isDrawing = true;
	}
	break;
	case WM_MOUSEMOVE: {
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		WCHAR buffer[200];
		wsprintf(buffer, L"%d, %d", x, y);
		SetWindowText(hWnd, buffer);

		if (isDrawing) {
			lastX = x;
			lastY = y;

			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
					   break;
	case WM_LBUTTONUP: {
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		MENUITEMINFO menuItem = { 0 };
		menuItem.cbSize = sizeof(MENUITEMINFO);
		menuItem.fMask = MIIM_STATE;

		GetMenuItemInfo(hMenu, ID_DRAW_LINE, FALSE, &menuItem);
		if (menuItem.fState == MFS_CHECKED)
		{
			shapes.push_back(new CLine(startX, startY, x, y));

		}

		GetMenuItemInfo(hMenu, ID_DRAW_RECTANGLE, FALSE, &menuItem);
		if (menuItem.fState == MFS_CHECKED)
		{
			if (GetKeyState(VK_LSHIFT)<0)
			{
				shapes.push_back(new CSquare(startX, startY, startX+abs(startX-x), startY+abs(startY-y)));
			}
			else
			{
				shapes.push_back(new CRectangle(startX, startY, x, y));
			}		
		}

		GetMenuItemInfo(hMenu, ID_DRAW_ELLIPSE, FALSE, &menuItem);
		if (menuItem.fState == MFS_CHECKED)
		{
			if (menuItem.fState == MFS_CHECKED)
			{
				if (GetKeyState(VK_LSHIFT)<0)
				{
					shapes.push_back(new CCircle(startX, startY, startX + abs(startX - x), startY + abs(startY - y)));
				}
				else
				{
					shapes.push_back(new CEllipse(startX, startY, x, y));
				}
			}
		}


		isDrawing = false;

		InvalidateRect(hWnd, NULL, TRUE);

	}
					   break;

	case WM_CREATE:
	{
		prototypes.push_back(new CLine);
		prototypes.push_back(new CRectangle);
		prototypes.push_back(new CEllipse);
		prototypes.push_back(new CSquare);
		prototypes.push_back(new CCircle);
		CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED);

	}
	break;
	case WM_COMMAND:
	{
		
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_LINE: {
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
			CShape* shape = prototypes[0]->Create(0, 0, 0, 0);
			shapes.push_back(shape);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
						 
		case ID_DRAW_RECTANGLE:
		{
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
			if (GetKeyState(VK_LSHIFT)<0)
			{
				CShape* shape = prototypes[3]->Create(0, 0, 0, 0);
				shapes.push_back(shape);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				CShape* shape = prototypes[1]->Create(0, 0, 0, 0);
				shapes.push_back(shape);
				InvalidateRect(hWnd, NULL, TRUE);
			}	
			break;
		}
		case ID_DRAW_ELLIPSE:
		{
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_CHECKED);
			if (GetKeyState(VK_LSHIFT)<0)
			{
				CShape* shape = prototypes[4]->Create(0, 0, 0, 0);
				shapes.push_back(shape);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				CShape* shape = prototypes[2]->Create(0, 0, 0, 0);
				shapes.push_back(shape);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		MENUITEMINFO menuItem = { 0 };
		menuItem.cbSize = sizeof(MENUITEMINFO);
		menuItem.fMask = MIIM_STATE;

		

		HDC hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->Draw(hdc);
		}
		if (isDrawing) {
			GetMenuItemInfo(hMenu, ID_DRAW_LINE, FALSE, &menuItem);
			if (menuItem.fState==MFS_CHECKED)
			{
				MoveToEx(hdc, startX, startY, NULL);
				LineTo(hdc, lastX, lastY);
			}
			GetMenuItemInfo(hMenu, ID_DRAW_RECTANGLE, FALSE, &menuItem);
			if (menuItem.fState == MFS_CHECKED)
			{
				if (GetKeyState(VK_LSHIFT)<0)

				{
					int temp = abs(startX - lastX);
					Rectangle(hdc, startX, startY, startX+temp, startY+temp);
				}
				else
				{
					Rectangle(hdc, startX, startY, lastX, lastY);
				}	
			}
			GetMenuItemInfo(hMenu, ID_DRAW_ELLIPSE, FALSE, &menuItem);
			if (menuItem.fState == MFS_CHECKED)
			{
				if (GetKeyState(VK_LSHIFT)<0)

				{
					int temp = abs(startX - lastX);
					Ellipse(hdc, startX, startY, startX + temp, startY + temp);
				}
				else
				{
					Ellipse(hdc, startX, startY, lastX, lastY);
				}
				
			}
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}