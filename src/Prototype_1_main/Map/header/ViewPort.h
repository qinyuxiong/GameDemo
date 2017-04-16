#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "MapBlock.h"

class ViewPort
{
public:
	unsigned char *m_ViewData;                        // 窗口数据
	MapBlock m_pMapBlock[MAP_BLOCK_NUM];              // 双缓冲MapBlock
	int m_nCurrentBlock;                              // 当前使用的MapBlock
	Rect m_Rect;                                      // 当前区域
	bool m_bPreloading;                               // 当前是否另外一个MapBlock在读取
	HDC m_hdc;                                        // 设备上下文
	HWND m_hWnd;                                      // 窗口句柄 
	BITMAPINFO m_bmpInfo;                             // BitBlt位图信息头

	ViewPort();
	~ViewPort();

	// 设置窗口句柄和上下文
	void SetHWND(HWND hwnd);

	// 根据玩家坐标读取初始BlockMap
	void InitView(int nPlayerStartX, int nPlayerStartY);

	// 根据角色当前坐标移动视窗
	void MoveCamera(int nX, int nY);

	// 根据角色当前坐标预加载地图
	void PreLoadMap();

	// 获取当前视口数据
	void GetViewData();

	//// 投影到窗口
	//void Blit2Screen();

	//void Blit();
};

#endif