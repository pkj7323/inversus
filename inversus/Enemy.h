#pragma once
#include "header.h"
#include "Board.h"
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
	bool collision(Player player, BulletControl& bulletControl, vector<vector<Board>>& boards);
	bool getIsAlive();
	void setIsAlive(bool trigger);
	bool Death(vector<vector<Board>>& boards);

private:
	RECT rect;
	RECT AroundRect;
	bool isAlive;
	COLORREF color = RGB(0, 130, 255);
	
};

