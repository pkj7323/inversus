#include "Board.h"

void Board::paint(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB((225-GetRValue(color)), (225 - GetGValue(color)), (225 - GetBValue(color))));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

}
