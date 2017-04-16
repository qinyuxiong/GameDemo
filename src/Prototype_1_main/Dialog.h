#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "Widget.h"
#include "PreCompile.h"

// �Ի������

class Dialog : public Widget
{
public:
	//map<int, Widget*> m_ChildWidget;     // �Ի��������ӿؼ�����һ��Ϊ�Ի�����firstΪ�ؼ���Σ�secondΪ�ؼ�ָ��
	vector<Widget*> m_ChildWidget;        // �Ի��������ӿؼ�����һ��Ϊ�Ի�����firstΪ�ؼ���Σ�secondΪ�ؼ�ָ��
	string m_strName;                     // �Ի�������
	//int m_nDlgLayer;                    // ��ǰ�Ի������еĲ��

	// ����
	Dialog* Build(string &strName);

	// �����ӿؼ�
	void CreateChildWidgets(vector<string> &vecWidgets);

	// �ҵ��ӿؼ�
	bool FindWidget(string &strConName, Widget **p);

	//// �����麯��
	//void ProcMsg(string &Msg, MsgParam &MsgParam);

	// �����������Ӧ
	void OnLButtonClicked(Point &pt);

	// ���ػ��ƺ���
	virtual void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);

	Dialog();
	~Dialog();
};

#endif