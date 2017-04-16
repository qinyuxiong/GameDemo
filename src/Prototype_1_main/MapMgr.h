#ifndef _MAGMGR_H_
#define _MAGMGR_H_

#include "MapBuffer.h"
#include "Canvas.h"

class MapMgr
{
public:
	BYTE *m_pMapData;                                 // 当前窗口显示的地图数据
	MapBuffer m_pSurface[MAP_BUFFER_NUM];             // 读取地图buffer
	int m_nCurrentBlock;                              // 当前使用的Surface
	Rect m_recArea;                                   // 当前区域
	bool m_bPreloading;                               // 当前是否另外一个Surface在读取
	Rect m_recMaxMapRange;                            // 地图最大区域

	MapMgr();
	~MapMgr();

	// 根据玩家坐标读取初始BlockMap
	void Init();

	// 根据角色当前坐标移动视窗
	void MoveCamera(int nX, int nY);

	// 计算出当前需要显示的地图区域
	void CalViewArea(int nX, int nY);

	// 判断是否接近边界
	BOOL ApproachBoundary(int &nOffsetX, int &nOffsetY);

	// 根据角色当前坐标预加载地图
	void PreLoadMap(int nOffsetX, int nOffsetY);

	// 绘制
	void Draw(Canvas *pCanvas);

	int GetMaxLeft(){ return m_recMaxMapRange.nLeft; }

	int GetMaxRight(){ return m_recMaxMapRange.nRight; }

	int GetMaxTop(){ return m_recMaxMapRange.nTop; }

	int GetMaxDown(){ return m_recMaxMapRange.nDown; }
};

#endif