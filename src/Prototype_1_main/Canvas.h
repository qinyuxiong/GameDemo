#ifndef _Canvas_H_
#define _Canvas_H_

#include "PreCompile.h"
#include "ViewPort.h"

enum DRAW_TYPE
{
	DRAW_ANIMATE,
	DRAW_MAP,
	DRAW_DLG
};

class ViewPort;

class Canvas
{
public:
	BYTE *m_pSurface;
	ViewPort m_ViewPort;

	Canvas();
	~Canvas();

	void Init(HWND hWnd);

	void Blit2Screen();

	void Draw(int nDstStartX, int nDstStartY, int nSrcSartY, int nSrcEndY, int nSrcStartX, int nSrcEendX, int nSrcPitch, BYTE *pSrcData, DRAW_TYPE type);

	void Text(int nStartX, int nEndX, int nStartY, int nEndY, string &strText);
};

#endif