#include "pch.h"
#include "Boss.h"

Boss::Boss()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\ΩΩ∂Û¿”_Sprite.png");
	_x = 0, _y = 0, _width = 0, _height = 0;
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
}

void Boss::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 7;
	_bossImg.Draw(hdc, 0, 0, 235, 254, 235 * anicount, 0, 235, 254);
}
