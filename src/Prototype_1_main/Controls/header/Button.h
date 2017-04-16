#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Control.h"

// ∞¥≈•¿‡
class Button : public Control
{
public:
	BmpImage *m_pDownImage;

	Button();
	~Button();
	void Create(vector<string> &vecInit, Control *pParent);
};

#endif