//#include "Surface.h"
//
//extern DWORD WINAPI LoadMapImg(LPVOID lpParameter);
//extern HANDLE LoadMapImgThread[4];
//extern HANDLE LoadMapImgMutex[4];
//extern LoadMapImgParam *pLoadMapImgParam;
//extern void CreateMultiMutex(HANDLE handle[]);
//extern void ReleaseMultiMutex(HANDLE handle[]);
//
//Surface::Surface()
//{
//	m_pData = new BYTE[MAP_BLOCK_WIDTH * 4 * MAP_BLOCK_HEIGHT * 4];
//	m_nLeftDownMapIndexX = 1;
//	m_nLeftDownMapIndexY = 1;
//
//	// ���뻥����
//	CreateMultiMutex(LoadMapImgMutex);
//}
//
//
//Surface::~Surface()
//{
//	delete m_pData;
//}
//
//// ƴ��4��BmpͼƬ��data
//void Surface::Paste()
//{
//	// ��Ҫ�Ŀ�BmpͼƬ����ȡ���
//	WaitForMultipleObjects(4, LoadMapImgMutex, true, INFINITE);
//
//	int i, j, k = 0;
//
//	int nPitch = MAP_BLOCK_WIDTH * 4;
//	for (i = 0; i < 2; i++)
//	{
//		for (j = 0; j < MAP_BLOCK_HEIGHT; j++)
//		{
//			memcpy(m_pData + k, m_arrImages[i][0].m_pData + j * nPitch, nPitch);
//			k += nPitch;
//			memcpy(m_pData + k, m_arrImages[i][1].m_pData + j * nPitch, nPitch);
//			k += nPitch;
//		}
//	}
//
//	// �ͷŻ�����
//	ReleaseMultiMutex(LoadMapImgMutex);
//}
//
//// ���ݵ�ͼ�����������ŵ�ͼ��
//void Surface::LoadSurfaces(int nIndexX, int nIndexY)
//{
//	m_nLeftDownMapIndexX = nIndexX;
//	m_nLeftDownMapIndexY = nIndexY;
//
//	//char szFileName[64] = { 0 };
//
//	int i, j, k = 0;
//	for (i = 0; i <= 1; i++)
//	{
//		for (j = 0; j <= 1; j++)
//		{
//			//StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", m_nLeftDownMapYIndex + i, m_nLeftDownMapXIndex + j);
//			//memcpy(pLoadMapImgParam[k].szFileName, szFileName, sizeof(szFileName));
//
//			// �õ���ͼ����
//			StringCbPrintf(pLoadMapImgParam[k].szFileName, sizeof(pLoadMapImgParam[k].szFileName), "BigMap_%d_%d.bmp", m_nLeftDownMapIndexY + i, m_nLeftDownMapIndexX + j);
//			pLoadMapImgParam[k].Img = &m_arrImages[i][j];
//			pLoadMapImgParam[k].index = k;
//			LoadMapImgThread[k] = CreateThread(NULL, 0, LoadMapImg, (LPVOID)&pLoadMapImgParam[k++], 0, NULL);
//		}
//	}
//
//	// ����ͼƬ�����õ���ǰSurface������
//	m_recArea.nLeft = (m_nLeftDownMapIndexY - 1) * MAP_BLOCK_WIDTH;
//	m_recArea.nDown = (m_nLeftDownMapIndexY - 1) * MAP_BLOCK_HEIGHT;
//	m_recArea.nRight = m_recArea.nLeft + MAP_BLOCK_WIDTH * 2;
//	m_recArea.nTop = m_recArea.nDown + MAP_BLOCK_HEIGHT * 2;
//
//	// ��4��MapBlockƴ��
//	Paste();
//}