#ifndef _BMPIMAGE_H_
#define _BMPIMAGE_H_

// 像素结构体 
typedef struct _Pixel
{
	char r;
	char g;
	char b;
} Pixel;

// Bmp图像结构体 
class BmpImage
{
public:
	int m_nWidth;              // 图像宽、高
	int m_nHeight;
	int m_nPitch;              // 图像每行字节数
	unsigned char *m_pData;    // 图像data

	BmpImage();
	~BmpImage();

	// 获取某一行某一列的像素
	void GetByte(int x, int y, Pixel &pixel);
	
	// 读取Bmp图像
	void LoadImg(const char *pFile);

	unsigned char *GetData();
};

#endif