#include "ScreenData.h"

ScreenData::ScreenData()
{
	m_pBuffer = new unsigned char[VIEWHEIGHT * VIEWWIDTH * 4];
}

ScreenData::~ScreenData()
{
	delete m_pBuffer;
}

// 设置窗口句柄 
void ScreenData::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
	m_hdc = GetDC(m_hWnd);

	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
}

// 设置矩形区域
void ScreenData::SetRect(unsigned char *pSrc, int nStartX, int nWidth, int nStartY, int nEndY)
{
	for (int i = nStartY, k = 0; i < nEndY; i++, k++)
		memcpy(m_pBuffer + i * VIEWWIDTH * 4 + nStartX * 4, pSrc + k * nWidth * 4, nWidth * 4);
}

// 设置整个屏幕
void ScreenData::SetFull(unsigned char *pSrc)
{
	memcpy(m_pBuffer, pSrc, VIEWWIDTH * VIEWHEIGHT * 4);
}

void ScreenData::Bilt()
{
	SetDIBitsToDevice(m_hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, 0, 0, 0, VIEWHEIGHT, m_pBuffer, &m_bmpInfo, 0);
}

ScreenData *g_pScreenData = new ScreenData;