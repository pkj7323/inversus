#pragma once
#include "header.h"
class Bullet
{
public:
	RECT bulletRect;
	COLORREF bulletColor = RGB(0, 0, 0);
	RECT bulletTailRect;
	COLORREF bulletTailColor = RGB(30, 30, 30);
	RECT bulletTailRect2;
	COLORREF bulletTailColor2 = RGB(80, 80, 80);
	float dx, dy;
	enum Direction
	{
		stop,L,T,R,B
	};
	Direction direction = stop;
	Bullet();
	Bullet(Direction d);
	float bulletMoveSpeed = 4.5f;
	bool addBulletTime();
	void move();
	void paint(HDC hdc);
private:
	float bulletTimer = 0;
	float bulletTimerAccel = 0.1f;
};

