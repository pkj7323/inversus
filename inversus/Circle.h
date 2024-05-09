#pragma once
#include "header.h"
class Circle
{
public:
	int dx, dy;
	double angle;
	COLORREF color = RGB(0, 0, 0);
	bool wasShot = false;
	float coolTime = 10;
	void rotateBullet(RECT rect);
	void paint(HDC hdc, COLORREF rectcolor);
	
};

