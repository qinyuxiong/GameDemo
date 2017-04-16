#include "Dialog.h"
#include "Button.h"
#include "Text.h"

Dialog:: Dialog()
{

}

Dialog::~Dialog()
{

}

// ���������ļ������Ի���
Dialog* Dialog::Build(string &strName, int nLayer)
{
	vector<string> m_vecControls;
	// ��ֵ���ֺͲ��
	m_strName = strName;
	m_nDlgLayer = nLayer;

	// ��ȡ�ļ�·��
	string strDlgCfgPath = m_strName + ".ini";

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
				m_vecControls.push_back(strFileLine.substr(1, nLast - 1));

				// ��������
				while (getline(m_FileIn, strFileLine))
				{
					// ��=�����ֶ�����ֵ,���Դ˷�������,�洢��ʽΪ��һ��Ϊ�ֶ������ڶ���Ϊ�ֶε�ֵ
					int nIndex = strFileLine.find('=');
					string strFirst = strFileLine.substr(0, nIndex);
					string strSecond = strFileLine.substr(nIndex + 1, strFileLine.size());
					m_vecControls.push_back(strFirst);
					m_vecControls.push_back(strSecond);
					if (m_FileIn.eof())
						break;
				}
				
				// ����һ��Section�������ӿؼ�
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
		// ȡtype�ֶε�ֵ
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

		// �����ؼ�
		pControl->Create(vecControls, this);

		// �ؼ������ӿؼ�����
		m_ChildControl[m_nDlgLayer++] = pControl;

		// �����ǰ�ؼ��ֶ�ֵ�б�
		vecControls.clear();
	}
}

// �ҵ��ӿؼ�
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

// �����������Ӧ
void Dialog::OnLButtonClicked(Point &pt)
{
	map<int, Control*>::iterator result;
	for (result = m_ChildControl.begin(); result != m_ChildControl.end(); result++)
	{

	}
}