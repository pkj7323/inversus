#include "Effect.h"

Effect::Effect()
{
}

//이펙트 시작 지점 가운데pos
Effect::Effect(int x,int y)
{
	pos = POINT{ x,y };
}

void Effect::paint(HDC hdc)
{
	Ellipse(hdc, pos.x - 10 - size[4], pos.y - 10 - size[4], pos.x - 10 + size[4], pos.y - 10 + size[4]);
	Ellipse(hdc, pos.x - 4 - size[3], pos.y - 4 - size[3], pos.x - 4 + size[3], pos.y - 4 + size[3]);
	
	Ellipse(hdc, pos.x + 2 - size[1], pos.y + 2 - size[1], pos.x + 2 + size[1], pos.y + 2 + size[1]);
	Ellipse(hdc, pos.x + 6 - size[2], pos.y + 6 - size[2], pos.x + 6 + size[2], pos.y + 6 + size[2]);
	Ellipse(hdc, pos.x - size[0], pos.y - size[0], pos.x + size[0], pos.y + size[0]);
	
	
}

void Effect::setPos(POINT pos)
{
	this->pos = pos;
}

void Effect::shrinkSize()
{
	for (size_t i = 0; i < size.size(); i++)
	{
		if (size[i]==0)
		{

		}
		else {
			size[i]--;
		}
		
	}
	if (size[4] == 0)
	{
		size = { 5, 10, 15, 20, 25 };
		isAlive = false;
	}
	else {
		isAlive = true;
	}
}

bool Effect::getIsAlive()
{
	return isAlive;
}

void Effect::setIsAlive(bool isAlive)
{
	this->isAlive = isAlive;
}


