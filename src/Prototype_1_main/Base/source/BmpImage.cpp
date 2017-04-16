#include "BmpImage.h"
#include "PreCompile.h"

BmpImage::BmpImage()
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_nPitch = 0;
	m_pData = NULL;
}

BmpImage::~BmpImage()
{
	delete m_pData;
}

// 读取Bmp图像
void BmpImage::LoadImg(const char *filePath)
{
	// 二进制打开BMP文件
	FILE *pFile = fopen(filePath, "rb");
	if (0 == pFile)
		return;

	// 读取BMP文件头
	BITMAPFILEHEADER fileHeader;
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);

	// 文件类型是否为BMP
	if (BITMAP != fileHeader.bfType)
		return;

	// 读取信息头
	BITMAPINFOHEADER infoHeader;
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	// 是否为32位BMP
	if (BMP_TYPE_32 != infoHeader.biBitCount)
		return;
	// 读取长宽
	m_nHeight = infoHeader.biHeight;
	m_nWidth = infoHeader.biWidth;

	// 获取每行字节数
	m_nPitch = (m_nWidth*infoHeader.biBitCount / 8) / 4 * 4;

	// 分配内存
	m_pData = new unsigned char[m_nPitch * m_nHeight];
	fread(&m_pData[0], 1, m_nPitch * m_nHeight, pFile);
	fclose(pFile);
}

// 获取某一行某一列的像素
void BmpImage::GetByte(int x, int y, Pixel &pixel)
{
	if (x <= m_nHeight && x >= 0 && y <= m_nWidth && y >= 0)
	{
		pixel.r = m_pData[x * m_nPitch + y * 4 + 2];
		pixel.g = m_pData[x * m_nPitch + y * 4 + 1];
		pixel.b = m_pData[x * m_nPitch + y * 4];
	}
}

// 获取Bmp图像的数据指针
unsigned char *BmpImage::GetData()
{
	return m_pData;
}