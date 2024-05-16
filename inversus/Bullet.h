#pragma once
#include "header.h"
class Bullet
{
public:
	
	enum Direction
	{
		stop, L, T, R, B
	};
	Bullet();
	Bullet(Direction d,bool special);
	virtual bool addBulletTime();
	virtual void move();
	virtual void paint(HDC hdc);
	bool getSpecial();
	Direction direction = stop;
	RECT bulletRect;
	COLORREF bulletColor = RGB(0, 0, 0);
	RECT bulletTailRect;
	COLORREF bulletTailColor = RGB(30, 30, 30);
	RECT bulletTailRect2;
	COLORREF bulletTailColor2 = RGB(80, 80, 80);
private:
	bool special;
	float bulletMoveSpeed = 4.5f;
	float dx, dy;
	float bulletTimer = 0;
	float bulletTimerAccel = 0.1f;
};

