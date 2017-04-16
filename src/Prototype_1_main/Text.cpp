#include "Text.h"
#include "PreCompile.h"

Text::Text()
{

}

Text::~Text()
{

}

void Text::Create(vector<string> &vecInit, Widget *pParent)
{
	Widget::Create(vecInit, pParent);
	for (int i = 3; i < vecInit.size(); i++)
	{
		// 获取类型和值，并初始化属性值
		string strType = vecInit[i];
		string strValue = vecInit[++i];
		if (strType == "Texts")
		{
			m_text = strValue.c_str();
		}
	}
}

void Text::Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY)
{
	pCanvas->Text(nStartX, nEndX, nStartY, nEndY, m_text);
}