#include "Circle.h"

void Circle::rotateBullet(RECT rect)
{
	dx = rect.right - (rect.right - rect.left)/2 + 15 * cos(angle);
	dy = rect.bottom - (rect.bottom - rect.top)/2 + 15 * sin(angle);
}

void Circle::paint(HDC hdc,COLORREF rectcolor)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	if (!wasShot)
	{
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, dx - 5, dy - 5, dx + 5, dy + 5);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
	}
	else {
		
	}
	
}
