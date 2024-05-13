#pragma once
#include"header.h"
class Effect
{
public:
	void paint(HDC hdc);
	void setPos(POINT pos);
	void shrinkSize();
private:
	POINT pos;
	vector<int> size = { 5, 10, 15, 20, 25 };
};

