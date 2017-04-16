#include <Windows.h>
#include <iostream>

#include "Canvas.h"
#include "ViewPort.h"
#include "DlgMgr.h"
#include "GameMgr.h"
#include "MapMgr.h"
#include "Animation.h"

using namespace std;

WNDCLASSEX  wcex;
HINSTANCE   hInst;
const TCHAR WndClass[] = "One";
const TCHAR WndTitle[] = "One";
static HWND hWnd;

WORD RegWndClass(HINSTANCE hInstance);
BOOL InitWnd(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern DlgMgr *g_pDlgMgr;
extern GameMgr *g_pGameMgr;
extern MapMgr *g_pMapMgr;
extern Canvas *g_pCanvas;

int nPlayerPosX = 683;
int nPlayerPosY = 384;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	if (!RegWndClass(hInstance))
		return false;

	if (!InitWnd(hInstance, nCmdShow))//初始化
		return false;

	g_pGameMgr->InitGame(hWnd);
	g_pMapMgr->Init();

	Dialog *p = g_pDlgMgr->CreateDlg(string("Dialog"));


	//p->Draw(g_pCanvas, 200, 200, 400, 200, );

	//Image image;
	//image.LoadBmpImg("BigMap_1_1.bmp");

	//Canvas ScreenView;
	//HDC hdc, hdcMem;
	//hdc = GetDC(hWnd);
	//hdcMem = CreateCompatibleDC(hdc);

	//BITMAPINFO bmpInfo = { { sizeof(BITMAPINFOHEADER), MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, 1, 32, BI_RGB, MAP_BLOCK_WIDTH * MAP_BLOCK_HEIGHT * 4, 0, 0, 0, 0 } };
	//LPVOID ptr;
	//HBITMAP nBmp = CreateDIBSection(hdcMem, &bmpInfo, DIB_RGB_COLORS, &ptr, 0, 0);
	//HBITMAP oBmp = (HBITMAP)SelectObject(hdcMem, nBmp);

	//memcpy(ptr, ScreenView.m_pSurface[0].m_FourImages[0][0].m_pData, 1750 * 900 * 4);

	//BitBlt(hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, hdcMem, 0, 0, SRCCOPY);
	//ReleaseDC(hWnd, hdc);

	MSG msg;
	msg.message = WM_NULL;
	/*Animation *pAnimate = new Animation;
	pAnimate->LoadAnimation("../res/Animate/Player/00001/Forward/");
	pAnimate->Start();*/
	DWORD dwLastTime = GetTickCount();
	DWORD dwCurTime;
	while (msg.message != WM_QUIT)//进入消息循环
	{
		dwCurTime = GetTickCount();
		if (dwCurTime - dwLastTime >= 35)
		{
			g_pMapMgr->Draw(g_pCanvas);
			g_pDlgMgr->SendMsg(string("Dialog"), string("Dialog"), string("MSG_SHOW"));
			//pAnimate->Draw(g_pCanvas, 100, 0, 0, 100, 0);
			g_pCanvas->Blit2Screen();
			dwLastTime = dwCurTime;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//g_pCanvas->Blit2Screen();
			//ScreenView.MoveCamera(nPlayerPosX, nPlayerPosY);
			//g_pDlgMgr->SendMsg(string("Dialog"), string("Dialog"), string("MSG_SHOW"));
			//g_pViewPort->Bilt();
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
		if (wParam == VK_UP && nPlayerPosY <= g_pMapMgr->GetMaxTop())
		{
			nPlayerPosY += 10;
		}
		else if (wParam == VK_DOWN && nPlayerPosY >= g_pMapMgr->GetMaxDown())
		{
			nPlayerPosY -= 10;
		}
		else if (wParam == VK_LEFT && nPlayerPosX >= g_pMapMgr->GetMaxLeft())
		{
			nPlayerPosX -= 10;
		}
		else if (wParam == VK_RIGHT && nPlayerPosX <= g_pMapMgr->GetMaxRight())
		{
			nPlayerPosX += 10;
		}
		g_pMapMgr->MoveCamera(nPlayerPosX, nPlayerPosY);
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