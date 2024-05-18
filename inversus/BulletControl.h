#pragma once
#include "header.h"
#include "Bullet.h"
#include "Board.h"
#include "Player.h"
class BulletControl
{
public:
	BulletControl();
	void move();
	void paint(HDC hdc);
	bool BoardFor(vector<vector<Board>>& board, Bullet bulletI);
	void shoot(int d, Player player);
	void collision(vector<vector<Board>>& board, RECT gameRect);
	void setPlayer(Player player);
	void setBullets(vector<Bullet> bullets);
	
	vector<Bullet> getBullets();
private:
	
	vector<Bullet> bullets;
	vector<Bullet> specialBullets;
	
	Player player;
};

