#include "DropBullets.h"



void DropBullets::rotateBullet()
{
	for (int i = 0; i < circles.size(); i++)
	{
		
		circles[i].rotateBullet(rect);
	}
}

DropBullets::DropBullets()
{
	color = RGB(0, 255, 255);
	rect = RECT{ 0,0,0,0 };
}

DropBullets::DropBullets(int num, RECT rect,bool special)
{
	color = RGB(0, 255, 255);
	this->rect = rect;
	this->num = num;
	this->isSpecial = special;
	for (int i = 0; i < num; i++)
	{
		circles.push_back(Circle(num,i,color));
	}
}

void DropBullets::paint(HDC hdc)
{

	for (int i = 0; i < circles.size(); i++)
	{
		circles[i].paint(hdc, color);
	}
}

void DropBullets::setRect(RECT rect)
{
}

RECT DropBullets::getRect()
{
	return rect;
}

int DropBullets::getNum()
{
	return num;
}

void DropBullets::setSpecial(bool isSpecial)
{
	this->isSpecial = isSpecial;
}

bool DropBullets::getSpecial()
{
	return isSpecial;
}


