#pragma once
#include"header.h"
class Effect
{
public:
	Effect();
	Effect(int x, int y);
	void paint(HDC hdc);
	void setPos(POINT pos);
	void shrinkSize();
	bool getIsAlive();
	void setIsAlive(bool isAlive);
private:
	bool isAlive = false;
	POINT pos;
	vector<int> size = { 5, 10, 15, 20, 25 };
};

