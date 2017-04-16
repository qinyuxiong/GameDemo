#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "Utility.h"
#include "Canvas.h"
#include "PreCompile.h"


// �ؼ�������
class Widget
{
public:
	Rect m_recArea;                                                                 // �ؼ�����
	Image *m_pBckGround;                                                         // ����λͼ
	Widget *m_pParent;                                                             // ���ڵ�
	string m_strName;                                                               // �ؼ���
	int m_nLayer;                                                                   // ��ǰ���
	          
	Widget();
	~Widget();

	virtual void Create(vector<string> &vecInit, Widget *pParent);                 // �����ؼ����������Ժ͸��ؼ�

	virtual void Show(Canvas *pCanvas);

	virtual void GetRelativePos(int &nStartX, int &nEndX, int &nWidth, int &nStartY, int &nEndY);

	virtual void DrawBackground(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);                                            // ��ʾ�ؼ�

	virtual void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);

	virtual void ProcMsg(string &Msg, MsgParam &MsgParam);                          // ������Ϣ 

	virtual bool PtIn(Point &ptMouse);                                              // ���Ƿ���������

	virtual void OnLButtonClicked(Point &pt);                                       // �����������Ӧ

};

#endif