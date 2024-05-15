#pragma once
#include "header.h"
#include "Board.h"
#include"Effect.h"
class Player;
class BulletControl;
class Enemy
{
public:
	Enemy();
	Enemy(RECT rect, Board board);
	void paint(HDC hdc);
	void setRect(RECT rect,Board board);
	void move(Player player);
	bool collision(BulletControl& bulletControl, vector<vector<Board>>& boards,RECT gamerect);
	bool getIsAlive();
	void setIsAlive(bool trigger);
	RECT getRect();
	void Death(vector<vector<Board>>& boards);
	RECT getAroundRect();
	Effect effect;
private:
	float spawnTime = 10;
	RECT rect;
	RECT AroundRect;
	bool isAlive;
	COLORREF color = RGB(0, 130, 255);
	
};

