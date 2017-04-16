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

// ��������
void ViewPort::SetHWND(HWND hwnd)
{
	m_hWnd = hwnd;
	m_hdc = GetDC(m_hWnd);

	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
}

// ������������ȡ��ʼBlockMap
void ViewPort::InitView(int nPlayerStartX, int nPlayerStartY)
{
	int n = nPlayerStartX / MAP_BLOCK_WIDTH;
	int m = nPlayerStartY / MAP_BLOCK_HEIGHT;

	// �����BlockMapӦ��Ϊͬһ��
	m_pMapBlock[0].LoadMapBlocks(n, m);
	m_pMapBlock[1].LoadMapBlocks(n, m);
}

// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
void ViewPort::MoveCamera(int nX, int nY)
{
	// ���ݵ�ǰ�������������ӿڷ�Χ
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

	// ���ڼ��ص�ͼ
	if (!m_bPreloading)
		PreLoadMap();

	// ��ȡ��ǰ�ӽ�����
	GetViewData();

	// ͶӰ����Ļ
	g_pScreenData->SetFull(m_ViewData);
}

// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
void ViewPort::PreLoadMap()
{
	// �ж��Ƿ�ӽ��߽�
	int nIndexAddX = 0, nIndexAddY = 0;
	// �ӽ�BigMap��߽�
	if (m_Rect.nLeft - m_pMapBlock[m_nCurrentBlock].m_Rect.nLeft <= EXCEED_BOUND_WIDTH && m_Rect.nLeft >= MAP_BLOCK_WIDTH)
		nIndexAddX = -1;
	// �ӽ�BigMap�ұ߽�
	else if (m_Rect.nRight + EXCEED_BOUND_WIDTH >= m_pMapBlock[m_nCurrentBlock].m_Rect.nRight && m_Rect.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
		nIndexAddX = 1;
	// �ӽ�BigMap�±߽�
	if (m_Rect.nDown - m_pMapBlock[m_nCurrentBlock].m_Rect.nDown <= EXCEED_BOUND_HEIGHT && m_Rect.nDown >= MAP_BLOCK_HEIGHT)
		nIndexAddY = -1;
	// �ӽ�BigMap�ϱ߽�
	else if (m_Rect.nTop + EXCEED_BOUND_HEIGHT >= m_pMapBlock[m_nCurrentBlock].m_Rect.nTop && m_Rect.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
		nIndexAddY = 1;

	if (0 == nIndexAddX && 0 == nIndexAddY)
		return;

	// ������һ��MapBlock�����½�����
	int nCurIndexX = m_pMapBlock[m_nCurrentBlock].m_nLeftDownMapXIndex;
	int nCurIndexY = m_pMapBlock[m_nCurrentBlock].m_nLeftDownMapYIndex;
	nCurIndexX += nIndexAddX;
	nCurIndexY += nIndexAddY;

	// ���е�ͼԤ����
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

// ��ȡ��ǰ�ӽ�����
void ViewPort::GetViewData()
{
	MapBlock *index = &m_pMapBlock[m_nCurrentBlock];

	// ȷ����ǰ�ӽ������MapBlock������ƫ��
	int nStartX = m_Rect.nLeft - index->m_Rect.nLeft;
	int nStartY = m_Rect.nDown - index->m_Rect.nDown;
	int k = 0;

	// ÿ���ֽ���
	int nPitch = VIEWWIDTH * 4;

	// ���������ȡ����
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

//// ͶӰ����Ļ
//void ViewPort::Blit2Screen()
//{
//	SetDIBitsToDevice(m_hdc, 0, 0, VIEWWIDTH, VIEWHEIGHT, 0, 0, 0, VIEWHEIGHT, m_ViewData, &m_bmpInfo, 0);
//}