#include "Button.h"
#include "PreCompile.h"
#include "Image.h"

Button::Button()
{
	m_pDownImage = NULL;
}

Button::~Button()
{
	delete m_pDownImage;
}

void Button::Create(vector<string> &vecInit, Widget *pParent)
{
	Widget::Create(vecInit, pParent);
	for (int i = 2; i < vecInit.size(); i++)
	{
		string strIndex = vecInit[i];
		if (0 == strIndex.find("DownIamge"))
		{
			m_pDownImage = new Image;
			m_pDownImage->LoadBmpImg(strIndex.substr(strIndex.find('=')).c_str());
		}
	}
}