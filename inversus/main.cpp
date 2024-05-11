#include<Windows.h>
#include<tchar.h>
#include<vector>
#include"Board.h"
#include<chrono>
#include<atlimage.h>
#include "Player.h"
#include"BulletControl.h"
#pragma comment (lib, "msimg32.lib")
using namespace std;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Inversus";
typedef Player PLAYER;
LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK ScoreFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void setRects(RECT gamerect, vector<vector<Board>>& rects, int xDiv,int yDiv, RECT& playerSize);
void CALLBACK moveFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK rotateFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

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
		300, 50, 1200, 900, NULL, (HMENU)NULL, hInstance, NULL);
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
PLAYER player;
vector<vector<Board>> boards;
RECT GameRect;
BulletControl bulletControl;
LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	static RECT clientrect;
	
	static RECT playerRect;
	
	static int xDiv = 11;
	static int yDiv = 11;
	static RECT turnWhiterect;
	static RECT temprect;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	HFONT hFont, oldFont;
	static wstring str = TEXT("");
	switch (iMessage)
	{
	case WM_CREATE:
		boards.resize(yDiv);
		for (size_t i = 0; i < yDiv; i++)
		{
			boards[i].resize(xDiv);
		}
		SetTimer(hWnd, 1, 30, (TIMERPROC)ScoreFunc);
		SetTimer(hWnd, 2, 10, (TIMERPROC)rotateFunc);
		SetTimer(hWnd, 3, 0.000001, (TIMERPROC)moveFunc);
		GetClientRect(hWnd, &clientrect);
		GameRect = RECT{ 0,0,700,700 };
		turnWhiterect = RECT{ 0,0,140,140 };
		
		OffsetRect(&GameRect, (clientrect.right - 700) / 2, 120);
		setRects(GameRect, boards, xDiv, yDiv, playerRect);
		
		player.setRect(playerRect);
		OffsetRect(&turnWhiterect, player.rect.left - (playerRect.right - playerRect.left), player.rect.top - 25);
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
		break;
	
	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientrect);
		
		
		

		

		mDC = CreateCompatibleDC(hDC);//메모리 dc만들기
		hBitmap = CreateCompatibleBitmap(hDC, clientrect.right, clientrect.bottom);//메모리Dc와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap);//메모리DC와 비트맵 연결


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
		TextOutW(mDC, 0, 50, str.c_str(), str.size());
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
			break;
		case VK_DOWN:
			bulletControl.shoot(4, player);
			break;
		case VK_LEFT:
			bulletControl.shoot(1, player);
			break;
		case VK_RIGHT:
			bulletControl.shoot(3, player);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
			player.playerState = PLAYER::STOP;
			break;
		case 'S':
			player.playerState = PLAYER::STOP;
			break;
		case 'A':
			player.playerState = PLAYER::STOP;
			break;
		case 'D':
			player.playerState = PLAYER::STOP;
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'w':
			player.playerState = PLAYER::T;
			break;
		case 's':
			player.playerState = PLAYER::B;
			break;
		case 'a':
			player.playerState = PLAYER::L;
			break;
		case 'd':
			player.playerState = PLAYER::R;
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
void CALLBACK ScoreFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	Score++;
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
		player.collision(boards,GameRect);
		time = 0;
	}
	static double bulletTime = 0;
	bulletTime += bulletControl.getSpeed();
	if (bulletTime >= 1)
	{
		bulletControl.setPlayer(player);
		bulletControl.move();
		bulletControl.collision(boards, GameRect);
		bulletTime = 0;
	}
	
	
	InvalidateRect(hWnd, NULL, false);
}
void CALLBACK rotateFunc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	player.rotateBullet();
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
