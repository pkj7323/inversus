#pragma once
#include"header.h"
#include"Circle.h"

class Board;
class Bullet;
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
	void collision(vector<vector<Board>> board, RECT gameRect);
	void shoot(int d, Bullet*& bullet);
	
	
	
	RECT rect = {0,0,50,50};
	RECT beforeRect = { 0,0,50,50 };
	RECT gameRect;
	COLORREF rectColor = RGB(100, 100, 100);
	vector<Circle> circles;
	state playerState;
	double speed = 0.7f;
	
	
};

