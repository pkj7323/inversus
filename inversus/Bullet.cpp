#include "Bullet.h"

Bullet::Bullet()
{
	dx = 0;
	dy = 0;
	bulletRect = RECT{ 0,0,0,0 };
	bulletTailRect = RECT{ 0,0,0,0 };
	bulletTailRect2 = RECT{ 0,0,0,0 };
}

Bullet::Bullet(Direction d, bool special)
{
	this->special = special;
	dx = 0;
	dy = 0;
	direction = d;
	if (special)
	{
		bulletColor = RGB(255, 1, 1);
		bulletTailColor = RGB(210, 0, 0);
		bulletTailColor2 = RGB(180, 0, 0);
	}
	switch (direction)
	{
	case Bullet::stop:
		bulletRect = RECT{ 0,0,0,0 };
		bulletTailRect = RECT{ 0,0,0,0 };
		bulletTailRect2 = RECT{ 0,0,0,0 };
		break;
	case Bullet::L:
		bulletRect = RECT{ 0,0,20,20 };
		bulletTailRect = RECT{ 10,0,30,20 };
		bulletTailRect2 = RECT{ 20,0,50,20 };
		break;
	case Bullet::T:
		bulletRect = RECT{ 0,0,20,20 };
		bulletTailRect = RECT{ 0,10,20,30 };
		bulletTailRect2 = RECT{ 0,20,20,50 };
		break;
	case Bullet::R:
		bulletTailRect2 = RECT{ 0,0,30,20 };
		bulletTailRect = RECT{ 20,0,40,20 };
		bulletRect = RECT{ 30,0,50,20 };
		break;
	case Bullet::B:
		bulletTailRect2 = RECT{ 0,0,20,30 };
		bulletTailRect = RECT{ 0,20,20,40 };
		bulletRect = RECT{ 0,30,20,50 };
		break;
	default:
		bulletRect = RECT{ 0,0,0,0 };
		bulletTailRect = RECT{ 0,0,0,0 };
		bulletTailRect2 = RECT{ 0,0,0,0 };
		break;
	}
}
void Bullet::copyBullet(Bullet origin) {
	this->bulletColor = origin.bulletColor;
	this->bulletTailColor = origin.bulletTailColor;
	this->bulletTailColor2 = origin.bulletTailColor2;
	this->bulletMoveSpeed = origin.bulletMoveSpeed;
	this->bulletTimer = origin.bulletTimer;
	this->bulletTimerAccel = origin.bulletTimerAccel;
	this->direction = origin.direction;
	this->dx = origin.dx;
	this->dy = origin.dy;
	this->special = origin.special;
	this->bulletRect = origin.bulletRect;
	this->bulletTailRect = origin.bulletTailRect;
	this->bulletTailRect2 = origin.bulletTailRect2;
}
void Bullet::offsetRect(int dx, int dy)
{
	OffsetRect(&bulletRect, dx, dy);
	OffsetRect(&bulletTailRect, dx, dy);
	OffsetRect(&bulletTailRect2, dx, dy);
}
bool Bullet::addBulletTime()
{
	bulletTimer += bulletTimerAccel;
	if (bulletTimer >= 1)
	{
		
		bulletTimer = 0;
		
		if (bulletTimerAccel>=1)
		{
			
			bulletMoveSpeed += 0.5f;
		}
		else
		{
			bulletTimerAccel += 0.1f;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::move()
{
	switch (direction)
	{
	case Bullet::L:
		dx = -bulletMoveSpeed;
		break;
	case Bullet::T:
		dy = -bulletMoveSpeed;
		break;
	case Bullet::R:
		dx = bulletMoveSpeed;
		break;
	case Bullet::B:
		dy = bulletMoveSpeed;
		break;
	default:
		break;
	}
	
	OffsetRect(&bulletRect, dx, dy);
	OffsetRect(&bulletTailRect, dx, dy);
	OffsetRect(&bulletTailRect2, dx, dy);
}

void Bullet::paint(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(bulletTailColor2);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, bulletTailRect2.left, bulletTailRect2.top, bulletTailRect2.right, bulletTailRect2.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(bulletTailColor);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, bulletTailRect.left, bulletTailRect.top, bulletTailRect.right, bulletTailRect.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(bulletColor);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, bulletRect.left, bulletRect.top, bulletRect.right, bulletRect.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
	
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

bool Bullet::getSpecial()
{
	return special;
}

