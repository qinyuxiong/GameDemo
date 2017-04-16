#ifndef _Image_H_
#define _Image_H_

#include <Windows.h>

// 像素结构体 
typedef struct _Pixel
{
	char r;
	char g;
	char b;
} Pixel;

// Bmp图像结构体 
class Image
{
public:
	int m_nWidth;              // 图像宽、高
	int m_nHeight;
	int m_nPitch;              // 图像每行字节数
	BYTE *m_pData;    // 图像data

	Image();
	~Image();

	// 获取某一行某一列的像素
	void GetByte(int x, int y, Pixel &pixel);
	
	// 读取Bmp图像
	void LoadBmpImg(const char *pFilePath);

	// 读取Png图像
	void LoadPngImg(const char *pFilePath);

	BYTE *GetData();
};

#endif