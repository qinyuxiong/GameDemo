#include "Image.h"
#include "PreCompile.h"

Image::Image()
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_nPitch = 0;
	m_pData = NULL;
}

Image::~Image()
{
	delete m_pData;
}

// 读取Bmp图像
void Image::LoadBmpImg(const char *pFilePath)
{
	// 二进制打开BMP文件
	FILE *pFile = fopen(pFilePath, "rb");
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
	m_pData = new BYTE[m_nPitch * m_nHeight];
	fread(&m_pData[0], 1, m_nPitch * m_nHeight, pFile);
	fclose(pFile);
}


// 读取Png图像
void Image::LoadPngImg(const char *pFilePath)
{
	// 二进制打开Png文件 
	//由于vs甚么安全性的原因，不让使用fopen，用下面的fopen_s代替；  
	FILE*imgP;
	fopen_s(&imgP, pFilePath, "rb");//这里是用二进制读取，read-r；binary-b；因为只弄r结果出错！！弄了后面那个的再来看这个才发现是这个的问题！！  
	if (imgP == NULL)return;
	fseek(imgP, 0L, SEEK_END);
	long size = ftell(imgP);
	//byte*imgbuf = new byte[size + 1];
	fseek(imgP, 0x0L, SEEK_SET);//图片源  
	m_pData = new BYTE[size];
	fread(&m_pData, sizeof(m_pData[0]), size, imgP);
	/*for (int j = 0; j < size; j++)
	cout << (imgbuf[j] & 0xff) << ":";*/
	fclose(imgP);
}

// 获取某一行某一列的像素
void Image::GetByte(int x, int y, Pixel &pixel)
{
	if (x <= m_nHeight && x >= 0 && y <= m_nWidth && y >= 0)
	{
		pixel.r = m_pData[x * m_nPitch + y * 4 + 2];
		pixel.g = m_pData[x * m_nPitch + y * 4 + 1];
		pixel.b = m_pData[x * m_nPitch + y * 4];
	}
}

// 获取Bmp图像的数据指针
BYTE *Image::GetData()
{
	return m_pData;
}