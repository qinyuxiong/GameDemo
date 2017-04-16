#ifndef _BMPIMAGE_H_
#define _BMPIMAGE_H_

// ���ؽṹ�� 
typedef struct _Pixel
{
	char r;
	char g;
	char b;
} Pixel;

// Bmpͼ��ṹ�� 
class BmpImage
{
public:
	int m_nWidth;              // ͼ�����
	int m_nHeight;
	int m_nPitch;              // ͼ��ÿ���ֽ���
	unsigned char *m_pData;    // ͼ��data

	BmpImage();
	~BmpImage();

	// ��ȡĳһ��ĳһ�е�����
	void GetByte(int x, int y, Pixel &pixel);
	
	// ��ȡBmpͼ��
	void LoadImg(const char *pFile);

	unsigned char *GetData();
};

#endif