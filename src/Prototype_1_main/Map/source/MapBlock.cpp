#include "MapBlock.h"

extern DWORD WINAPI LoadMapImg(LPVOID lpParameter);
extern HANDLE LoadMapImgThread[4];
extern HANDLE LoadMapImgMutex[4];
extern LoadMapImgParam *pLoadMapImgParam;
extern void CreateMultiMutex(HANDLE handle[]);
extern void ReleaseMultiMutex(HANDLE handle[]);

MapBlock::MapBlock()
{
	m_pData = new unsigned char[MAP_BLOCK_WIDTH * MAP_BLOCK_HEIGHT * 4 * 4];
	m_nLeftDownMapXIndex = 1;
	m_nLeftDownMapYIndex = 1;

	// ���뻥����
	CreateMultiMutex(LoadMapImgMutex);
}


MapBlock::~MapBlock()
{
	delete m_pData;
}

// ƴ��4��BmpͼƬ��data
void MapBlock::MakeJoint()
{
	// ��Ҫ�Ŀ�BmpͼƬ����ȡ���
	WaitForMultipleObjects(4, LoadMapImgMutex, true, INFINITE);

	int i, l, k = 0;

	int nPitch = MAP_BLOCK_WIDTH * 4;
	for (i = 0; i < 2; i++)
	{
		for (l = 0; l < MAP_BLOCK_HEIGHT; l++)
		{
			memcpy(m_pData + k, m_FourImages[i][0].m_pData + l * nPitch, nPitch);
			k += nPitch;
			memcpy(m_pData + k, m_FourImages[i][1].m_pData + l * nPitch, nPitch);
			k += nPitch;
		}
	}

	// �ͷŻ�����
	ReleaseMultiMutex(LoadMapImgMutex);
}

// ���ݵ�ͼ�����������ŵ�ͼ��
void MapBlock::LoadMapBlocks(int nIndexX, int nIndexY)
{
	m_nLeftDownMapXIndex = nIndexX;
	m_nLeftDownMapYIndex = nIndexY;

	// �õ���ͼ����
	char szFileName[64] = { 0 };

	int i, j, k = 0;
	for (i = 0; i <= 1; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			StringCbPrintf(szFileName, sizeof(szFileName), "BigMap_%d_%d.bmp", m_nLeftDownMapYIndex + i, m_nLeftDownMapXIndex + j);
			memcpy(pLoadMapImgParam[k].szFileName, szFileName, sizeof(szFileName));
			pLoadMapImgParam[k].Img = &m_FourImages[i][j];
			pLoadMapImgParam[k].index = k;
			LoadMapImgThread[k] = CreateThread(NULL, 0, LoadMapImg, (LPVOID)&pLoadMapImgParam[k++], 0, NULL);
		}
	}

	// ����ͼƬ�����õ���ǰMapBlock������
	m_Rect.nLeft = (m_nLeftDownMapXIndex - 1) * MAP_BLOCK_WIDTH;
	m_Rect.nDown = (m_nLeftDownMapYIndex - 1) * MAP_BLOCK_HEIGHT;
	m_Rect.nRight = m_Rect.nLeft + MAP_BLOCK_WIDTH * 2;
	m_Rect.nTop = m_Rect.nDown + MAP_BLOCK_HEIGHT * 2;

	MakeJoint();
}