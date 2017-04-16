#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "PreCompile.h"

class ViewPort
{
public:
	ViewPort();
	~ViewPort();

	// 设置窗口句柄
	void SetHWND(HWND hwnd);

	void Text(int nStartX, int nEndX, int nStartY, int nEndY, string &strText);

	//// 设置矩形区域
	//void SetRect(BYTE *pSrc, int nStartX, int nWidth, int nStartY, int nEndY);

	//// 设置整个屏幕
	//void SetFull(BYTE *pSrc);

	// 显示
	void Bilt(BYTE *pSrc);

	//BYTE *m_pBuffer;
	HDC m_hdc;                                        // 设备上下文
	HWND m_hWnd;                                      // 窗口句柄 
	BITMAPINFO m_bmpInfo;                             // BitBlt位图信息头
	RECT rect;
	string m_strText;
};

#endif