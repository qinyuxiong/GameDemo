#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "PreCompile.h"

class ViewPort
{
public:
	ViewPort();
	~ViewPort();

	// ���ô��ھ��
	void SetHWND(HWND hwnd);

	void Text(int nStartX, int nEndX, int nStartY, int nEndY, string &strText);

	//// ���þ�������
	//void SetRect(BYTE *pSrc, int nStartX, int nWidth, int nStartY, int nEndY);

	//// ����������Ļ
	//void SetFull(BYTE *pSrc);

	// ��ʾ
	void Bilt(BYTE *pSrc);

	//BYTE *m_pBuffer;
	HDC m_hdc;                                        // �豸������
	HWND m_hWnd;                                      // ���ھ�� 
	BITMAPINFO m_bmpInfo;                             // BitBltλͼ��Ϣͷ
	RECT rect;
	string m_strText;
};

#endif