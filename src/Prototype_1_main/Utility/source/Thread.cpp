#include "MapBlock.h"

DWORD WINAPI LoadMapImg(LPVOID lpParameter);
HANDLE LoadMapImgThread[4];
HANDLE LoadMapImgMutex[4];
LoadMapImgParam *pLoadMapImgParam = new LoadMapImgParam[4];
void CreateMultiMutex(HANDLE handle[]);

// ��ȡBmpͼƬ�̺߳��� 
DWORD WINAPI LoadMapImg(LPVOID lpParameter)
{
	LoadMapImgParam *pParam = (LoadMapImgParam *)lpParameter;
	WaitForSingleObject(LoadMapImgMutex[pParam->index], INFINITE);
	(*pParam->Img).LoadImg(pParam->szFileName);
	ReleaseMutex(LoadMapImgMutex[pParam->index]);
	return 0;
}

// �������Mutex
void CreateMultiMutex(HANDLE handle[])
{
	for (int i = 0; i < sizeof(handle); i++)
		handle[i] = CreateMutex(NULL, FALSE, NULL);
}

// �ͷŶ��Mutex
void ReleaseMultiMutex(HANDLE handle[])
{
	for (int i = 0; i < sizeof(handle); i++)
		ReleaseMutex(handle[i]);
}