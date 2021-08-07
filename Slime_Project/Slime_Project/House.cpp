#include "pch.h"
#include "House.h"

House::House()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
	_houseImg.Load(L"..\\Resources\\images\\Main\\House.png");
}

House::~House()
{
}

void House::Draw(HDC hdc)
{
	_houseImg.Draw(hdc, _x, _y, _width, _height, 0, 0, 601, 600);
}

void House::Update()
{
}

void House::Init(int x, int y)
{
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
}

void House::GetCoord(int& x, int& y)
{
	x = _x;
	y = _y;
}
