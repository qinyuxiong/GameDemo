#include "Utility.h"

// 判断点是否在区域内
bool PtIn(Point &pt, Rect &rc)
{
	if (pt.nX >= rc.nLeft && pt.nY <= rc.nRight)
		if (pt.nY >= rc.nDown && pt.nY <= rc.nTop)
			return true;
	return false;
}