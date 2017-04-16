#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "Utility.h"
#include "Canvas.h"
#include "PreCompile.h"


// 控件基础类
class Widget
{
public:
	Rect m_recArea;                                                                 // 控件区域
	Image *m_pBckGround;                                                         // 背景位图
	Widget *m_pParent;                                                             // 父节点
	string m_strName;                                                               // 控件名
	int m_nLayer;                                                                   // 当前层次
	          
	Widget();
	~Widget();

	virtual void Create(vector<string> &vecInit, Widget *pParent);                 // 创建控件并设置属性和父控件

	virtual void Show(Canvas *pCanvas);

	virtual void GetRelativePos(int &nStartX, int &nEndX, int &nWidth, int &nStartY, int &nEndY);

	virtual void DrawBackground(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);                                            // 显示控件

	virtual void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);

	virtual void ProcMsg(string &Msg, MsgParam &MsgParam);                          // 处理消息 

	virtual bool PtIn(Point &ptMouse);                                              // 点是否在区域内

	virtual void OnLButtonClicked(Point &pt);                                       // 鼠标左键点击响应

};

#endif