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
//	// 申请互斥量
//	CreateMultiMutex(LoadMapImgMutex);
//}
//
//
//Surface::~Surface()
//{
//	delete m_pData;
//}
//
//// 拼接4块Bmp图片到data
//void Surface::Paste()
//{
//	// 需要四块Bmp图片都读取完成
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
//	// 释放互斥量
//	ReleaseMultiMutex(LoadMapImgMutex);
//}
//
//// 根据地图索引加载四张地图块
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
//			// 得到地图名称
//			StringCbPrintf(pLoadMapImgParam[k].szFileName, sizeof(pLoadMapImgParam[k].szFileName), "BigMap_%d_%d.bmp", m_nLeftDownMapIndexY + i, m_nLeftDownMapIndexX + j);
//			pLoadMapImgParam[k].Img = &m_arrImages[i][j];
//			pLoadMapImgParam[k].index = k;
//			LoadMapImgThread[k] = CreateThread(NULL, 0, LoadMapImg, (LPVOID)&pLoadMapImgParam[k++], 0, NULL);
//		}
//	}
//
//	// 根据图片索引得到当前Surface的区域
//	m_recArea.nLeft = (m_nLeftDownMapIndexY - 1) * MAP_BLOCK_WIDTH;
//	m_recArea.nDown = (m_nLeftDownMapIndexY - 1) * MAP_BLOCK_HEIGHT;
//	m_recArea.nRight = m_recArea.nLeft + MAP_BLOCK_WIDTH * 2;
//	m_recArea.nTop = m_recArea.nDown + MAP_BLOCK_HEIGHT * 2;
//
//	// 将4个MapBlock拼接
//	Paste();
//}