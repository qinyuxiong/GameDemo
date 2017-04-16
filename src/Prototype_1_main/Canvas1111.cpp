//#include "Canvas.h"
//#include "ScreenData.h"
//
//extern ScreenData *g_pScreenData;
//
//Canvas::Canvas()
//{
//	m_bPreloading = false;
//	m_nCurrentBlock = 0;
//	//m_pSurface[m_nCurrentBlock].LoadSurfaces(1, 1);
//	m_ViewData = new BYTE[VIEWHEIGHT * VIEWWIDTH * 4];
//}
//
//Canvas::~Canvas()
//{
//	delete m_ViewData;
//}
//
////// 设置数据
////void Canvas::SetHWND(HWND hwnd)
////{
////	m_hWnd = hwnd;
////	m_hdc = GetDC(m_hWnd);
////
////	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
////}
//
//// 根据玩家坐标读取初始BlockMap
//void Canvas::Init(int nPlayerStartX, int nPlayerStartY)
//{
//	int n = nPlayerStartX / MAP_BLOCK_WIDTH;
//	int m = nPlayerStartY / MAP_BLOCK_HEIGHT;
//
//	// 最初两BlockMap应该为同一个
//	m_pSurface[0].LoadSurfaces(n, m);
//	//m_pSurface[1].LoadSurfaces(n, m);
//}
//
//// 根据角色当前坐标移动视窗
//void Canvas::MoveCamera(int nX, int nY)
//{
//	// 根据当前玩家坐标点计算出视口范围
//	if (nX <= VIEW_PORT_MAX_X && nX >= VIEW_PORT_MIN_X)
//	{
//		m_recArea.nLeft = nX - VIEWWIDTH / 2;
//		m_recArea.nRight = m_recArea.nLeft + VIEWWIDTH;
//	}
//	else if (nX > VIEW_PORT_MAX_X)
//	{
//		m_recArea.nLeft = BIG_MAP_WIDTH - VIEWWIDTH;
//		m_recArea.nRight = BIG_MAP_WIDTH;
//	}
//	else if (nX < VIEW_PORT_MIN_X)
//	{
//		m_recArea.nLeft = 0;
//		m_recArea.nRight = VIEWWIDTH;
//	}
//	if (nY <= VIEW_PORT_MAX_Y && nY >= VIEW_PORT_MIN_Y)
//	{
//		m_recArea.nDown = nY - VIEWHEIGHT / 2;
//		m_recArea.nTop = m_recArea.nDown + VIEWHEIGHT;
//	}
//	else if (nY > VIEW_PORT_MAX_Y)
//	{
//		m_recArea.nDown = BIG_MAP_HEIGHT - VIEWHEIGHT;
//		m_recArea.nTop = BIG_MAP_HEIGHT;
//	}
//	else if (nY < VIEW_PORT_MIN_Y)
//	{
//		m_recArea.nDown = 0;
//		m_recArea.nTop = VIEWHEIGHT;
//	}
//
//	// 正在加载地图
//	if (!m_bPreloading)
//		PreLoadMap();
//
//	// 获取当前视角数据
//	GetViewData();
//
//	// 投影到屏幕
//	g_pScreenData->SetFull(m_ViewData);
//}
//
//// 根据角色当前坐标预加载地图
//void Canvas::PreLoadMap()
//{
//	// 判断是否接近边界
//	int nIndexAddX = 0, nIndexAddY = 0;
//	// 接近BigMap左边界
//	if (m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft <= EXCEED_BOUND_WIDTH && m_recArea.nLeft >= MAP_BLOCK_WIDTH)
//		nIndexAddX = -1;
//	// 接近BigMap右边界
//	else if (m_recArea.nRight + EXCEED_BOUND_WIDTH >= m_pSurface[m_nCurrentBlock].m_recArea.nRight && m_recArea.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
//		nIndexAddX = 1;
//	// 接近BigMap下边界
//	if (m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown <= EXCEED_BOUND_HEIGHT && m_recArea.nDown >= MAP_BLOCK_HEIGHT)
//		nIndexAddY = -1;
//	// 接近BigMap上边界
//	else if (m_recArea.nTop + EXCEED_BOUND_HEIGHT >= m_pSurface[m_nCurrentBlock].m_recArea.nTop && m_recArea.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
//		nIndexAddY = 1;
//
//	if (0 == nIndexAddX && 0 == nIndexAddY)
//		return;
//
//	// 计算下一个Surface的左下角索引
//	int nCurIndexX = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexX;
//	int nCurIndexY = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexY;
//	nCurIndexX += nIndexAddX;
//	nCurIndexY += nIndexAddY;
//
//	// 进行地图预加载
//	if (0 == m_nCurrentBlock)
//	{
//		m_pSurface[1].LoadSurfaces(nCurIndexX, nCurIndexY);
//		m_nCurrentBlock = 1;
//		m_bPreloading = false;
//
//		m_pSurface[0].m_nLeftDownMapIndexX = nCurIndexX;
//		m_pSurface[0].m_nLeftDownMapIndexY = nCurIndexY;
//	}
//	else if (1 == m_nCurrentBlock)
//	{
//		m_pSurface[0].LoadSurfaces(nCurIndexX, nCurIndexY);
//		m_nCurrentBlock = 0;
//		m_bPreloading = false;
//
//		m_pSurface[1].m_nLeftDownMapIndexX = nCurIndexX;
//		m_pSurface[1].m_nLeftDownMapIndexY = nCurIndexY;
//	}
//}
//
//// 获取当前视角数据
//void Canvas::GetViewData()
//{
//	Surface *index = &m_pSurface[m_nCurrentBlock];
//
//	// 确定当前视角相对于Surface的坐标偏移
//	int nStartX = m_recArea.nLeft - index->m_recArea.nLeft;
//	int nStartY = m_recArea.nDown - index->m_recArea.nDown;
//	int k = 0;
//
//	// 每行字节数
//	int nPitch = VIEWWIDTH * 4;
//
//	// 根据坐标读取数据
//	for (int i = nStartY; i < nStartY + VIEWHEIGHT; i++)
//	{
//		memcpy(m_ViewData + k, index->m_pData + i * MAP_BLOCK_WIDTH * 4 * 2 + nStartX * 4, nPitch);
//		k += nPitch;
//	}
//}