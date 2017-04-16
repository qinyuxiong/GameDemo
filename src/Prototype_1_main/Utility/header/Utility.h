#ifndef _UTILITY_H_
#define _UTILITY_H_

class BmpImage;

// 区域结构体
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

// 线程参数
class LoadMapImgParam
{
public:
	char szFileName[64];             // Bmp图片名
	BmpImage *Img;                   // Bmp图片数据指针 
	int index;                       // 为MapBlock中第几个图片
};

// 判断点是否在区域内
bool PtIn(Point &pt, Rect &rc);

#endif