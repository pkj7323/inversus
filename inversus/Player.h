#pragma once
#include"header.h"
#include"Circle.h"
#include"Effect.h"

class Board;
class Bullet;
class DropBullets;
class Enemy;
class Lifeitem;
class Player
{
public:
	Player();
	Player(RECT gameRect);
	
	void move();
	void paint(HDC hdc);
	void rotateBullet();
	void setRect(RECT rect);
	
	void collision(vector<vector<Board>> board, RECT gameRect, vector<DropBullets>& dropbullets,vector<Lifeitem>& lifeitems);
	void shoot();
	int getBulletCount();
	void shootCooltime();
	void addBulletCount();
	void Death(RECT gamerect);
	void setAroundRect(RECT AroundRect);
	void setLife(int life);
	int getLife();
	void setAlive(bool isAlive);
	bool getIsAlive();
	RECT getAroundRect();
	bool playerSpawn(vector<Enemy>& enemies, vector<vector<Board>>& boards);
	void playerSpawnEffect();
	RECT rect = {0,0,50,50};
	RECT beforeRect = { 0,0,50,50 };
	
	COLORREF* rectColor = new COLORREF(RGB(100, 100, 100));
	vector<Circle> circles;
	
	float speed = 0.7f;
	bool L, R, T, B;
private:
	Effect effect;
	int life;
	RECT AroundRect;
	float coolTime = 10;
	int bulletCount = 6;
	bool isAlive;
};

