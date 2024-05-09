#pragma once
#include "header.h"
class Board
{
public:
	RECT rect;
	COLORREF color=RGB(0,0,0);
	void paint(HDC hdc);
};

