#include "DlgMgr.h"

DlgMgr::DlgMgr()
{

}

DlgMgr::~DlgMgr()
{

}

// �������ִ����Ի��� 
Dialog* DlgMgr::CreateDlg(string &DlgName)
{
	Dialog *pDlg;

	// �������ִ����Ի������
	if (DlgName == "Dialog")
		pDlg = new Dialog;
	else
		pDlg = new Dialog;

	pDlg->Build(DlgName, m_nMaxLayer);

	// ��ǰ�����
	m_nMaxLayer += 50;

	// ����Ի��������
	m_vDlgArr.push_back(*pDlg);

	return pDlg;
}

// �ҵ�ָ�����ֵĶԻ���
bool DlgMgr::FindDialog(string &strName, Dialog **p)
{
	for (int i = 0; i < m_vDlgArr.size(); i++)
	{
		if (m_vDlgArr[i].m_strName == strName)
		{
			*p = &m_vDlgArr[i];
			return true;
		}
	}
	return false;
}

void DlgMgr::SendMsg(string &strDlgName, string &strConName, string &Msg, MsgParam *MsgParam)
{
	Dialog *pDlg = NULL;
	if (FindDialog(strDlgName, &pDlg))
	{
		Control *pCon = NULL;
		if (pDlg->FindControl(strConName, &pCon))
		{
			pCon->ProcMsg(Msg, *MsgParam);
		}
	}
}

// ������¼�
void DlgMgr::ButtonClick(Point &ptMouse)
{
	ptMouse.nY = VIEWHEIGHT - ptMouse.nY;
	for (int i = 0; i < m_vDlgArr.size(); i++)
	{
		if (PtIn(ptMouse, m_vDlgArr[i].m_Rect))
		{
			MsgParam msg;
			msg.pt = ptMouse;
			SendMsg(m_vDlgArr[i].m_strName, m_vDlgArr[i].m_strName, string("MSG_LBUTTONCLICKED"), &msg);
		}
	}
}

// ȫ�ֱ���
DlgMgr *g_pDlgMgr = new DlgMgr;
