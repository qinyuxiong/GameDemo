#ifndef _MAPBLOCK_H_
#define _MAPBLOCK_H_

#include "BmpImage.h"
#include "PreCompile.h"
#include "Utility.h"

// �ĸ�BmpͼƬƴ�ɵ�һ����ͼBlock
class MapBlock
{
public:
	BmpImage m_FourImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];   // �ĸ�BmpͼƬ
	unsigned char *m_pData;                                                // �ĸ�BmpͼƬƴ�ӳɵ�MapBlock���� 
	Rect m_Rect;                                                           // MapBlockռ���ͼ������
	int m_nLeftDownMapXIndex;                 	                           // ���½ǵ�ͼ�������
	int m_nLeftDownMapYIndex;

	MapBlock();
	~MapBlock();

	// ���ݵ�ͼ�����������ŵ�ͼ��
	void LoadMapBlocks(int nIndexX, int nIndexY);

	// ƴ��4��Block��ͼ��һ���Block
	void MakeJoint();
};

#endif