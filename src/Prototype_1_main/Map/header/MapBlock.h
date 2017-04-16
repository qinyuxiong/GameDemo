#ifndef _MAPBLOCK_H_
#define _MAPBLOCK_H_

#include "BmpImage.h"
#include "PreCompile.h"
#include "Utility.h"

// 四个Bmp图片拼成的一个地图Block
class MapBlock
{
public:
	BmpImage m_FourImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];   // 四个Bmp图片
	unsigned char *m_pData;                                                // 四个Bmp图片拼接成的MapBlock数据 
	Rect m_Rect;                                                           // MapBlock占大地图的区域
	int m_nLeftDownMapXIndex;                 	                           // 左下角地图块的索引
	int m_nLeftDownMapYIndex;

	MapBlock();
	~MapBlock();

	// 根据地图索引加载四张地图块
	void LoadMapBlocks(int nIndexX, int nIndexY);

	// 拼接4块Block地图成一块大Block
	void MakeJoint();
};

#endif