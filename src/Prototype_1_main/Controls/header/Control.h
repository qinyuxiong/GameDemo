#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Utility.h"
#include "PreCompile.h"


// �ؼ�������
class Control
{
public:
	Rect m_Rect;                                                                    // �ؼ�����
	BmpImage *m_pBckGround;                                                         // ����λͼ
	Control *m_pParent;                                                             // ���ڵ�
	string m_strName;                                                               // �ؼ���
	int m_nLayer;                                                                   // ��ǰ���
	          
	Control();
	~Control();

	virtual void Create(vector<string> &vecInit, Control *pParent);                 // �����ؼ����������Ժ͸��ؼ�

	virtual void Draw();                                                            // ��ʾ�ؼ�

	virtual void ProcMsg(string &Msg, MsgParam &MsgParam);                          // ������Ϣ 

	virtual bool PtIn(Point &ptMouse);                                              // ���Ƿ���������
};

#endif