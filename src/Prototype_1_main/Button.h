#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Widget.h"

// ∞¥≈•¿‡
class Button : public Widget
{
public:
	Image *m_pDownImage;

	Button();
	~Button();
	void Create(vector<string> &vecInit, Widget *pParent);
};

#endif