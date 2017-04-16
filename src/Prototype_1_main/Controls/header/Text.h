#ifndef _TEXT_H_
#define _TEXT_H_

#include "Control.h"

class Text :public Control
{
public:
	string m_text;
	Text();
	~Text();

	void Create(vector<string> &vecInit, Control *pParent);
};

#endif