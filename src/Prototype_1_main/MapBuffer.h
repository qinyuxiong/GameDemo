#ifndef _MapBuffer_H_
#define _MapBuffer_H_

#include "Image.h"
#include "PreCompile.h"
#include "Utility.h"

// ���ĸ���ͼ��ͼƴ�ɵ�һ����ǰ��ͼ��������
class MapBuffer
{
public:
	Image m_arrImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];       // �ĸ�BmpͼƬ
	Rect m_recArea;                                                           // MapBufferռ���ͼ������
	int m_nLeftDownMapIndexX;                 	                              // ���½ǵ�ͼ�������
	int m_nLeftDownMapIndexY;

	MapBuffer();
	~MapBuffer();

	// ���ݵ�ͼ�����������ŵ�ͼ��
	void LoadSurfaces(int nIndexX, int nIndexY);

	// ƴ��4��Block��ͼ��һ���Block
	void Paste(BYTE *pDst);
};

#endif