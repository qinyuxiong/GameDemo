#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "MapBlock.h"

class ViewPort
{
public:
	unsigned char *m_ViewData;                        // ��������
	MapBlock m_pMapBlock[MAP_BLOCK_NUM];              // ˫����MapBlock
	int m_nCurrentBlock;                              // ��ǰʹ�õ�MapBlock
	Rect m_Rect;                                      // ��ǰ����
	bool m_bPreloading;                               // ��ǰ�Ƿ�����һ��MapBlock�ڶ�ȡ
	HDC m_hdc;                                        // �豸������
	HWND m_hWnd;                                      // ���ھ�� 
	BITMAPINFO m_bmpInfo;                             // BitBltλͼ��Ϣͷ

	ViewPort();
	~ViewPort();

	// ���ô��ھ����������
	void SetHWND(HWND hwnd);

	// ������������ȡ��ʼBlockMap
	void InitView(int nPlayerStartX, int nPlayerStartY);

	// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
	void MoveCamera(int nX, int nY);

	// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
	void PreLoadMap();

	// ��ȡ��ǰ�ӿ�����
	void GetViewData();

	//// ͶӰ������
	//void Blit2Screen();

	//void Blit();
};

#endif