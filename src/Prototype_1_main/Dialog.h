#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "Widget.h"
#include "PreCompile.h"

// 对话框基类

class Dialog : public Widget
{
public:
	//map<int, Widget*> m_ChildWidget;     // 对话框所有子控件，第一个为对话框本身。first为控件层次，second为控件指针
	vector<Widget*> m_ChildWidget;        // 对话框所有子控件，第一个为对话框本身。first为控件层次，second为控件指针
	string m_strName;                     // 对话框名字
	//int m_nDlgLayer;                    // 当前对话框所有的层次

	// 创建
	Dialog* Build(string &strName);

	// 创建子控件
	void CreateChildWidgets(vector<string> &vecWidgets);

	// 找到子控件
	bool FindWidget(string &strConName, Widget **p);

	//// 覆盖虚函数
	//void ProcMsg(string &Msg, MsgParam &MsgParam);

	// 鼠标左键点击响应
	void OnLButtonClicked(Point &pt);

	// 重载绘制函数
	virtual void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);

	Dialog();
	~Dialog();
};

#endif