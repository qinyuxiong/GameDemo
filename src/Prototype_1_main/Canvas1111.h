//#ifndef _Canvas_H_
//#define _Canvas_H_
//
//#include "Surface.h"
//
//class Canvas
//{
//public:
//	BYTE *m_ViewData;                                 // ��������
//	Surface m_pSurface[MAP_BLOCK_NUM];                // ˫����Surface
//	int m_nCurrentBlock;                              // ��ǰʹ�õ�Surface
//	Rect m_recArea;                                   // ��ǰ����
//	bool m_bPreloading;                               // ��ǰ�Ƿ�����һ��Surface�ڶ�ȡ
//	//HDC m_hdc;                                        // �豸������
//	//HWND m_hWnd;                                      // ���ھ�� 
//	//BITMAPINFO m_bmpInfo;                             // BitBltλͼ��Ϣͷ
//
//	Canvas();
//	~Canvas();
//
//	//// ���ô��ھ����������
//	//void SetHWND(HWND hwnd);
//
//	// ������������ȡ��ʼBlockMap
//	void Init(int nPlayerStartX, int nPlayerStartY);
//
//	// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
//	void MoveCamera(int nX, int nY);
//
//	// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
//	void PreLoadMap();
//
//	// ��ȡ��ǰ�ӿ�����
//	void GetViewData();
//};
//
//#endif