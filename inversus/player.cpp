#include "Player.h"
#include "Board.h"
#include"Bullet.h"
#include"DropBullets.h"
Player::Player()
{
}
Player::Player(RECT gameRect)
{
	circles.resize(6);
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].angle = 1.0471975 * i;
	}
	OffsetRect(&rect, gameRect.bottom/2, gameRect.right/2);
	beforeRect = rect;
	
	L = false;
	R = false;
	T = false;
	B = false;

}

Player::~Player()
{

}

void Player::move()
{
	if (L)
	{
		OffsetRect(&rect, -10, 0);
		OffsetRect(&AroundRect, -10, 0);
	}
	if (R)
	{
		OffsetRect(&rect, 10, 0);
		OffsetRect(&AroundRect, 10, 0);
	}
	if (T)
	{
		OffsetRect(&rect, 0, -10);
		OffsetRect(&AroundRect, 0, -10);
	}
	if (B)
	{
		OffsetRect(&rect, 0, 10);
		OffsetRect(&AroundRect, 0, 10);
	}
	
}

void Player::paint(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(*rectColor);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom,20,20);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].paint(hdc, *rectColor);
	}
}

void Player::rotateBullet()
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		
		circles[i].rotateBullet(this->rect);
	}
}

void Player::setRect(RECT rectsize)
{
	rect.left = rectsize.left+2;
	rect.top = rectsize.top+2;
	rect.right = rectsize.right-2;
	rect.bottom = rectsize.bottom-2;

	AroundRect = RECT{ rect.left - (rectsize.right - rectsize.left) ,rect.top - (rectsize.bottom - rectsize.top),
			rect.right + (rectsize.right - rectsize.left),rect.bottom + (rectsize.bottom - rectsize.top) };

}



void Player::collision(vector<vector<Board>> board,RECT gameRect,vector<DropBullets>& dropbullets)
{
	RECT temp;
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			if (IntersectRect(&temp,&rect,&board[i][j].rect)&&board[i][j].color!=RGB(255,255,255))
			{
				rect = beforeRect;
			}
			if (gameRect.right<rect.right||gameRect.bottom<rect.bottom||gameRect.top>rect.top||gameRect.left>rect.left)
			{
				rect = beforeRect;
			}
			
		}
	}
	for (size_t i = 0; i < dropbullets.size(); i++)
	{
		RECT DBRects = dropbullets[i].getRect();
		if (IntersectRect(&temp, &DBRects,&rect))
		{
			for (size_t j = 0; j < dropbullets[i].getNum(); j++)
			{
				addBulletCount();
			}
			dropbullets.erase(dropbullets.begin() + i);
		}
	}
}

void Player::shoot()
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		if (circles[i].wasShot == false)
		{
			circles[i].wasShot = true;
			break;
		}
		
	}
	if (bulletCount>0)
	{
		bulletCount--;
	}
	
}

int Player::getBulletCount()
{
	return bulletCount;
}

void Player::shootCooltime()
{
	if (coolTime<=0)
	{
		addBulletCount();
		coolTime = 10;
	}
	coolTime -= 1;
}

void Player::addBulletCount()
{
	if (bulletCount < 6)
	{
		bulletCount++;
		for (size_t i = 0; i < circles.size(); i++)
		{
			if (circles[i].wasShot == true)
			{
				circles[i].wasShot = false;
				break;
			}

		}
	}
}

void Player::Death()
{
	//죽음 타이머 돌아가고 맵 가운데 생성 이펙트
	//맵 가운데 생성하면서 그주변 하얀색 및 적 사망
	//죽음 타이머가 0이 되면 다시 생성
}

void Player::setAroundRect(RECT AroundRect)
{
	this->AroundRect = AroundRect;
}

RECT Player::getAroundRect()
{
	return AroundRect;
}








