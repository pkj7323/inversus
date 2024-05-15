#include "Lifeitem.h"

Lifeitem::Lifeitem()
{
}

Lifeitem::Lifeitem(RECT rect)
{
	this->rect = rect;
	life = 1;
}

void Lifeitem::paint(HDC hdc)
{
	RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, 10, 10);
	DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER | DT_VCENTER|DT_SINGLELINE);
}

RECT Lifeitem::getRect()
{
	return rect;
}

int Lifeitem::getlife()
{
	return life;
}


