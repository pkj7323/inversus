#pragma once
#include"header.h"
#include"Circle.h"

class Board;
class Bullet;
class Player
{
public:
	Player();
	Player(RECT gameRect);
	~Player();
	void move();
	void paint(HDC hdc);
	void rotateBullet();
	void setRect(RECT rect);
	void collision(vector<vector<Board>> board, RECT gameRect);
	void shoot();
	int getBulletCount();
	void shootCooltime();
	void addBulletCount();
	void Death();
	RECT getAroundRect();
	RECT rect = {0,0,50,50};
	RECT beforeRect = { 0,0,50,50 };
	
	COLORREF* rectColor = new COLORREF(RGB(100, 100, 100));
	vector<Circle> circles;
	
	float speed = 0.7f;
	bool L, R, T, B;
private:
	RECT AroundRect;
	float coolTime = 10;
	int bulletCount = 6;
};

