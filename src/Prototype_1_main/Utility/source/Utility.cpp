#include "Utility.h"

// �жϵ��Ƿ���������
bool PtIn(Point &pt, Rect &rc)
{
	if (pt.nX >= rc.nLeft && pt.nY <= rc.nRight)
		if (pt.nY >= rc.nDown && pt.nY <= rc.nTop)
			return true;
	return false;
}