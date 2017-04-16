#include "Dialog.h"
#include "Button.h"
#include "Text.h"

Dialog:: Dialog()
{

}

Dialog::~Dialog()
{

}

// 根据配置文件创建对话框
Dialog* Dialog::Build(string &strName, int nLayer)
{
	vector<string> m_vecControls;
	// 赋值名字和层次
	m_strName = strName;
	m_nDlgLayer = nLayer;

	// 获取文件路径
	string strDlgCfgPath = m_strName + ".ini";

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
				m_vecControls.push_back(strFileLine.substr(1, nLast - 1));

				// 放入属性
				while (getline(m_FileIn, strFileLine))
				{
					// 以=区分字段名和值,并以此放入容器,存储形式为第一行为字段名，第二行为字段的值
					int nIndex = strFileLine.find('=');
					string strFirst = strFileLine.substr(0, nIndex);
					string strSecond = strFileLine.substr(nIndex + 1, strFileLine.size());
					m_vecControls.push_back(strFirst);
					m_vecControls.push_back(strSecond);
					if (m_FileIn.eof())
						break;
				}
				
				// 读完一个Section，创建子控件
				CreateChildControls(m_vecControls);
			}
		}
	}
	return this;
}

void Dialog::CreateChildControls(vector<string> &vecControls)
{
	if (0 != vecControls.size())
	{
		// 取type字段的值
		string strType = vecControls[2];

		Control *pControl;
		if ("Dialog" == strType)
			pControl = this;
		else if ("Button" == strType)
			pControl = new Button;
		else if ("Text" == strType)
			pControl = new Text;
		else
			pControl = new Control;

		// 创建控件
		pControl->Create(vecControls, this);

		// 控件加入子控件容器
		m_ChildControl[m_nDlgLayer++] = pControl;

		// 清楚当前控件字段值列表
		vecControls.clear();
	}
}

// 找到子控件
bool Dialog::FindControl(string &strConName, Control **p)
{
	map<int, Control*>::iterator result;
	for (result = m_ChildControl.begin(); result != m_ChildControl.end(); result++)
	{
		if (result->second->m_strName == strConName)
		{
			*p = result->second;
			return true;
		}
	}
	return false;
}

void Dialog::ProcMsg(string &Msg, MsgParam &MsgParam)
{
	if (Msg == "MSG_SHOW")
		Draw();
	else if (Msg == "MSG_LBUTTONCLICKED")
		OnLButtonClicked(MsgParam.pt);
}

// 鼠标左键点击响应
void Dialog::OnLButtonClicked(Point &pt)
{
	map<int, Control*>::iterator result;
	for (result = m_ChildControl.begin(); result != m_ChildControl.end(); result++)
	{

	}
}