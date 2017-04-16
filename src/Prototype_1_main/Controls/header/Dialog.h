#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "Control.h"
#include "PreCompile.h"

// �Ի������

class Dialog : public Control
{
public:
	map<int, Control*> m_ChildControl;     // �Ի��������ӿؼ�����һ��Ϊ�Ի�����firstΪ�ؼ���Σ�secondΪ�ؼ�ָ��      
	string m_strName;                     // �Ի�������
	int m_nDlgLayer;                      // ��ǰ�Ի������еĲ��

	// ����
	Dialog* Build(string &strName, int nLayer);

	// �����ӿؼ�
	void CreateChildControls(vector<string> &vecControls);

	// �ҵ��ӿؼ�
	bool FindControl(string &strConName, Control **p);

	// �����麯��
	void ProcMsg(string &Msg, MsgParam &MsgParam);

	// �����������Ӧ
	void OnLButtonClicked(Point &pt);

	Dialog();
	~Dialog();
};

#endif