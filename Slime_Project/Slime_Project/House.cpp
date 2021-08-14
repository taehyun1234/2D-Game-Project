#include "pch.h"
#include "House.h"

House::House()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
	_houseImg.Load(L"..\\Resources\\images\\Main\\House.png");
	_hpBar.Load(L"..\\Resources\\images\\Main\\hp_bar.png");
	_hpfill.Load(L"..\\Resources\\images\\Main\\hp.png");
}

House::~House()
{
}

void House::Draw(HDC hdc)
{
	_houseImg.Draw(hdc, _x, _y, _width, _height, 0, 0, 601, 600);
	int bar = (1000 - _hp) * 60 / 1000;

	if (60 - bar > 0)
	{
		_hpBar.Draw(hdc, _x, _y - _height / 3, 60, 10, 0, 0, 901, 241);
		_hpfill.Draw(hdc, _x, _y - _height / 3, 60 - bar, 10, 0, 0, 901, 241);
	}
}


void House::Init(int x, int y)
{
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
	_hp = 1000;
}

bool House::Damaged(int damage)		// ¾ê 0µÇ¸é ³¡
{
	bool bRet = false;
	_hp -= damage;
	if (_hp <= 0)
		bRet = true;
	
	return bRet;
}

void House::GetCoord(int& x, int& y)
{
	x = _x;
	y = _y;
}
