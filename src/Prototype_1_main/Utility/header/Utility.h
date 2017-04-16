#ifndef _UTILITY_H_
#define _UTILITY_H_

class BmpImage;

// ����ṹ��
typedef struct AREA
{
	int nLeft;
	int nRight;
	int nTop;
	int nDown;
} Rect;

typedef struct _POINT
{
	int nX;
	int nY;
} Point;

typedef struct MSGPARAM
{
	Point pt;
} MsgParam;

// �̲߳���
class LoadMapImgParam
{
public:
	char szFileName[64];             // BmpͼƬ��
	BmpImage *Img;                   // BmpͼƬ����ָ�� 
	int index;                       // ΪMapBlock�еڼ���ͼƬ
};

// �жϵ��Ƿ���������
bool PtIn(Point &pt, Rect &rc);

#endif