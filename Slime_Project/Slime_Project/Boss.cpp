#include "pch.h"
#include "Boss.h"

Boss::Boss()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\ΩΩ∂Û¿”_Sprite.png");
	_x = 0, _y = 0, _width = 80, _height = 100;
	hp = 1000;
}

Boss::~Boss()
{
}

void Boss::Update()
{
}

void Boss::Init(int x,int y)
{
	_x = x;
	_y = y;
	hp = 1000;
}

void Boss::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 7;
	_bossImg.Draw(hdc, _x, _y, _width, _height, 235 * anicount, 0, 235, 254);
}

void Boss::AStar()
{
}
