#ifndef _DLGMGR_H_
#define _DLGMGR_H_

#include "Dialog.h"

class DlgMgr
{
public:
	vector<Dialog> m_vDlgArr;                                                                           // �洢���жԻ���
	int m_nMaxLayer;                                                                                    // ��ǰ�����

	DlgMgr();
	~DlgMgr();

	Dialog* CreateDlg(string &DlgName);                                                                 // �������ִ����Ի���

	bool FindDialog(string &strName, Dialog **p);                                                       // �ҵ�ָ�����ֵĶԻ���

	void SendMsg(string &strDlgName, string &strConName, string &Msg, MsgParam *MsgParam = NULL);       // ���Ի�������Ϣ

	void ButtonClick(Point &ptMouse);                                                                   // ������¼�
}; 

#endif