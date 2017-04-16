#include "Control.h"
#include "BmpImage.h"
#include "ScreenData.h"

extern ScreenData *g_pScreenData;

Control::Control()
{
	m_pBckGround = new BmpImage;
	m_pParent = NULL;
}

Control::~Control()
{
	delete m_pBckGround;
	delete m_pParent;
}

// 创建控件并设置属性和父控件
void Control::Create(vector<string> &vecInit, Control *pParent)
{
	m_pParent = pParent;
	m_strName = vecInit[0];
	for (int i = 3; i < vecInit.size(); ++i)
	{
		// 获取类型和值，并初始化属性值
		string strType = vecInit[i];
		string strValue = vecInit[++i];
		if (strType == "Left")
		{
			m_Rect.nLeft = atoi(strValue.c_str());
		}
		else if (strType == "Top")
		{
			m_Rect.nTop = atoi(strValue.c_str());
		}
		else if (strType == "Width")
		{
			m_Rect.nRight = atoi(strValue.c_str()) + m_Rect.nLeft;
		}
		else if (strType == "Height")
		{
			m_Rect.nDown = m_Rect.nTop - atoi(strValue.c_str());
		}
		else if (strType == "BckImage")
		{
			m_pBckGround->LoadImg(strValue.c_str());
		}
	}
}

// 显示控件
void Control::Draw()
{
	// 获取父控件的位置
	Rect rcParent;
	if (m_pParent != NULL && m_pParent != this)
		rcParent = m_pParent->m_Rect;
	else
		rcParent = { 0, 0, 0, 0 };

	// 根据控件坐标显示到对应位置
	int nStartX = rcParent.nLeft + m_Rect.nLeft;
	int nEndX = rcParent.nRight + m_Rect.nRight;
	int nWidth = nEndX - nStartX;
	int nStartY = rcParent.nDown + m_Rect.nDown;
	int nEndY = rcParent.nTop + m_Rect.nTop;

	// 设置举行区域
	g_pScreenData->SetRect(m_pBckGround->m_pData, nStartX, nWidth, nStartY, nEndY);
}

// 处理消息 
void Control::ProcMsg(string &Msg, MsgParam &MsgParam)
{
	if (Msg == "")
	{

	}
}

// 点是否在区域内
bool Control::PtIn(Point &ptMouse)
{
	if (ptMouse.nX >= m_Rect.nLeft && ptMouse.nY <= m_Rect.nRight)
	    if (ptMouse.nY >= m_Rect.nDown && ptMouse.nY <= m_Rect.nTop)
		    return true;
	return false;
}