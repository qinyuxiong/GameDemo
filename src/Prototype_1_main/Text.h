#ifndef _TEXT_H_
#define _TEXT_H_

#include "Widget.h"

class Text :public Widget
{
public:
	string m_text;
	Text();
	~Text();

	virtual void Create(vector<string> &vecInit, Widget *pParent);

	virtual void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);
};

#endif