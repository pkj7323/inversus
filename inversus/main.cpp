#include<Windows.h>
#include<tchar.h>
#include<vector>
#include"Board.h"
#include<chrono>
#include"Enemy.h"
#include "Player.h"
#include"BulletControl.h"
#include"DropBullets.h"
#include"Effect.h"
#include"BoardShakeManager.h"
#include<random>
#include"resource.h"
#include"Lifeitem.h"
#pragma comment (lib, "msimg32.lib")
using namespace std;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Inversus";

mt19937 mt{ random_device{}() };

typedef Player PLAYER;
LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK ScoreFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void setRects(RECT gamerect, vector<vector<Board>>& rects, int xDiv,int yDiv, RECT& playerSize);
void CALLBACK moveFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK bulletTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK coolTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK EnemyMoveTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = (WNDPROC)WinProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);

	RegisterClassExW(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
		300, 50, 1200, 900, NULL, LoadMenu(hInstance,MAKEINTRESOURCE( IDR_MENU1)), hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

int Score = 0;
int num = 11;
PLAYER player;
vector<vector<Board>> boards;
RECT GameRect;
BulletControl bulletControl;
vector <Enemy> enemies;
vector<DropBullets> dropBullets;
vector<Lifeitem> lifeitems;
BoardShakeManager boardShakeManager;
bool comboMessage = false;
bool invincible = false;

LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	static RECT clientrect;
	
	static RECT playerRect;
	static int life;
	static int xDiv;
	static int yDiv;
	static RECT turnWhiterect;
	static RECT temprect;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HFONT hFont, oldFont;
	static wstring str = TEXT("");
	static wstring lifestr = TEXT("");
	static wstring special = TEXT("");
	static SIZE size;
	static bool isPau = false, isStart = false;
	switch (iMessage)
	{
	case WM_CREATE:
		
		break;
	
	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientrect);
		
		mDC = CreateCompatibleDC(hDC);//메모리 dc만들기
		hBitmap = CreateCompatibleBitmap(hDC, clientrect.right, clientrect.bottom);//메모리Dc와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap);//메모리DC와 비트맵 연결
		
		if (isStart)
		{
			if (player.getLife() == 0)
			{
				Rectangle(mDC, 0, clientrect.top+100, clientrect.right, clientrect.bottom-100);
				hFont = CreateFont(100, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
					CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("굴림체"));
				oldFont = (HFONT)SelectObject(mDC, hFont);
				SetBkMode(mDC, TRANSPARENT);
				DrawText(mDC, L"GAME OVER", lstrlen(L"GAME OVER"), &clientrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SelectObject(mDC, oldFont);
				DeleteObject(hFont);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
				isStart = false;
			}
			else {
				hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
				oldBrush = (HBRUSH)SelectObject(mDC, hBrush);
				hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(mDC, hPen);
				Rectangle(mDC, 0, 0, clientrect.right, clientrect.bottom);//메모리DC에 그리기
				SelectObject(mDC, oldPen);
				DeleteObject(hPen);
				SelectObject(mDC, oldBrush);

				Rectangle(mDC, clientrect.left, clientrect.top, clientrect.right, GameRect.top - 10);

				hFont = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
					CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("굴림체"));
				oldFont = (HFONT)SelectObject(mDC, hFont);
				SetBkMode(mDC, TRANSPARENT);
				TextOutW(mDC, 0, 0, L"SCORE", lstrlen(L"SCORE"));
				str = to_wstring(Score);
				if (comboMessage)
				{
					str += L"콤보!!";

				}
				TextOutW(mDC, 0, 50, str.c_str(), str.size());

				TextOutW(mDC, (clientrect.right - clientrect.left) / 2 - 120, 10, L"LIFE:", lstrlen(L"LIFE:"));
				lifestr = to_wstring(player.getLife());
				TextOutW(mDC, (clientrect.right - clientrect.left) / 2, clientrect.top + 10, lifestr.c_str(), lifestr.size());
				special = L"SPECIAL:";
				GetTextExtentPoint32W(mDC, special.c_str(), special.size(), &size);
				TextOutW(mDC, clientrect.right - size.cx-50, 0, special.c_str(), special.size());
				special = to_wstring(player.getSpecialBulletCount());
				TextOutW(mDC, clientrect.right -50, 0, special.c_str(), special.size());
				SelectObject(mDC, oldFont);
				DeleteObject(hFont);
				for (size_t i = 0; i < boards.size(); i++)
				{
					for (size_t j = 0; j < boards[i].size(); j++)
					{
						boards[i][j].paint(mDC);
					}
				}
				player.paint(mDC);
				bulletControl.paint(mDC);
				for (size_t i = 0; i < enemies.size(); i++)
				{
					enemies[i].paint(mDC);
				}
				for (size_t i = 0; i < lifeitems.size(); i++)
				{
					lifeitems[i].paint(mDC);
				}
				for (size_t i = 0; i < dropBullets.size(); i++)
				{
					dropBullets[i].paint(mDC);
				}
				
			}
		}
		else {
			Rectangle(mDC, 0, 0, clientrect.right, clientrect.bottom);//메모리DC에 그리기
			hFont = CreateFont(100, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("굴림체"));
			oldFont = (HFONT)SelectObject(mDC, hFont);
			DrawText(mDC, L"INVERSUS", lstrlen(L"INVERSUS"), &clientrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(mDC, oldFont);
			DeleteObject(hFont);
		}
		
		

		//복사하고 
		BitBlt(hDC, 0, 0, clientrect.right, clientrect.bottom, mDC, 0, 0, SRCCOPY);

		//해제
		DeleteDC(mDC);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:

			bulletControl.shoot(2,player);
			player.shoot();
			break;
		case VK_DOWN:
			bulletControl.shoot(4, player);
			player.shoot();
			break;
		case VK_LEFT:
			bulletControl.shoot(1, player);
			player.shoot();
			break;
		case VK_RIGHT:
			bulletControl.shoot(3, player);
			player.shoot();
			break;
		default:
			break;
		}
		
		
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
			player.T = false;
			break;
		case 'S':
			player.B= false;
			break;
		case 'A':
			player.L = false;		
			break;
		case 'D':
			player.R = false;
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'w':
			player.T = true;
			break;
		case 's':
			player.B = true;
			break;
		case 'a':
			player.L = true;
			break;
		case 'd':
			player.R = true;
			
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_GAME_PAU:
			isPau = !isPau;
			if (isPau)
			{
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
			}
			else {
				SetTimer(hWnd, 1, 30, (TIMERPROC)ScoreFunc);
				SetTimer(hWnd, 2, 250, (TIMERPROC)coolTimer);
				SetTimer(hWnd, 3, 1, (TIMERPROC)bulletTimer);
				SetTimer(hWnd, 4, 1, (TIMERPROC)moveFunc);
				SetTimer(hWnd, 5, 10, (TIMERPROC)EnemyMoveTimer);
			}
			
			break;
		case ID_GAME_START:
			
			if (!isStart)
			{
				boards.clear();
				enemies.clear();
				dropBullets.clear();
				lifeitems.clear();
				Score = 0;
				comboMessage = false;


				life = 3;
				yDiv = num;
				xDiv = num;
				boards.resize(yDiv);
				for (size_t i = 0; i < yDiv; i++)
				{
					boards[i].resize(xDiv);
				}
				SetTimer(hWnd, 1, 30, (TIMERPROC)ScoreFunc);
				SetTimer(hWnd, 2, 250, (TIMERPROC)coolTimer);
				SetTimer(hWnd, 3, 1, (TIMERPROC)bulletTimer);
				SetTimer(hWnd, 4, 1, (TIMERPROC)moveFunc);
				SetTimer(hWnd, 5, 10, (TIMERPROC)EnemyMoveTimer);
				GetClientRect(hWnd, &clientrect);
				GameRect = RECT{ 0,0,700,700 };
				turnWhiterect = RECT{ 0,0,140,140 };

				OffsetRect(&GameRect, (clientrect.right - 700) / 2, 120);
				setRects(GameRect, boards, xDiv, yDiv, playerRect);
				player = PLAYER(GameRect);
				player.setRect(playerRect);
				
				

				turnWhiterect = player.getAroundRect();
				for (size_t i = 0; i < boards.size(); i++)
				{
					for (size_t j = 0; j < boards[i].size(); j++)
					{
						if (IntersectRect(&temprect, &turnWhiterect, &boards[i][j].rect))
						{
							boards[i][j].color = RGB(255, 255, 255);
						}
					}
				}
				if (num==15)
				{
					for (size_t z = 0; z < 6; z++)
					{
						uniform_int_distribution<> uid{ 0,num - 1 };
						int x = uid(mt);
						int y = uid(mt);
						for (size_t i = 0; i < boards.size(); i++)
						{
							for (size_t j = 0; j < boards[i].size(); j++)
							{
								if (i == x && j == y)
								{
									boards[i][j].color = RGB(255, 0, 0);
								}
							}
						}
					}
					
				}
				isStart = true;
			}
			else {

			}
			break;
		case ID_GAME_EASY:
			if (!isStart)
			{
				num = 7;
				xDiv = num;
				yDiv = num;
			}
			break;
		case ID_GAME_NORMAL:
			if (!isStart)
			{
				num = 11;
				xDiv = num;
				yDiv = num;
			}
			break;
		case ID_GAME_HARD:
			if (!isStart)
			{
				num = 15;
				xDiv = num;
				yDiv = num;
			}
			break;
		case ID_GAME_INVINCIBILITY:
			invincible = !invincible;
			break;
		case ID_GAME_QUIT:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void CALLBACK coolTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	player.shootCooltime();
	
}
void CALLBACK ScoreFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	Score++; 
	static double comboTime=0;
	if (comboMessage)
	{
		comboTime += 0.05;
	}
	
	if (comboTime>=1)
	{
		comboMessage = false;
		comboTime = 0;
	}
}
void CALLBACK bulletTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	
	bulletControl.move();
	bulletControl.collision(boards, GameRect);
	player.beforeRect = player.rect;
	boardShakeManager.setNum(num);
	boardShakeManager.shake(GameRect, boards);
	InvalidateRect(hWnd, NULL, false);
	
}
void CALLBACK moveFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	static double time = 0;
	time += player.speed;
	
	if (time>=1)
	{
		player.beforeRect = player.rect;
		player.move();
		player.collision(boards, GameRect,dropBullets,lifeitems,enemies,invincible);
		
		time = 0;
	}
	
	for (size_t i = 0; i < dropBullets.size(); i++)
	{
		dropBullets[i].rotateBullet();
	}
	player.rotateBullet();
	if (player.playerSpawn(enemies, boards)) {
		if (!boardShakeManager.getWasShake())
		{
			boardShakeManager.setWasShake(true);
			boardShakeManager.update();
		}
		
		
		
	}
	if (player.getIsAlive())
	{
		SetTimer(hWnd, 5, 10, (TIMERPROC)EnemyMoveTimer);
	}
	else {
		KillTimer(hWnd, 5);
	}
	static double effectTime = 0;
	effectTime += 0.05;
	if (effectTime>1)
	{
		player.playerSpawnEffect();
		effectTime = 0;
	}
	
}
void CALLBACK EnemyMoveTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
	uniform_int_distribution<int> dist{ 0,num - 1 };
	int x = 0;
	int y = 0;
	static double enemyTime = 0;
	static double comboTime = 0;
	static double enemyTimeAccel = 0.005;
	comboTime += 0.008;
	enemyTime += enemyTimeAccel;
	if (enemyTime > 1)
	{
		if (enemies.size() < 10)
		{
			while (true) {
				x = dist(mt);
				y = dist(mt);
				RECT temp;
				RECT plyerAroundRect = player.getAroundRect();
				if (IntersectRect(&temp, &plyerAroundRect, &boards[y][x].rect)) {
					continue;
				}
				else {
					break;
				}

			}
			uniform_int_distribution<int> random{ 0,100 };
			if (random(mt) % 2 == 0)
			{
				enemies.push_back(Enemy(boards[y][x].rect, boards[y][x],false));
			}
			else {
				enemies.push_back(Enemy(boards[y][x].rect, boards[y][x], true));
			}
			
			enemyTimeAccel += 0.0005;
		}

		enemyTime = 0;
	}
	static float timer = 0;
	timer += 0.3f;
	if (timer>=1)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(player,boards);
			int col = enemies[i].collision(bulletControl, boards, GameRect);
			if (col ==1|| col == 2) {
				uniform_int_distribution<int> randomDrop{ 0,10000 };
				int RD = randomDrop(mt);
				RD %= 4;
				for (size_t j = 0; j < RD; j++)
				{
					if (randomDrop(mt)%100>49)
					{
						dropBullets.push_back(DropBullets(RD, enemies[i].getRect(), true));
					}
					else {
						dropBullets.push_back(DropBullets(RD, enemies[i].getRect(), false));
					}
					
				}
				
				
				RECT aroundRect = enemies[i].getAroundRect();
				Enemy* ene = &enemies[i];
				if (randomDrop(mt) % 20 == 0)
				{
					lifeitems.push_back(Lifeitem(enemies[i].getRect()));
				}
				if (col == 2)
				{
					bool t = true;
					while (t)
					{
						t = false;
						for (size_t j = 0; j < enemies.size(); j++)
						{
							RECT temp;
							RECT enemyRect = enemies[j].getRect();
							if (IntersectRect(&temp, &aroundRect, &enemyRect) && ene != &enemies[j])
							{
								enemies.erase(enemies.begin() + j);
								t = true;
								break;
							}
						}

					}
					
				}
				
				for (size_t j = 0; j < enemies.size(); j++)
				{
					if (ene==&enemies[j])
					{
						enemies.erase(enemies.begin() + j);
						break;
					}
				}
				boardShakeManager.update();
				
				if (comboTime<1)
				{
					Score += 200;
					comboMessage = true;
					comboTime = 0;
				}
				else {
					Score += 100;
					comboTime = 0;
				}
				
			}

		}
		timer = 0;
	}
	
}
void setRects(RECT gamerect, vector<vector<Board>>& boards, int xDiv,int yDiv,RECT& playerSize)
{
	RECT temp = gamerect;
	gamerect.right = gamerect.left + ((gamerect.right - gamerect.left) / xDiv);
	gamerect.bottom = gamerect.top + ((gamerect.bottom - gamerect.top) / yDiv);
	int dx = gamerect.right - gamerect.left;
	int dy = gamerect.bottom - gamerect.top;
	playerSize = RECT{ 0,0,dx-10,dy-10 };
	OffsetRect(&playerSize, (temp.right - (temp.right - temp.left) / 2) - dx / 2, (temp.bottom - (temp.bottom - temp.top) / 2)-dy/2);
	for (size_t i = 0; i < yDiv; i++)
	{
		for (size_t j = 0; j < xDiv; j++)
		{
			boards[i][j].rect = gamerect;

			gamerect.left += dx;
			gamerect.right += dx;
		}
		gamerect.left = temp.left;
		gamerect.right = temp.left+dx;
		gamerect.top += dy;
		gamerect.bottom += dy;
	}
	
}
