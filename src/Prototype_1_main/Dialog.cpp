#include "Dialog.h"
#include "Button.h"
#include "Text.h"
#include "Animation.h"

extern Canvas *g_pCanvas;

Dialog:: Dialog()
{

}

Dialog::~Dialog()
{

}

// ���������ļ������Ի���
Dialog* Dialog::Build(string &strName)
{
	vector<string> vecWidgets;
	// ��ֵ���ֺͲ��
	m_strName = strName;
	//m_nDlgLayer = nLayer;

	// ��ȡ�ļ�·��
	string strDlgCfgPath = "../cfg/" + m_strName + ".ini";

	ifstream m_FileIn(strDlgCfgPath.c_str(), ios::in);
	if (m_FileIn.is_open())
	{
		string strFileLine;
		while (!m_FileIn.eof())
		{
			getline(m_FileIn, strFileLine);
			int nLast = strFileLine.size() - 1;

			// ��ȡSection��ʶ��
			if ('[' == strFileLine[0] && ']' == strFileLine[nLast])
			{
				vecWidgets.push_back(strFileLine.substr(1, nLast - 1));

				// ��������
				while (getline(m_FileIn, strFileLine))
				{
					// ��=�����ֶ�����ֵ,���Դ˷�������,�洢��ʽΪ��һ��Ϊ�ֶ������ڶ���Ϊ�ֶε�ֵ
					int nIndex = strFileLine.find('=');
					string strFirst = strFileLine.substr(0, nIndex);
					string strSecond = strFileLine.substr(nIndex + 1, strFileLine.size());
					vecWidgets.push_back(strFirst);
					vecWidgets.push_back(strSecond);
					if (m_FileIn.eof() || strFileLine == "")
						break;
				}
				
				// ����һ��Section�������ӿؼ�
				CreateChildWidgets(vecWidgets);

				// �����ǰ�ؼ��ֶ�ֵ�б�
				vecWidgets.clear();
			}
		}
	}
	return this;
}

void Dialog::CreateChildWidgets(vector<string> &vecWidgets)
{
	if (0 != vecWidgets.size())
	{
		// ȡtype�ֶε�ֵ
		string strType = vecWidgets[2];

		Widget *pWidget;
		if ("Dialog" == strType)
			pWidget = this;
		else if ("Button" == strType)
			pWidget = new Button;
		else if ("Text" == strType)
			pWidget = new Text;
		else if ("Animation" == strType)
			pWidget = new Animation;
		else
			pWidget = new Widget;

		// �����ؼ�
		pWidget->Create(vecWidgets, this);

		// �ؼ������ӿؼ�����
		m_ChildWidget.push_back(pWidget);
	}
}

// �ҵ��ӿؼ�
bool Dialog::FindWidget(string &strConName, Widget **p)
{
	//map<int, Widget*>::iterator result;
	vector<Widget*>::iterator result;
	for (result = m_ChildWidget.begin(); result != m_ChildWidget.end(); result++)
	{
		if ((*result)->m_strName == strConName)
		{
			*p = *result;
			return true;
		}
	}
	return false;
}

//void Dialog::ProcMsg(string &Msg, MsgParam &MsgParam)
//{
//	if (Msg == "MSG_SHOW")
//		Draw(g_pCanvas);
//	else if (Msg == "MSG_LBUTTONCLICKED")
//		OnLButtonClicked(MsgParam.pt);
//}

// �����������Ӧ
void Dialog::OnLButtonClicked(Point &pt)
{
	vector<Widget*>::iterator result;
	for (result = m_ChildWidget.begin(); result != m_ChildWidget.end(); result++)
	{
		if ((*result)->PtIn(pt))
		{

		}
	}
}

void Dialog::Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY)
{
	vector<Widget*>::iterator result;
	for (result = m_ChildWidget.begin() + 1; result != m_ChildWidget.end(); result++)
	{
		Widget *pWidget = *result;
		if (pWidget->m_strName == "Animation")
		{
			if (!((Animation*)pWidget)->IsStart())
				((Animation*)pWidget)->Start();
			//pWidget->Draw();
		}
		pWidget->Show(pCanvas);
	}
}