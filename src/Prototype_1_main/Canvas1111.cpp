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
////// ��������
////void Canvas::SetHWND(HWND hwnd)
////{
////	m_hWnd = hwnd;
////	m_hdc = GetDC(m_hWnd);
////
////	m_bmpInfo = { { sizeof(BITMAPINFOHEADER), VIEWWIDTH, VIEWHEIGHT, 1, 32, BI_RGB, VIEWWIDTH * VIEWHEIGHT * 4, 0, 0, 0, 0 } };
////}
//
//// ������������ȡ��ʼBlockMap
//void Canvas::Init(int nPlayerStartX, int nPlayerStartY)
//{
//	int n = nPlayerStartX / MAP_BLOCK_WIDTH;
//	int m = nPlayerStartY / MAP_BLOCK_HEIGHT;
//
//	// �����BlockMapӦ��Ϊͬһ��
//	m_pSurface[0].LoadSurfaces(n, m);
//	//m_pSurface[1].LoadSurfaces(n, m);
//}
//
//// ���ݽ�ɫ��ǰ�����ƶ��Ӵ�
//void Canvas::MoveCamera(int nX, int nY)
//{
//	// ���ݵ�ǰ�������������ӿڷ�Χ
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
//	// ���ڼ��ص�ͼ
//	if (!m_bPreloading)
//		PreLoadMap();
//
//	// ��ȡ��ǰ�ӽ�����
//	GetViewData();
//
//	// ͶӰ����Ļ
//	g_pScreenData->SetFull(m_ViewData);
//}
//
//// ���ݽ�ɫ��ǰ����Ԥ���ص�ͼ
//void Canvas::PreLoadMap()
//{
//	// �ж��Ƿ�ӽ��߽�
//	int nIndexAddX = 0, nIndexAddY = 0;
//	// �ӽ�BigMap��߽�
//	if (m_recArea.nLeft - m_pSurface[m_nCurrentBlock].m_recArea.nLeft <= EXCEED_BOUND_WIDTH && m_recArea.nLeft >= MAP_BLOCK_WIDTH)
//		nIndexAddX = -1;
//	// �ӽ�BigMap�ұ߽�
//	else if (m_recArea.nRight + EXCEED_BOUND_WIDTH >= m_pSurface[m_nCurrentBlock].m_recArea.nRight && m_recArea.nRight <= BIG_MAP_WIDTH - MAP_BLOCK_WIDTH)
//		nIndexAddX = 1;
//	// �ӽ�BigMap�±߽�
//	if (m_recArea.nDown - m_pSurface[m_nCurrentBlock].m_recArea.nDown <= EXCEED_BOUND_HEIGHT && m_recArea.nDown >= MAP_BLOCK_HEIGHT)
//		nIndexAddY = -1;
//	// �ӽ�BigMap�ϱ߽�
//	else if (m_recArea.nTop + EXCEED_BOUND_HEIGHT >= m_pSurface[m_nCurrentBlock].m_recArea.nTop && m_recArea.nTop <= BIG_MAP_HEIGHT - MAP_BLOCK_HEIGHT)
//		nIndexAddY = 1;
//
//	if (0 == nIndexAddX && 0 == nIndexAddY)
//		return;
//
//	// ������һ��Surface�����½�����
//	int nCurIndexX = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexX;
//	int nCurIndexY = m_pSurface[m_nCurrentBlock].m_nLeftDownMapIndexY;
//	nCurIndexX += nIndexAddX;
//	nCurIndexY += nIndexAddY;
//
//	// ���е�ͼԤ����
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
//// ��ȡ��ǰ�ӽ�����
//void Canvas::GetViewData()
//{
//	Surface *index = &m_pSurface[m_nCurrentBlock];
//
//	// ȷ����ǰ�ӽ������Surface������ƫ��
//	int nStartX = m_recArea.nLeft - index->m_recArea.nLeft;
//	int nStartY = m_recArea.nDown - index->m_recArea.nDown;
//	int k = 0;
//
//	// ÿ���ֽ���
//	int nPitch = VIEWWIDTH * 4;
//
//	// ���������ȡ����
//	for (int i = nStartY; i < nStartY + VIEWHEIGHT; i++)
//	{
//		memcpy(m_ViewData + k, index->m_pData + i * MAP_BLOCK_WIDTH * 4 * 2 + nStartX * 4, nPitch);
//		k += nPitch;
//	}
//}