#include "BoardShakeManager.h"

void BoardShakeManager::shake(RECT& gamerect, vector<vector<Board>>& boards)
{
	switch (seq)
	{
	case BoardShakeManager::one:
		OffsetRect(&gamerect, 10, 10);
		seq = two;
		break;
	case BoardShakeManager::two:
		OffsetRect(&gamerect, -10, -10);
		seq = three;
		break;
	case BoardShakeManager::three:
		OffsetRect(&gamerect, -10, -10);
		seq = four;
		break;
	case BoardShakeManager::four:
		OffsetRect(&gamerect, 10, 10);
		seq = five;
		break;
	case BoardShakeManager::five:
		//OffsetRect(&gamerect, 10, 10);
		wasshake = false;
		seq = stop;
		break;
	default:
		break;
	}
	setRects(gamerect, boards);
}

void BoardShakeManager::update()
{
	if (seq == stop)
	{
		seq = one;
	}
}

BoardShakeManager::BoardShakeManager()
{
	timer = 0;
	num = 0;
	seq = stop;

}

void BoardShakeManager::setRects(RECT gamerect, vector<vector<Board>>& boards)
{
	{
		RECT temp = gamerect;
		gamerect.right = gamerect.left + ((gamerect.right - gamerect.left) / num);
		gamerect.bottom = gamerect.top + ((gamerect.bottom - gamerect.top) / num);
		int dx = gamerect.right - gamerect.left;
		int dy = gamerect.bottom - gamerect.top;

		for (size_t i = 0; i < boards.size(); i++)
		{
			for (size_t j = 0; j < boards[i].size(); j++)
			{
				boards[i][j].rect = gamerect;

				gamerect.left += dx;
				gamerect.right += dx;
			}
			gamerect.left = temp.left;
			gamerect.right = temp.left + dx;
			gamerect.top += dy;
			gamerect.bottom += dy;
		}

	}
}

void BoardShakeManager::setNum(int num)
{
	this->num = num;
}

bool BoardShakeManager::getWasShake()
{
	return wasshake;
}

void BoardShakeManager::setWasShake(bool wasshake)
{
	this->wasshake = wasshake;
}
