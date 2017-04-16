#include "Animation.h"
#include "BmpImage.h"
#include "ScreenData.h"
#include "io.h"

extern ScreenData *g_pScreenData;

Animation::Animation()
{

}

Animation::~Animation()
{

}

// 根据当前时间显示特定帧
void Animation::Draw()
{
	DWORD dwCurTime = GetTickCount();
	if (dwCurTime - m_dwLastTime >= m_nRate)
	{
		//Draw(m_mapData[m_nCurFrame++]);
		g_pScreenData->SetRect(m_mapData[m_nCurFrame++].GetData(), m_Rect.nLeft, m_Rect.nRight - m_Rect.nLeft, m_Rect.nDown, m_Rect.nTop);
		if (m_nCurFrame >= m_nTotalFrame)
			m_nCurFrame = 0;
		m_dwLastTime = dwCurTime;
	}
}

// 加载指定路径下的所有连续Bmp图片为动画数据
void Animation::LoadAnimation(string strAniPath)
{
	int nIndex = 0;
	_finddata_t fileInfo;
	long hFile = _findfirst(strAniPath.c_str(), &fileInfo);
	while (hFile != -1)
	{
		if (!(fileInfo & _A_SUBDIR))
		{
			BmpImage *p = new BmpImage;
			p->LoadImg(fileInfo.name);
			m_mapData[nIndex] = *p;
		}
		_findnext(hFile, &fileInfo);
	}
}