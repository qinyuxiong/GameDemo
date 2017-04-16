#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "Image.h"

class Image;

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
	Image *Img;                   // BmpͼƬ����ָ�� 
	int index;                       // ΪSurface�еڼ���ͼƬ
};

// �жϵ��Ƿ���������
bool PtIn(Point &pt, Rect &rc);

#endif