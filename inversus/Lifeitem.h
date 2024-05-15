#pragma once
#include"header.h"
class Player;
class Lifeitem
{
public:
	Lifeitem();
	Lifeitem(RECT rect);
	void paint(HDC hdc);
	RECT getRect();
	int getlife();
private:
	int life;
	RECT rect;
	wstring text = L"Life";
};

