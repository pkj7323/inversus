#pragma once
#include"header.h"
#include"Circle.h"
class DropBullets :public Circle
{
public:
	DropBullets();
	DropBullets(int num, RECT rect, bool special);
	void rotateBullet();
	void paint(HDC hdc);
	void setRect(RECT rect);
	RECT getRect();
	int getNum();
	void setSpecial(bool isSpecial);
	bool getSpecial();
private:
	int num;
	vector<Circle> circles;
	RECT rect;
	COLORREF color;
	bool isSpecial;
};

