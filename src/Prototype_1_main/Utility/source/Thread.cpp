#include "MapBlock.h"

DWORD WINAPI LoadMapImg(LPVOID lpParameter);
HANDLE LoadMapImgThread[4];
HANDLE LoadMapImgMutex[4];
LoadMapImgParam *pLoadMapImgParam = new LoadMapImgParam[4];
void CreateMultiMutex(HANDLE handle[]);

// 读取Bmp图片线程函数 
DWORD WINAPI LoadMapImg(LPVOID lpParameter)
{
	LoadMapImgParam *pParam = (LoadMapImgParam *)lpParameter;
	WaitForSingleObject(LoadMapImgMutex[pParam->index], INFINITE);
	(*pParam->Img).LoadImg(pParam->szFileName);
	ReleaseMutex(LoadMapImgMutex[pParam->index]);
	return 0;
}

// 创建多个Mutex
void CreateMultiMutex(HANDLE handle[])
{
	for (int i = 0; i < sizeof(handle); i++)
		handle[i] = CreateMutex(NULL, FALSE, NULL);
}

// 释放多个Mutex
void ReleaseMultiMutex(HANDLE handle[])
{
	for (int i = 0; i < sizeof(handle); i++)
		ReleaseMutex(handle[i]);
}