#include "BulletControl.h"

BulletControl::BulletControl()
{
}

void BulletControl::move()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].move();
	}
}

void BulletControl::paint(HDC hdc)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].paint(hdc);
	}
	
}

bool BulletControl::BoardFor(vector<vector<Board>>& board, Bullet bulletI)
{
	POINT pt = { bulletI.bulletRect.left+(bulletI.bulletRect.right - bulletI.bulletRect.left)/2,
		bulletI.bulletRect.top+(bulletI.bulletRect.right-bulletI.bulletRect.left)/2};
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			if (PtInRect(&board[i][j].rect,pt)&&board[i][j].color==RGB(0,0,0))
			{
				board[i][j].color = RGB(255, 255, 255);
				return true;
			}
		}
	}
	return false;
}

void BulletControl::shoot(int d,Player player)
{
	setPlayer(player);
	Bullet::Direction dir;
	switch (d)
	{
	case 1:
		dir = Bullet::L;
		break;
	case 2:
		dir = Bullet::T;
		break;
	case 3:
		dir = Bullet::R;
		break;
	case 4:
		dir = Bullet::B;
		break;
	case 0:
		dir = Bullet::stop;
		break;
	default:
		break;
	}
	bullets.push_back(Bullet(dir));
	Bullet* bullet=&bullets[bullets.size() - 1];
	switch (dir)
	{
	case Bullet::L:
		OffsetRect(&bullet->bulletRect, player.rect.left, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		OffsetRect(&bullet->bulletTailRect, player.rect.left, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		OffsetRect(&bullet->bulletTailRect2, player.rect.left, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		break;
	case Bullet::T:
		OffsetRect(&bullet->bulletRect, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.top);
		OffsetRect(&bullet->bulletTailRect, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.top);
		OffsetRect(&bullet->bulletTailRect2, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.top);
		break;
	case Bullet::R:
		OffsetRect(&bullet->bulletRect, player.rect.right, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		OffsetRect(&bullet->bulletTailRect, player.rect.right, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		OffsetRect(&bullet->bulletTailRect2, player.rect.right, player.rect.top + (player.rect.bottom - player.rect.top) / 2);
		break;
	case Bullet::B:
		OffsetRect(&bullet->bulletRect, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.bottom);
		OffsetRect(&bullet->bulletTailRect, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.bottom);
		OffsetRect(&bullet->bulletTailRect2, player.rect.left + (player.rect.right - player.rect.left) / 2, player.rect.bottom);
		break;
	default:
		break;
	}
	
}

void BulletControl::collision(vector<vector<Board>>& board, RECT gameRect)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].bulletRect.left<gameRect.left||
			bullets[i].bulletRect.top<gameRect.top||
			bullets[i].bulletRect.bottom>gameRect.bottom||
			bullets[i].bulletRect.right>gameRect.right)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (BoardFor(board,bullets[i]))
		{
			break;
		}
	}
}

void BulletControl::setPlayer(Player player)
{
	this->player = player;
}

double BulletControl::getSpeed()
{
	return speed;
}


