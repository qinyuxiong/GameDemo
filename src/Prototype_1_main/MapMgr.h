#ifndef _MAGMGR_H_
#define _MAGMGR_H_

#include "MapBuffer.h"
#include "Canvas.h"

class MapMgr
{
public:
	BYTE *m_pMapData;                                 // ��ǰ������ʾ�ĵ�ͼ����
	MapBuffer m_pSurface[MAP_BUFFER_NUM];             // ��ȡ��ͼbuffer
	int m_nCurrentBlock;                              // ��ǰʹ�õ�Surface
	Rect m_recArea;                                   // ��ǰ����
	bool m_bPreloading;                               // ��ǰ�Ƿ�����һ��Surface�ڶ�ȡ
	Rect m_recMaxMapRange;                            // ��ͼ�������

	MapMgr();
	~MapMgr();

	// ������������ȡ��ʼBlockMap
	void Init();

	// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
	void MoveCamera(int nX, int nY);

	// �������ǰ��Ҫ��ʾ�ĵ�ͼ����
	void CalViewArea(int nX, int nY);

	// �ж��Ƿ�ӽ��߽�
	BOOL ApproachBoundary(int &nOffsetX, int &nOffsetY);

	// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
	void PreLoadMap(int nOffsetX, int nOffsetY);

	// ����
	void Draw(Canvas *pCanvas);

	int GetMaxLeft(){ return m_recMaxMapRange.nLeft; }

	int GetMaxRight(){ return m_recMaxMapRange.nRight; }

	int GetMaxTop(){ return m_recMaxMapRange.nTop; }

	int GetMaxDown(){ return m_recMaxMapRange.nDown; }
};

#endif