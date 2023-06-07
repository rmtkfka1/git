#include "pch.h"
#include <tchar.h>
#include "GAME.h"
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	RECT rt = { 0,0,1200,600 };
	GAME Game;

	Game.Init(hWnd);
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	float t = rt.bottom - rt.top;
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	while (1) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			Game.Update();
			Game.Render();
		}
	}
	return (int)Message.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt = { 0,0,800,600 };
	static HBITMAP hBitmap = NULL;
	static HDC mdc = NULL;
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == 'q')
			exit(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}