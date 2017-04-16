#ifndef _MapBuffer_H_
#define _MapBuffer_H_

#include "Image.h"
#include "PreCompile.h"
#include "Utility.h"

// 由四个地图子图拼成的一个当前地图载入区域
class MapBuffer
{
public:
	Image m_arrImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];       // 四个Bmp图片
	Rect m_recArea;                                                           // MapBuffer占大地图的区域
	int m_nLeftDownMapIndexX;                 	                              // 左下角地图块的索引
	int m_nLeftDownMapIndexY;

	MapBuffer();
	~MapBuffer();

	// 根据地图索引加载四张地图块
	void LoadSurfaces(int nIndexX, int nIndexY);

	// 拼接4块Block地图成一块大Block
	void Paste(BYTE *pDst);
};

#endif