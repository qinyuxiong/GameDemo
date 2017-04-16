#include <Windows.h>
#include <iostream>

#include "ViewPort.h"
#include "ScreenData.h"
#include "DlgMgr.h"

using namespace std;

WNDCLASSEX  wcex;
HINSTANCE   hInst;
const TCHAR WndClass[] = "One";
const TCHAR WndTitle[] = "One";
static HWND hWnd;

WORD RegWndClass(HINSTANCE hInstance);
BOOL InitWnd(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern ScreenData *g_pScreenData;
extern DlgMgr *g_pDlgMgr;

int nPlayerPosX = 9985;
int nPlayerPosY = 7984;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	if (!RegWndClass(hInstance))
		return false;

	if (!InitWnd(hInstance, nCmdShow))//初始化
		return false;

	ViewPort ScreenView;
	ScreenView.SetHWND(hWnd);
	ScreenView.InitView(nPlayerPosX, nPlayerPosY);

	g_pScreenData->SetHWND(hWnd);
	Dialog *p = g_pDlgMgr->CreateDlg(string("Dialog"));
	g_pDlgMgr->SendMsg(string("Dialog"), string("Dialog"), string("MSG_SHOW"));
	//p->Draw();

	//BmpImage image;
	//image.LoadImg("BigMap_1_1.bmp");

	//ViewPort ScreenView;
	//HDC hdc, hdcMem;
	//hdc = GetDC(hWnd);
	//hdcMem = CreateCompatibleDC(hdc);

	//BITMAPINFO bmpInfo = { { sizeof(BITMAPINFOHEADER), MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, 1, 32, BI_RGB, MAP_BLOCK_WIDTH * MAP_BLOCK_HEIGHT * 4, 0, 0, 0, 0 } };
	//LPVOID ptr;
	//HBITMAP nBmp = CreateDIBSection(hdcMem, &bmpInfo, DIB_RGB_COLORS, &ptr, 0, 0);
	//HBITMAP oBmp = (HBITMAP)SelectObject(hdcMem, nBmp);

	//memcpy(ptr, ScreenView.m_pMapBlock[0].m_FourImages[0][0].m_pData, 1750 * 900 * 4);

	//BitBlt(hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, hdcMem, 0, 0, SRCCOPY);
	//ReleaseDC(hWnd, hdc);

	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)//进入消息循环
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			ScreenView.MoveCamera(nPlayerPosX, nPlayerPosY);
			g_pDlgMgr->SendMsg(string("Dialog"), string("Dialog"), string("MSG_SHOW"));
			g_pScreenData->Bilt();
		}
	}
	UnregisterClass(WndClass, wcex.hInstance);
	return msg.wParam;
}

WORD RegWndClass(HINSTANCE hInstance)
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_WINICON);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WndClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL InitWnd(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow(WndClass, WndTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, VIEWWIDTH + 12, VIEWHEIGHT + 34, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return false;

	RECT rect = { 0, 0, VIEWWIDTH + 12, VIEWHEIGHT + 34};
	int wx = rect.right - rect.left;
	int wy = rect.bottom - rect.top;
	int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(hWnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_UP)
		{
			nPlayerPosY += 10;
		}
		else if (wParam == VK_DOWN)
		{
			nPlayerPosY -= 10;
		}
		else if (wParam == VK_LEFT)
		{
			nPlayerPosX -= 10;
		}
		else if (wParam == VK_RIGHT)
		{
			nPlayerPosX += 10;
		}
	}
	else if (message == WM_LBUTTONDOWN)
	{
		Point ptMouse;
		ptMouse.nX = LOWORD(lParam);
		ptMouse.nY = HIWORD(lParam);
		g_pDlgMgr->ButtonClick(ptMouse);
	}
	else if (message == WM_DESTROY)
		PostQuitMessage(0);

	return DefWindowProc(hWnd, message, wParam, lParam);
}