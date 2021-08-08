#include "pch.h"
#include "MonsterAttack.h"

MonsterAttack::MonsterAttack()
{
	_x = 0;
	_y = 0;

	_img.Load(L"..\\Resources\\images\\Main\\슬라임_Attack_3.png");
	_img2.Load(L"..\\Resources\\images\\Main\\슬라임_Attack_2.png");
}

MonsterAttack::~MonsterAttack()
{
}

void MonsterAttack::Init(int x, int y, int dir)
{
	_x = x;
	_y = y;
	_aniCount = 0;
	_width = 47;
	_height = 47;
	_dir = dir;
	_speed = 5;
	_aliveTime = 0;
}

void MonsterAttack::Draw(HDC hdc)
{
	switch (_dir)
	{
	case LEFT:
		_img.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 0, 100, 100);
		break;
	case RIGHT:
		_img.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 100, 100, 100);
		break;
	case BACK:
		_img.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 200, 100, 100);
		break;
	case FRONT:
		_img.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 300, 100, 100);
		break;
	case LEFT_BACK:
		_img2.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 0, 100, 100);
		break;
	case LEFT_FRONT:
		_img2.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 300, 100, 100);
		break;
	case RIGHT_BACK:
		_img2.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 100, 100, 100);
		break;
	case RIGHT_FRONT:
		_img2.Draw(hdc, _x, _y, _width, _height, 100 * _aniCount, 200, 100, 100);
		break;
	}
}

void MonsterAttack::Update()
{
	if (_aniCount < 2) 
	{
		_aniCount++;
	}
	else
	{
		_aniCount = 0;
	}
	switch (_dir)
	{
	case LEFT:
		_x -= _speed;
		break;
	case RIGHT:
		_x += _speed;
		break;
	case FRONT:
		_y += _speed;
		break;
	case BACK:
		_y -= _speed;
		break;
	case LEFT_FRONT:
		_x -= _speed;
		_y += _speed;
		break;
	case LEFT_BACK:
		_x -= _speed;
		_y -= _speed;
		break;
	case RIGHT_FRONT:
		_x += _speed;
		_y += _speed;
		break;
	case RIGHT_BACK:
		_x += _speed;
		_y -= _speed;
		break;
	}
	_aliveTime++;
}

void MonsterAttack::GetCoord(int& x, int& y)
{
	x = _x;
	y = _y;
}

int MonsterAttack::GetAliveTime()
{
	return _aliveTime;
}
