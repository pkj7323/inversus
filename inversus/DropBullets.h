#pragma once
#include"header.h"
#include"Circle.h"
class DropBullets :public Circle
{
public:
	DropBullets();
	DropBullets(int num,RECT rect);
	void rotateBullet();
	void paint(HDC hdc);
	void setRect(RECT rect);
	RECT getRect();
	int getNum();
private:
	int num;
	vector<Circle> circles;
	RECT rect;
	COLORREF color;
};

