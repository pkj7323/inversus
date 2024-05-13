#include "Enemy.h"
#include "Player.h"
#include "BulletControl.h"
Enemy::Enemy()
{
	isAlive = true;
}
Enemy::Enemy(RECT rect, Board board)
{
	setRect(rect, board);
	isAlive = true;
}
void Enemy::paint(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPen = CreatePen(PS_DASH, 2, color);
	HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, AroundRect.left, AroundRect.top, AroundRect.right, AroundRect.bottom);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, oldBrush);

}

void Enemy::setRect(RECT rect,Board board)
{
	this->rect = rect;
	AroundRect = RECT{ rect.left - (board.rect.right - board.rect.left) ,rect.top - (board.rect.bottom-board.rect.top),
		rect.right + (board.rect.right - board.rect.left),rect.bottom + (board.rect.bottom - board.rect.top) };
}

void Enemy::move(Player player)
{
	POINT playerPos = { player.rect.left + (player.rect.right - player.rect.left) / 2,
		player.rect.top + (player.rect.bottom - player.rect.top) / 2 };
	POINT enemy = { rect.left + (rect.right - rect.left) / 2, rect.top + (rect.bottom - rect.top) / 2 };
	POINT diff = { playerPos.x - enemy.x,playerPos.y - enemy.y };
	if (abs(diff.x)>abs(diff.y))
	{
		if (diff.x<0)
		{
			OffsetRect(&rect, -5, 0);
			OffsetRect(&AroundRect, -5, 0);
		}
		else {
			OffsetRect(&rect, 5, 0);
			OffsetRect(&AroundRect, 5, 0);
		}
	}
	else
	{
		if (diff.y < 0)
		{
			OffsetRect(&rect, 0, -5);
			OffsetRect(&AroundRect, 0, -5);
		}
		else {
			OffsetRect(&rect, 0, 5);
			OffsetRect(&AroundRect, 0, 5);
		}
	}
}

bool Enemy::collision(Player player, BulletControl& bulletControl, vector<vector<Board>>& boards)
{
	RECT temp;
	if (IntersectRect(&temp,&rect,&player.rect))
	{
		//플레이어 죽음
	}
	vector<Bullet> bullets=bulletControl.getBullets();
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (IntersectRect(&temp, &rect, &bullets[i].bulletRect)
			|| IntersectRect(&temp, &rect, &bullets[i].bulletTailRect)
			|| IntersectRect(&temp, &rect, &bullets[i].bulletTailRect2))
		{
			return Death(boards);
		}
	}
	return false;

}

bool Enemy::getIsAlive()
{
	return isAlive;
}

void Enemy::setIsAlive(bool trigger)
{
	isAlive = trigger;
}

bool Enemy::Death(vector<vector<Board>>& boards)
{
	RECT temp;
	for (size_t i = 0; i < boards.size(); i++)
	{
		for (size_t j = 0; j < boards[i].size(); j++)
		{
			if (IntersectRect(&temp,&AroundRect,&boards[i][j].rect))
			{
				boards[i][j].color = RGB(255, 255, 255);
			}
			
		}
	}
	rect = RECT{ 0,0,0,0 };
	AroundRect = RECT{ 0,0,0,0 };
	isAlive = false;
	return true;
	
}

