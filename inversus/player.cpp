#include "Player.h"

Player::Player()
{
	circles.resize(6);
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].angle = 1.0471975 * i;
	}
	OffsetRect(&rect, gameRect.bottom/2, gameRect.right/2);
}

void Player::move()
{
	switch (playerState)
	{
	case Player::L:
		OffsetRect(&rect, -5, 0);
		break;
	case Player::R:
		OffsetRect(&rect, 5, 0);
		break;
	case Player::T:
		OffsetRect(&rect, 0, -5);
		break;
	case Player::B:
		OffsetRect(&rect, 0, 5);
		break;
	default:
		break;
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
	rect = rectsize;
}



