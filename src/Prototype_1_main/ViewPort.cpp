#include "ViewPort.h"

ViewPort::ViewPort()
{
	//m_pBuffer = new BYTE[VIEWHEIGHT * VIEWWIDTH * 4];
}

ViewPort::~ViewPort()
{
	//delete m_pBuffer;
}

// 设置窗口句柄 
void ViewPort::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
	m_hdc = GetDC(m_hWnd);

	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
}

void ViewPort::Text(int nStartX, int nEndX, int nStartY, int nEndY, string &strText)
{
	rect.left = nStartX;
	rect.right = nEndX;
	rect.bottom = nEndY;
	rect.top = nStartY;
	m_strText = strText;
}

//// 设置矩形区域
//void ViewPort::SetRect(BYTE *pSrc, int nStartX, int nWidth, int nStartY, int nEndY)
//{
//	for (int i = nStartY, k = 0; i < nEndY; i++, k++)
//		memcpy(m_pBuffer + i * VIEWWIDTH * 4 + nStartX * 4, pSrc + k * nWidth * 4, nWidth * 4);
//}

//// 设置整个屏幕
//void ViewPort::SetFull(BYTE *pSrc)
//{
//	memcpy(m_pBuffer, pSrc, VIEWWIDTH * VIEWHEIGHT * 4);
//}

void ViewPort::Bilt(BYTE *pSrc)
{
	SetDIBitsToDevice(m_hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, 0, 0, 0, VIEWHEIGHT, pSrc, &m_bmpInfo, 0);
	DrawText(m_hdc, m_strText.c_str(), m_strText.length(), &rect, DT_CENTER | DT_VCENTER);
}

//ViewPort *g_pViewPort = new ViewPort;