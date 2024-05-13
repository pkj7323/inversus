#include "Player.h"
#include "Board.h"
#include"Bullet.h"
Player::Player()
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

void Player::move()
{
	if (L)
	{
		OffsetRect(&rect, -10, 0);
	}
	if (R)
	{
		OffsetRect(&rect, 10, 0);
	}
	if (T)
	{
		OffsetRect(&rect, 0, -10);
	}
	if (B)
	{
		OffsetRect(&rect, 0, 10);
	}
	
}

void Player::paint(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(rectColor);
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
		circles[i].paint(hdc, rectColor);
	}
}

void Player::rotateBullet()
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].angle += 0.05;
		circles[i].rotateBullet(this->rect);
	}
}

void Player::setRect(RECT rectsize)
{
	rect.left = rectsize.left+2;
	rect.top = rectsize.top+2;
	rect.right = rectsize.right-2;
	rect.bottom = rectsize.bottom-2;
}



void Player::collision(vector<vector<Board>> board,RECT gameRect)
{
	RECT temp;
	
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			if (IntersectRect(&temp,&rect,&board[i][j].rect)&&board[i][j].color==RGB(0,0,0))
			{
				rect = beforeRect;
				L = false;
				R = false;
				T = false;
				B = false;
			}
			if (gameRect.right<rect.right||gameRect.bottom<rect.bottom||gameRect.top>rect.top||gameRect.left>rect.left)
			{
				rect = beforeRect;
				L = false;
				R = false;
				T = false;
				B = false;
			}
			
		}
	}
}







