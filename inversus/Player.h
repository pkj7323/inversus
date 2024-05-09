#pragma once
#include"header.h"
#include"Circle.h"

class Player
{
public:
	Player();
	enum state
	{
		STOP,L, R, T, B,
	};
	void move();
	void paint(HDC hdc);
	void rotateBullet();
	void setRect(RECT rect);
	RECT rect = {0,0,50,50};
	RECT gameRect;
	COLORREF rectColor = RGB(100, 100, 100);
	vector<Circle> circles;
	state playerState;
	double speed = 0.5f;
	
};

