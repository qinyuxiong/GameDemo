#include "DlgMgr.h"

DlgMgr::DlgMgr()
{

}

DlgMgr::~DlgMgr()
{

}

// 根据名字创建对话框 
Dialog* DlgMgr::CreateDlg(string &DlgName)
{
	Dialog *pDlg;

	// 根据名字创建对话框对象
	if (DlgName == "Dialog")
		pDlg = new Dialog;
	else
		pDlg = new Dialog;

	pDlg->Build(DlgName, m_nMaxLayer);

	// 当前最大层次
	m_nMaxLayer += 50;

	// 放入对话框管理器
	m_vDlgArr.push_back(*pDlg);

	return pDlg;
}

// 找到指定名字的对话框
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

// 鼠标点击事件
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

// 全局变量
DlgMgr *g_pDlgMgr = new DlgMgr;
