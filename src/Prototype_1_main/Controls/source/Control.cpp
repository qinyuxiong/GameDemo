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

// �����ؼ����������Ժ͸��ؼ�
void Control::Create(vector<string> &vecInit, Control *pParent)
{
	m_pParent = pParent;
	m_strName = vecInit[0];
	for (int i = 3; i < vecInit.size(); ++i)
	{
		// ��ȡ���ͺ�ֵ������ʼ������ֵ
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

// ��ʾ�ؼ�
void Control::Draw()
{
	// ��ȡ���ؼ���λ��
	Rect rcParent;
	if (m_pParent != NULL && m_pParent != this)
		rcParent = m_pParent->m_Rect;
	else
		rcParent = { 0, 0, 0, 0 };

	// ���ݿؼ�������ʾ����Ӧλ��
	int nStartX = rcParent.nLeft + m_Rect.nLeft;
	int nEndX = rcParent.nRight + m_Rect.nRight;
	int nWidth = nEndX - nStartX;
	int nStartY = rcParent.nDown + m_Rect.nDown;
	int nEndY = rcParent.nTop + m_Rect.nTop;

	// ���þ�������
	g_pScreenData->SetRect(m_pBckGround->m_pData, nStartX, nWidth, nStartY, nEndY);
}

// ������Ϣ 
void Control::ProcMsg(string &Msg, MsgParam &MsgParam)
{
	if (Msg == "")
	{

	}
}

// ���Ƿ���������
bool Control::PtIn(Point &ptMouse)
{
	if (ptMouse.nX >= m_Rect.nLeft && ptMouse.nY <= m_Rect.nRight)
	    if (ptMouse.nY >= m_Rect.nDown && ptMouse.nY <= m_Rect.nTop)
		    return true;
	return false;
}