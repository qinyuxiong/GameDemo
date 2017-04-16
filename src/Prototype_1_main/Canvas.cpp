#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
	if (m_pSurface != NULL)
		delete m_pSurface;
}

void Canvas::Init(HWND hWnd)
{
	m_pSurface = new BYTE[VIEWWIDTH * 4 * VIEWHEIGHT];
	m_ViewPort.SetHWND(hWnd);
}

void Canvas::Blit2Screen()
{
	m_ViewPort.Bilt(m_pSurface);
}


void Canvas::Draw(int nDstStartX, int nDstStartY, int nSrcSartY, int nSrcEndY, int nSrcStartX, int nSrcEendX, int nSrcPitch, BYTE *pSrcData, DRAW_TYPE type)
{
	if (pSrcData == NULL || pSrcData == NULL)
		return;

	BYTE *pDst = m_pSurface + nDstStartY * VIEWWIDTH * 4 + nDstStartX * 4;
	int nWidth = nSrcEendX - nSrcStartX;
	BYTE *pSrc = pSrcData + nSrcSartY * nSrcPitch + nSrcStartX * 4;
	int nDstPitch = VIEWWIDTH * 4;

	for (int i = nSrcSartY; i < nSrcEndY; i++)
	{
		if (type == DRAW_MAP)
		{
			memcpy(pDst, pSrc, nWidth * 4);
		}
		else if (type == DRAW_ANIMATE || type == DRAW_DLG)
		{
			for (int j = 0; j < nWidth * 4; j++)
			{
				// 暂且这样做
				if (*(pSrc + j) != 255)
					*(pDst + j) = *(pSrc + j);
			}
		}
		pDst += nDstPitch;
		pSrc += nSrcPitch;
	}
}

void Canvas::Text(int nStartX, int nEndX, int nStartY, int nEndY, string &strText)
{
	m_ViewPort.Text(nStartX, nEndX, nStartY, nEndY, strText);
}

// 全局变量
Canvas *g_pCanvas;