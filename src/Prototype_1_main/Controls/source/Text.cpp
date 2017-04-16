#include "Text.h"
#include "PreCompile.h"

Text::Text()
{

}

Text::~Text()
{

}

void Text::Create(vector<string> &vecInit, Control *pParent)
{
	Control::Create(vecInit, pParent);
	for (int i = 2; i < vecInit.size(); i++)
	{
		string strIndex = vecInit[i];
		if (0 == strIndex.find("Text"))
		{
			m_text = strIndex.substr(strIndex.find('='));
		}
	}
}