#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_

#include "PreCompile.h"

class ScreenData
{
public:
	ScreenData();
	~ScreenData();

	// ���ô��ھ��
	void SetHWND(HWND hwnd);

	// ���þ�������
	void SetRect(unsigned char *pSrc, int nStartX, int nWidth, int nStartY, int nEndY);

	// ����������Ļ
	void SetFull(unsigned char *pSrc);

	// ��ʾ
	void Bilt();

	unsigned char *m_pBuffer;
	HDC m_hdc;                                        // �豸������
	HWND m_hWnd;                                      // ���ھ�� 
	BITMAPINFO m_bmpInfo;                             // BitBltλͼ��Ϣͷ
};

#endif