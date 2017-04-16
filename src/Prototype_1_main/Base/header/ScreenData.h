#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_

#include "PreCompile.h"

class ScreenData
{
public:
	ScreenData();
	~ScreenData();

	// 设置窗口句柄
	void SetHWND(HWND hwnd);

	// 设置矩形区域
	void SetRect(unsigned char *pSrc, int nStartX, int nWidth, int nStartY, int nEndY);

	// 设置整个屏幕
	void SetFull(unsigned char *pSrc);

	// 显示
	void Bilt();

	unsigned char *m_pBuffer;
	HDC m_hdc;                                        // 设备上下文
	HWND m_hWnd;                                      // 窗口句柄 
	BITMAPINFO m_bmpInfo;                             // BitBlt位图信息头
};

#endif