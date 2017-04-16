#include "GlobalFunc.h"

DWORD WINAPI LoadResProc(LPVOID lpParameter)
{
	ResParam *index = (ResParam*)lpParameter;

	int nLeftDownMapXIndex = index->nLeftDownMapXIndex;
	int nLeftDownMapYIndex = index->nLeftDownMapYIndex;
	BmpImage(*m_FourImages)[2] = index->m_FourImages;

	// 得到地图名称
	char szFileName[64] = { 0 };
	StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", nLeftDownMapYIndex, nLeftDownMapXIndex);
	m_FourImages[0][0].LoadImg(szFileName);
	StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", nLeftDownMapYIndex, nLeftDownMapXIndex + 1);
	m_FourImages[0][1].LoadImg(szFileName);
	StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", nLeftDownMapYIndex + 1, nLeftDownMapXIndex);
	m_FourImages[1][0].LoadImg(szFileName);
	StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", nLeftDownMapYIndex + 1, nLeftDownMapXIndex + 1);
	m_FourImages[1][1].LoadImg(szFileName);

	return 0;
}