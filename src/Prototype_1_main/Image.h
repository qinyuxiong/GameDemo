#ifndef _Image_H_
#define _Image_H_

#include <Windows.h>

// ���ؽṹ�� 
typedef struct _Pixel
{
	char r;
	char g;
	char b;
} Pixel;

// Bmpͼ��ṹ�� 
class Image
{
public:
	int m_nWidth;              // ͼ�����
	int m_nHeight;
	int m_nPitch;              // ͼ��ÿ���ֽ���
	BYTE *m_pData;    // ͼ��data

	Image();
	~Image();

	// ��ȡĳһ��ĳһ�е�����
	void GetByte(int x, int y, Pixel &pixel);
	
	// ��ȡBmpͼ��
	void LoadBmpImg(const char *pFilePath);

	// ��ȡPngͼ��
	void LoadPngImg(const char *pFilePath);

	BYTE *GetData();
};

#endif