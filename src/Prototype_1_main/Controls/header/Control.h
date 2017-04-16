#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Utility.h"
#include "PreCompile.h"


// 控件基础类
class Control
{
public:
	Rect m_Rect;                                                                    // 控件区域
	BmpImage *m_pBckGround;                                                         // 背景位图
	Control *m_pParent;                                                             // 父节点
	string m_strName;                                                               // 控件名
	int m_nLayer;                                                                   // 当前层次
	          
	Control();
	~Control();

	virtual void Create(vector<string> &vecInit, Control *pParent);                 // 创建控件并设置属性和父控件

	virtual void Draw();                                                            // 显示控件

	virtual void ProcMsg(string &Msg, MsgParam &MsgParam);                          // 处理消息 

	virtual bool PtIn(Point &ptMouse);                                              // 点是否在区域内
};

#endif