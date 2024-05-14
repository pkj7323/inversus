#pragma once
#include"header.h"
#include"Board.h"
class BoardShakeManager
{
public:
	BoardShakeManager();
	enum sequence {
		stop,one, two, three, four, five
	};
	sequence seq;
	void shake(RECT& gamerect,vector<vector<Board>>& boards);
	void update();
	void setRects(RECT gamerect, vector<vector<Board>>& boards);
	void setNum(int num);
	bool getWasShake();
	void setWasShake(bool wasshake);
private:
	float timer;
	bool wasshake = false;
	int num;
};

