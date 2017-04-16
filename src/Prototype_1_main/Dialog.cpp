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

// 根据配置文件创建对话框
Dialog* Dialog::Build(string &strName)
{
	vector<string> vecWidgets;
	// 赋值名字和层次
	m_strName = strName;
	//m_nDlgLayer = nLayer;

	// 获取文件路径
	string strDlgCfgPath = "../cfg/" + m_strName + ".ini";

	ifstream m_FileIn(strDlgCfgPath.c_str(), ios::in);
	if (m_FileIn.is_open())
	{
		string strFileLine;
		while (!m_FileIn.eof())
		{
			getline(m_FileIn, strFileLine);
			int nLast = strFileLine.size() - 1;

			// 获取Section标识符
			if ('[' == strFileLine[0] && ']' == strFileLine[nLast])
			{
				vecWidgets.push_back(strFileLine.substr(1, nLast - 1));

				// 放入属性
				while (getline(m_FileIn, strFileLine))
				{
					// 以=区分字段名和值,并以此放入容器,存储形式为第一行为字段名，第二行为字段的值
					int nIndex = strFileLine.find('=');
					string strFirst = strFileLine.substr(0, nIndex);
					string strSecond = strFileLine.substr(nIndex + 1, strFileLine.size());
					vecWidgets.push_back(strFirst);
					vecWidgets.push_back(strSecond);
					if (m_FileIn.eof() || strFileLine == "")
						break;
				}
				
				// 读完一个Section，创建子控件
				CreateChildWidgets(vecWidgets);

				// 清楚当前控件字段值列表
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
		// 取type字段的值
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

		// 创建控件
		pWidget->Create(vecWidgets, this);

		// 控件加入子控件容器
		m_ChildWidget.push_back(pWidget);
	}
}

// 找到子控件
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

// 鼠标左键点击响应
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