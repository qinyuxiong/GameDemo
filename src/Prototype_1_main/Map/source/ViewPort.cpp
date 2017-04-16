#include "ViewPort.h"
#include "ScreenData.h"

extern ScreenData *g_pScreenData;

ViewPort::ViewPort()
{
	m_bPreloading = false;
	m_nCurrentBlock = 0;
	m_pMapBlock[m_nCurrentBlock].LoadMapBlocks(1, 1);
	m_ViewData = new unsigned char[VIEWHEIGHT * VIEWWIDTH * 4];
}

ViewPort::~ViewPort()
{
	delete m_ViewData;
}

// 设置数据
void ViewPort::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
	m_hdc = GetDC(m_hWnd);

	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
}

// 根据玩家坐标读取初始BlockMap
void ViewPort::InitView(int nPlayerStartX, int nPlayerStartY)
{
	int n = nPlayerStartX / MAP_BLOCK_WIDTH;
	int m = nPlayerStartY / MAP_BLOCK_HEIGHT;

	// 最初两BlockMap应该为同一个
	m_pMapBlock[0].LoadMapBlocks(n, m);
	m_pMapBlock[1].LoadMapBlocks(n, m);
}

// 根据角色当前坐标移动视窗
void ViewPort::MoveCamera(int nX, int nY)
{
	// 根据当前玩家坐标点计算出视口范围
	if (nX <= VIEW_PORT_MAX_X && nX >= VIEW_PORT_MIN_X)
	{
		m_Rect.nLeft = nX - VIEWWIDTH / 2;
		m_Rect.nRight = m_Rect.nLeft + VIEWWIDTH;
	}
	else if (nX > VIEW_PORT_MAX_X)
	{
		m_Rect.nLeft = BIG_MAP_WIDTH - VIEWWIDTH;
		m_Rect.nRight = BIG_MAP_WIDTH;
	}
	else if (nX < VIEW_PORT_MIN_X)
	{
		m_Rect.nLeft = 0;
		m_Rect.nRight = VIEWWIDTH;
	}
	if (nY <= VIEW_PORT_MAX_Y && nY >= VIEW_PORT_MIN_Y)
	{
		m_Rect.nDown = nY - VIEWHEIGHT / 2;
		m_Rect.nTop = m_Rect.nDown + VIEWHEIGHT;
	}
	else if (nY > VIEW_PORT_MAX_Y)
	{
		m_Rect.nDown = BIG_MAP_HEIGHT - VIEWHEIGHT;
		m_Rect.nTop = BIG_MAP_HEIGHT;
	}
	else if (nY < VIEW_PORT_MIN_Y)
	{
		m_Rect.nDown = 0;
		m_Rect.nTop = VIEWHEIGHT;
	}

	// 正在加载地图
	if (!m_bPreloading)
		PreLoadMap();

	// 获取当前视角数据
	GetViewData();

	// 投影到屏幕
	g_pScreenData->SetFull(m_ViewData);
}

// 根据角色当前坐标预加载地图
void ViewPort::PreLoadMap()
{
	// 判断是否接近边界
	int nIndexAddX = 0, nIndexAddY = 0;
	// 接近BigMap左边界
	if (m_Rect.nLeft - m_pMapBlock[m_nCurrentBlock].m_Rect.nLeft <= EXCEED_BOUND_WIDTH && m_Rect.nLeft >= MAP_BLOCK_WIDTH)
		nIndexAddX = -1;
	// 接近BigMap右边界
	else if (m_Rect.nRight + EXCEED_BOUND_WIDTH >= m_pMapBlock[m_nCurrentBlock].m_Rect.nRight && m_Rect.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
		nIndexAddX = 1;
	// 接近BigMap下边界
	if (m_Rect.nDown - m_pMapBlock[m_nCurrentBlock].m_Rect.nDown <= EXCEED_BOUND_HEIGHT && m_Rect.nDown >= MAP_BLOCK_HEIGHT)
		nIndexAddY = -1;
	// 接近BigMap上边界
	else if (m_Rect.nTop + EXCEED_BOUND_HEIGHT >= m_pMapBlock[m_nCurrentBlock].m_Rect.nTop && m_Rect.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
		nIndexAddY = 1;

	if (0 == nIndexAddX && 0 == nIndexAddY)
		return;

	// 计算下一个MapBlock的左下角索引
	int nCurIndexX = m_pMapBlock[m_nCurrentBlock].m_nLeftDownMapXIndex;
	int nCurIndexY = m_pMapBlock[m_nCurrentBlock].m_nLeftDownMapYIndex;
	nCurIndexX += nIndexAddX;
	nCurIndexY += nIndexAddY;

	// 进行地图预加载
	if (0 == m_nCurrentBlock)
	{
		m_pMapBlock[1].LoadMapBlocks(nCurIndexX, nCurIndexY);
		m_nCurrentBlock = 1;
		m_bPreloading = false;

		m_pMapBlock[0].m_nLeftDownMapXIndex = nCurIndexX;
		m_pMapBlock[0].m_nLeftDownMapYIndex = nCurIndexY;
	}
	else if (1 == m_nCurrentBlock)
	{
		m_pMapBlock[0].LoadMapBlocks(nCurIndexX, nCurIndexY);
		m_nCurrentBlock = 0;
		m_bPreloading = false;

		m_pMapBlock[1].m_nLeftDownMapXIndex = nCurIndexX;
		m_pMapBlock[1].m_nLeftDownMapYIndex = nCurIndexY;
	}
}

// 获取当前视角数据
void ViewPort::GetViewData()
{
	MapBlock *index = &m_pMapBlock[m_nCurrentBlock];

	// 确定当前视角相对于MapBlock的坐标偏移
	int nStartX = m_Rect.nLeft - index->m_Rect.nLeft;
	int nStartY = m_Rect.nDown - index->m_Rect.nDown;
	int k = 0;

	// 每行字节数
	int nPitch = VIEWWIDTH * 4;

	// 根据坐标读取数据
	for (int i = nStartY; i < nStartY + VIEWHEIGHT; i++)
	{
		memcpy(m_ViewData + k, index->m_pData + i * MAP_BLOCK_WIDTH * 4 * 2 + nStartX * 4, nPitch);
		k += nPitch;
	}
}

//void ViewPort::Blit()
//{
//	memcpy(g_pScreenData->m_pBuffer, m_ViewData, sizeof(m_ViewData));
//}

//// 投影到屏幕
//void ViewPort::Blit2Screen()
//{
//	SetDIBitsToDevice(m_hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, 0, 0, 0, VIEWHEIGHT, m_ViewData, &m_bmpInfo, 0);
//}