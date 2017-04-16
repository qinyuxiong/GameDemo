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

// ��ȡBmpͼ��
void Image::LoadBmpImg(const char *pFilePath)
{
	// �����ƴ�BMP�ļ�
	FILE *pFile = fopen(pFilePath, "rb");
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
	m_pData = new BYTE[m_nPitch * m_nHeight];
	fread(&m_pData[0], 1, m_nPitch * m_nHeight, pFile);
	fclose(pFile);
}


// ��ȡPngͼ��
void Image::LoadPngImg(const char *pFilePath)
{
	// �����ƴ�Png�ļ� 
	//����vs��ô��ȫ�Ե�ԭ�򣬲���ʹ��fopen���������fopen_s���棻  
	FILE*imgP;
	fopen_s(&imgP, pFilePath, "rb");//�������ö����ƶ�ȡ��read-r��binary-b����ΪֻŪr���������Ū�˺����Ǹ�������������ŷ�������������⣡��  
	if (imgP == NULL)return;
	fseek(imgP, 0L, SEEK_END);
	long size = ftell(imgP);
	//byte*imgbuf = new byte[size + 1];
	fseek(imgP, 0x0L, SEEK_SET);//ͼƬԴ  
	m_pData = new BYTE[size];
	fread(&m_pData, sizeof(m_pData[0]), size, imgP);
	/*for (int j = 0; j < size; j++)
	cout << (imgbuf[j] & 0xff) << ":";*/
	fclose(imgP);
}

// ��ȡĳһ��ĳһ�е�����
void Image::GetByte(int x, int y, Pixel &pixel)
{
	if (x <= m_nHeight && x >= 0 && y <= m_nWidth && y >= 0)
	{
		pixel.r = m_pData[x * m_nPitch + y * 4 + 2];
		pixel.g = m_pData[x * m_nPitch + y * 4 + 1];
		pixel.b = m_pData[x * m_nPitch + y * 4];
	}
}

// ��ȡBmpͼ�������ָ��
BYTE *Image::GetData()
{
	return m_pData;
}