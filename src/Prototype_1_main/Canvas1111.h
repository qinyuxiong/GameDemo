//#ifndef _Canvas_H_
//#define _Canvas_H_
//
//#include "Surface.h"
//
//class Canvas
//{
//public:
//	BYTE *m_ViewData;                                 // 窗口数据
//	Surface m_pSurface[MAP_BLOCK_NUM];                // 双缓冲Surface
//	int m_nCurrentBlock;                              // 当前使用的Surface
//	Rect m_recArea;                                   // 当前区域
//	bool m_bPreloading;                               // 当前是否另外一个Surface在读取
//	//HDC m_hdc;                                        // 设备上下文
//	//HWND m_hWnd;                                      // 窗口句柄 
//	//BITMAPINFO m_bmpInfo;                             // BitBlt位图信息头
//
//	Canvas();
//	~Canvas();
//
//	//// 设置窗口句柄和上下文
//	//void SetHWND(HWND hwnd);
//
//	// 根据玩家坐标读取初始BlockMap
//	void Init(int nPlayerStartX, int nPlayerStartY);
//
//	// 根据角色当前坐标移动视窗
//	void MoveCamera(int nX, int nY);
//
//	// 根据角色当前坐标预加载地图
//	void PreLoadMap();
//
//	// 获取当前视口数据
//	void GetViewData();
//};
//
//#endif