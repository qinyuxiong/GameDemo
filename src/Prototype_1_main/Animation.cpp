#include "Animation.h"
#include "Image.h"
#include "ViewPort.h"
#include "io.h"

extern ViewPort *g_pViewPort;

Animation::Animation()
{
	m_bStarted = FALSE;
}

Animation::~Animation()
{
	m_mapData.clear();
}

void Animation::Create(vector<string> &vecInit, Widget *pParent)
{
	Widget::Create(vecInit, pParent);
	for (int i = 3; i < vecInit.size(); ++i)
	{
		// 获取类型和值，并初始化属性值
		string strType = vecInit[i];
		string strValue = vecInit[++i];
		if (strType == "Src")
		{
			//string strPath = "../res/Animate/Player/00001/Forward/";
			LoadAnimation(strValue.c_str());
			//m_recArea.nLeft = atoi(strValue.c_str());
		}
	}
}

// 根据当前时间显示特定帧
void Animation::Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY)
{
	//pCanvas->Draw(nStartX, nStartY, 0, m_recArea.nRight - m_recArea.nLeft, 0, m_recArea.nTop - m_recArea.nDown, (m_recArea.nRight - m_recArea.nLeft) * 4, m_mapData[0].GetData());
	DWORD dwCurTime = GetTickCount();
	if (dwCurTime - m_dwLastTime >= m_nRate)
	{
		pCanvas->Draw(nStartX, nStartY, 0, m_recArea.nTop - m_recArea.nDown, 0, m_recArea.nRight - m_recArea.nLeft, (m_recArea.nRight - m_recArea.nLeft) * 4, m_mapData[m_nCurFrame++].GetData(), DRAW_ANIMATE);

		if (m_nCurFrame >= m_nTotalFrame)
			m_nCurFrame = 0;
		m_dwLastTime = dwCurTime;
	}
	else
		pCanvas->Draw(nStartX, nStartY, 0, m_recArea.nTop - m_recArea.nDown, 0, m_recArea.nRight - m_recArea.nLeft, (m_recArea.nRight - m_recArea.nLeft) * 4, m_mapData[m_nCurFrame].GetData(), DRAW_ANIMATE);
}

// 加载指定路径下的所有连续Bmp图片为动画数据
void Animation::LoadAnimation(string strAniPath)
{
	string strPath = strAniPath + "*.bmp";
	int nIndex = 0;
	_finddata_t fileInfo;
	long hFile = _findfirst(strPath.c_str(), &fileInfo);
	if (hFile != -1)
	{
		do
		{
			if (!(fileInfo.attrib & _A_SUBDIR))
			{
				Image *p = new Image;
				m_mapData.insert(make_pair(nIndex, *p));
				string strPath = strAniPath + fileInfo.name;
				m_mapData[nIndex++].LoadBmpImg(strPath.c_str());
			}
		} while (_findnext(hFile, &fileInfo) == 0);
		_findclose(hFile);
	}
	m_nTotalFrame = nIndex - 1;
	m_recArea.nRight = m_recArea.nLeft + m_mapData[0].m_nWidth;
	m_recArea.nTop = m_recArea.nDown + m_mapData[0].m_nHeight;
}

// 开始
void Animation::Start()
{
	m_nCurFrame = 0;
	m_nRate = 200;
	m_dwLastTime = GetTickCount();
	m_bStarted = TRUE;
}

// 停止
void Animation::Stop()
{

}