#include "Widget.h"
#include "Image.h"

extern Canvas *g_pCanvas;

Widget::Widget()
{
	m_pBckGround = new Image;
	m_pParent = NULL;
}

Widget::~Widget()
{
	delete m_pBckGround;
	delete m_pParent;
}

// �����ؼ����������Ժ͸��ؼ�
void Widget::Create(vector<string> &vecInit, Widget *pParent)
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
			m_recArea.nLeft = atoi(strValue.c_str());
		}
		else if (strType == "Top")
		{
			m_recArea.nTop = atoi(strValue.c_str());
		}
		else if (strType == "Width")
		{
			m_recArea.nRight = atoi(strValue.c_str()) + m_recArea.nLeft;
		}
		else if (strType == "Height")
		{
			m_recArea.nDown = m_recArea.nTop - atoi(strValue.c_str());
		}
		else if (strType == "BckImage")
		{
			string strPath = "../res/Dlg/" + strValue;
			m_pBckGround->LoadBmpImg(strPath.c_str());
		}
	}
}

void Widget::Show(Canvas *pCanvas)
{
	int nStartX, nEndX, nWidth, nStartY, nEndY;
	GetRelativePos(nStartX, nEndX, nWidth, nStartY, nEndY);
	DrawBackground(pCanvas, nStartX, nEndX, nWidth, nStartY, nEndY);

	Draw(pCanvas, nStartX, nEndX, nWidth, nStartY, nEndY);
}

void Widget::GetRelativePos(int &nStartX, int &nEndX, int &nWidth, int &nStartY, int &nEndY)
{
	// ��ȡ���ؼ���λ��
	Rect rcParent;
	if (m_pParent != NULL && m_pParent != this)
		rcParent = m_pParent->m_recArea;
	else
		rcParent = { 0, 0, 0, 0 };

	// ���ݿؼ�������ʾ����Ӧλ��
	nStartX = rcParent.nLeft + m_recArea.nLeft;
	nEndX = rcParent.nLeft + m_recArea.nRight;

	nWidth = nEndX - nStartX;

	nStartY = rcParent.nDown + m_recArea.nDown;
	nEndY = rcParent.nDown + m_recArea.nTop;
}

// ��ʾ�ؼ�
void Widget::DrawBackground(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY)
{
	pCanvas->Draw(nStartX, nStartY, 0, nEndY - nStartY, 0, nEndX - nStartX, nWidth * 4, m_pBckGround->m_pData, DRAW_DLG);
}

// ������������
void Widget::Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY)
{

}

// ������Ϣ 
void Widget::ProcMsg(string &Msg, MsgParam &MsgParam)
{
	if (Msg == "MSG_SHOW")
		Show(g_pCanvas);
	else if (Msg == "MSG_LBUTTONCLICKED")
		OnLButtonClicked(MsgParam.pt);
}

// ���Ƿ���������
bool Widget::PtIn(Point &ptMouse)
{
	if (ptMouse.nX >= m_recArea.nLeft 
		&& ptMouse.nX <= m_recArea.nRight
		&& ptMouse.nY >= m_recArea.nDown
		&& ptMouse.nY <= m_recArea.nTop)
		return true;

	return false;
}

// �����������Ӧ
void Widget::OnLButtonClicked(Point &pt)
{

}