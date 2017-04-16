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

// ������������ȡ��ʼBlockMap(���趨��ȡ���½�)
void MapMgr::Init()
{
	m_recMaxMapRange.nLeft = 0;
	m_recMaxMapRange.nRight = 10500;
	m_recMaxMapRange.nDown = 0;
	m_recMaxMapRange.nTop = 8100;

	// �����BlockMapӦ��Ϊͬһ��
	m_pSurface[0].LoadSurfaces(1, 1);
	m_pSurface[0].Paste(m_pMapData);

	m_recArea.nLeft = 0;
	m_recArea.nRight = VIEWWIDTH;
	m_recArea.nDown = 0;
	m_recArea.nTop = VIEWHEIGHT;
}

// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
void MapMgr::MoveCamera(int nX, int nY)
{
	CalViewArea(nX, nY);

	int nOffsetX = 0;
	int nOffsetY = 0;

	// ����ӽ��߽������ڼ��ص�ͼ
	if (ApproachBoundary(nOffsetX, nOffsetY) && !m_bPreloading)
	{
		PreLoadMap(nOffsetX, nOffsetY);

		// �õ����صĵ�ͼƴ�Ӻ������
		m_pSurface[m_nCurrentBlock].Paste(m_pMapData);
	}
}

// �������ǰ��Ҫ��ʾ�ĵ�ͼ����
void MapMgr::CalViewArea(int nX, int nY)
{
	// ���ݵ�ǰ��������������ͼ��Χ
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

// �ж��Ƿ�ӽ��߽�
BOOL MapMgr::ApproachBoundary(int &nOffsetX, int &nOffsetY)
{
	// �ӽ�BigMap��߽�
	if (m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft <= EXCEED_BOUND_WIDTH && m_recArea.nLeft >= MAP_BLOCK_WIDTH)
		nOffsetX = -1;
	// �ӽ�BigMap�ұ߽�
	else if (m_recArea.nRight + EXCEED_BOUND_WIDTH >= m_pSurface[m_nCurrentBlock].m_recArea.nRight && m_recArea.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
		nOffsetX = 1;
	// �ӽ�BigMap�±߽�
	if (m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown <= EXCEED_BOUND_HEIGHT && m_recArea.nDown >= MAP_BLOCK_HEIGHT)
		nOffsetY = -1;
	// �ӽ�BigMap�ϱ߽�
	else if (m_recArea.nTop + EXCEED_BOUND_HEIGHT >= m_pSurface[m_nCurrentBlock].m_recArea.nTop && m_recArea.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
		nOffsetY = 1;

	if (0 == nOffsetX && 0 == nOffsetY)
		return FALSE;
	else
		return TRUE;
}

// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
void MapMgr::PreLoadMap(int nOffsetX, int nOffsetY)
{
	// ������һ��Surface�����½�����
	int nCurIndexX = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexX;
	int nCurIndexY = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexY;
	nCurIndexX += nOffsetX;
	nCurIndexY += nOffsetY;

	// ���е�ͼԤ����
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

// ����
void MapMgr::Draw(Canvas *pCanvas)
{
	// ȷ����ǰ�ӽ������MapBuffer������ƫ��
	int nStartX = m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft > 0 ? m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft : 0;
	int nStartY = m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown > 0 ? m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown : 0;
	//int nSrcOffset = 0;

	//// ÿ���ֽ���
	//int nPitch = VIEWWIDTH * 4;

	//// ���������ȡ����
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
