#include "MapMgr.h"

MapMgr::MapMgr()
{
	m_bPreloading = false;
	m_nCurrentBlock = 0;
	m_pMapData = new BYTE[MAP_BLOCK_WIDTH * 4 * MAP_BLOCK_HEIGHT * 4];
}

MapMgr::~MapMgr()
{
	if (m_pMapData != NULL)
		delete m_pMapData;
}

// 根据玩家坐标读取初始BlockMap(先设定读取左下角)
void MapMgr::Init()
{
	m_recMaxMapRange.nLeft = 0;
	m_recMaxMapRange.nRight = 10500;
	m_recMaxMapRange.nDown = 0;
	m_recMaxMapRange.nTop = 8100;

	// 最初两BlockMap应该为同一个
	m_pSurface[0].LoadSurfaces(1, 1);
	m_pSurface[0].Paste(m_pMapData);

	m_recArea.nLeft = 0;
	m_recArea.nRight = VIEWWIDTH;
	m_recArea.nDown = 0;
	m_recArea.nTop = VIEWHEIGHT;
}

// 根据角色当前坐标移动视窗
void MapMgr::MoveCamera(int nX, int nY)
{
	CalViewArea(nX, nY);

	int nOffsetX = 0;
	int nOffsetY = 0;

	// 如果接近边界则正在加载地图
	if (ApproachBoundary(nOffsetX, nOffsetY) && !m_bPreloading)
	{
		PreLoadMap(nOffsetX, nOffsetY);

		// 得到加载的地图拼接后的数据
		m_pSurface[m_nCurrentBlock].Paste(m_pMapData);
	}
}

// 计算出当前需要显示的地图区域
void MapMgr::CalViewArea(int nX, int nY)
{
	// 根据当前玩家坐标点计算出地图范围
	if (nX <= VIEW_PORT_MAX_X && nX >= VIEW_PORT_MIN_X)
	{
		m_recArea.nLeft = nX - VIEWWIDTH / 2;
		m_recArea.nRight = m_recArea.nLeft + VIEWWIDTH;
	}
	else if (nX > VIEW_PORT_MAX_X)
	{
		m_recArea.nLeft = BIG_MAP_WIDTH - VIEWWIDTH;
		m_recArea.nRight = BIG_MAP_WIDTH;
	}
	else if (nX < VIEW_PORT_MIN_X)
	{
		m_recArea.nLeft = 0;
		m_recArea.nRight = VIEWWIDTH;
	}
	if (nY <= VIEW_PORT_MAX_Y && nY >= VIEW_PORT_MIN_Y)
	{
		m_recArea.nDown = nY - VIEWHEIGHT / 2;
		m_recArea.nTop = m_recArea.nDown + VIEWHEIGHT;
	}
	else if (nY > VIEW_PORT_MAX_Y)
	{
		m_recArea.nDown = BIG_MAP_HEIGHT - VIEWHEIGHT;
		m_recArea.nTop = BIG_MAP_HEIGHT;
	}
	else if (nY < VIEW_PORT_MIN_Y)
	{
		m_recArea.nDown = 0;
		m_recArea.nTop = VIEWHEIGHT;
	}
}

// 判断是否接近边界
BOOL MapMgr::ApproachBoundary(int &nOffsetX, int &nOffsetY)
{
	// 接近BigMap左边界
	if (m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft <= EXCEED_BOUND_WIDTH && m_recArea.nLeft >= MAP_BLOCK_WIDTH)
		nOffsetX = -1;
	// 接近BigMap右边界
	else if (m_recArea.nRight + EXCEED_BOUND_WIDTH >= m_pSurface[m_nCurrentBlock].m_recArea.nRight && m_recArea.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
		nOffsetX = 1;
	// 接近BigMap下边界
	if (m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown <= EXCEED_BOUND_HEIGHT && m_recArea.nDown >= MAP_BLOCK_HEIGHT)
		nOffsetY = -1;
	// 接近BigMap上边界
	else if (m_recArea.nTop + EXCEED_BOUND_HEIGHT >= m_pSurface[m_nCurrentBlock].m_recArea.nTop && m_recArea.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
		nOffsetY = 1;

	if (0 == nOffsetX && 0 == nOffsetY)
		return FALSE;
	else
		return TRUE;
}

// 根据角色当前坐标预加载地图
void MapMgr::PreLoadMap(int nOffsetX, int nOffsetY)
{
	// 计算下一个Surface的左下角索引
	int nCurIndexX = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexX;
	int nCurIndexY = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexY;
	nCurIndexX += nOffsetX;
	nCurIndexY += nOffsetY;

	// 进行地图预加载
	if (0 == m_nCurrentBlock)
	{
		m_pSurface[1].LoadSurfaces(nCurIndexX, nCurIndexY);
		m_nCurrentBlock = 1;
		m_bPreloading = false;

		m_pSurface[0].m_nLeftDownMapIndexX = nCurIndexX;
		m_pSurface[0].m_nLeftDownMapIndexY = nCurIndexY;
	}
	else if (1 == m_nCurrentBlock)
	{
		m_pSurface[0].LoadSurfaces(nCurIndexX, nCurIndexY);
		m_nCurrentBlock = 0;
		m_bPreloading = false;

		m_pSurface[1].m_nLeftDownMapIndexX = nCurIndexX;
		m_pSurface[1].m_nLeftDownMapIndexY = nCurIndexY;
	}
}

// 绘制
void MapMgr::Draw(Canvas *pCanvas)
{
	// 确定当前视角相对于MapBuffer的坐标偏移
	int nStartX = m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft > 0 ? m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft : 0;
	int nStartY = m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown > 0 ? m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown : 0;
	//int nSrcOffset = 0;

	//// 每行字节数
	//int nPitch = VIEWWIDTH * 4;

	//// 根据坐标读取数据
	//for (int i = nStartY; i < nStartY + VIEWHEIGHT; i++)
	//{
	//	memcpy(pCanvas->GetSurface() + nSrcOffset, m_pMapData + i * MAP_BLOCK_WIDTH * 4 * 2 + nStartX * 4, nPitch);
	//	nSrcOffset += nPitch;
	//}

	//void Canvas::Draw(int nDsStartX, int nDstStartY, int nSrcSartY, int nSrcEndY, int nSrcStartX, int nSrcSendX, int nSrcPitch, BYTE *pSrcData)

	pCanvas->Draw(0, 0, nStartY, nStartY + VIEWHEIGHT, nStartX, nStartX + VIEWWIDTH, MAP_BLOCK_WIDTH * 4 * 2, m_pMapData, DRAW_MAP);
	//pCanvas->DrawMap(m_pMapData, nStartX, nStartY);
}

MapMgr *g_pMapMgr;
