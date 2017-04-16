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

// ��ȡBmpͼ��
void BmpImage::LoadImg(const char *filePath)
{
	// �����ƴ�BMP�ļ�
	FILE *pFile = fopen(filePath, "rb");
	if (0 == pFile)
		return;

	// ��ȡBMP�ļ�ͷ
	BITMAPFILEHEADER fileHeader;
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);

	// �ļ������Ƿ�ΪBMP
	if (BITMAP != fileHeader.bfType)
		return;

	// ��ȡ��Ϣͷ
	BITMAPINFOHEADER infoHeader;
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	// �Ƿ�Ϊ32λBMP
	if (BMP_TYPE_32 != infoHeader.biBitCount)
		return;
	// ��ȡ����
	m_nHeight = infoHeader.biHeight;
	m_nWidth = infoHeader.biWidth;

	// ��ȡÿ���ֽ���
	m_nPitch = (m_nWidth*infoHeader.biBitCount / 8) / 4 * 4;

	// �����ڴ�
	m_pData = new unsigned char[m_nPitch * m_nHeight];
	fread(&m_pData[0], 1, m_nPitch * m_nHeight, pFile);
	fclose(pFile);
}

// ��ȡĳһ��ĳһ�е�����
void BmpImage::GetByte(int x, int y, Pixel &pixel)
{
	if (x <= m_nHeight && x >= 0 && y <= m_nWidth && y >= 0)
	{
		pixel.r = m_pData[x * m_nPitch + y * 4 + 2];
		pixel.g = m_pData[x * m_nPitch + y * 4 + 1];
		pixel.b = m_pData[x * m_nPitch + y * 4];
	}
}

// ��ȡBmpͼ�������ָ��
unsigned char *BmpImage::GetData()
{
	return m_pData;
}