#ifndef _DLGMGR_H_
#define _DLGMGR_H_

#include "Dialog.h"

class DlgMgr
{
public:
	vector<Dialog> m_vDlgArr;                                                                           // 存储所有对话框
	int m_nMaxLayer;                                                                                    // 当前最大层次

	DlgMgr();
	~DlgMgr();

	Dialog* CreateDlg(string &DlgName);                                                                 // 根据名字创建对话框

	bool FindDialog(string &strName, Dialog **p);                                                       // 找到指定名字的对话框

	void SendMsg(string &strDlgName, string &strConName, string &Msg, MsgParam *MsgParam = NULL);       // 给对话框发送消息

	void ButtonClick(Point &ptMouse);                                                                   // 鼠标点击事件
}; 

#endif