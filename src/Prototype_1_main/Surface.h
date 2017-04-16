//#ifndef _Surface_H_
//#define _Surface_H_
//
//#include "BmpImage.h"
//#include "PreCompile.h"
//#include "Utility.h"
//
//// 四个Bmp图片拼成的一个地图Block
//class Surface
//{
//public:
//	BmpImage m_arrImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];       // 四个Bmp图片
//	BYTE *m_pData;                                                            // 四个Bmp图片拼接成的Surface数据 
//	Rect m_recArea;                                                           // Surface占大地图的区域
//	int m_nLeftDownMapIndexX;                 	                              // 左下角地图块的索引
//	int m_nLeftDownMapIndexY;
//
//	Surface();
//	~Surface();
//
//	// 根据地图索引加载四张地图块
//	void LoadSurfaces(int nIndexX, int nIndexY);
//
//	// 拼接4块Block地图成一块大Block
//	void Paste();
//};
//
//#endif