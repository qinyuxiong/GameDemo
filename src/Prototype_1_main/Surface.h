//#ifndef _Surface_H_
//#define _Surface_H_
//
//#include "BmpImage.h"
//#include "PreCompile.h"
//#include "Utility.h"
//
//// �ĸ�BmpͼƬƴ�ɵ�һ����ͼBlock
//class Surface
//{
//public:
//	BmpImage m_arrImages[LITTLE_MAP_BLOCKS_ROW][LITTLE_MAP_BLOCKS_COL];       // �ĸ�BmpͼƬ
//	BYTE *m_pData;                                                            // �ĸ�BmpͼƬƴ�ӳɵ�Surface���� 
//	Rect m_recArea;                                                           // Surfaceռ���ͼ������
//	int m_nLeftDownMapIndexX;                 	                              // ���½ǵ�ͼ�������
//	int m_nLeftDownMapIndexY;
//
//	Surface();
//	~Surface();
//
//	// ���ݵ�ͼ�����������ŵ�ͼ��
//	void LoadSurfaces(int nIndexX, int nIndexY);
//
//	// ƴ��4��Block��ͼ��һ���Block
//	void Paste();
//};
//
//#endif