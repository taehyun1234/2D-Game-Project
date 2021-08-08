#include "pch.h"
#include "Monster.h"
#include "Time.h"
Monster::Monster()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\슬라임_Sprite.png");
	_bossHitImg.Load(L"..\\Resources\\images\\Main\\슬라임_Hit.png");
	_bossAttackImg.Load(L"..\\Resources\\images\\Main\\슬라임_Attack.png");
	_x = 0, _y = 0, _width = 47, _height = 47;
	hp = 1000;
	_hitAniCount = 0;
	_hit = false;
	_attack = false;
	printf("몬스터 생성 \n");
	_iter = _point.begin();
}


void Monster::GetTilePos(int& x, int& y, int tileSizeX, int tileSizeY)
{
	x = _x / tileSizeX;
	y = _y / tileSizeY;
}

Monster::~Monster()
{
	printf("몬스터 소멸 \n");
}

void Monster::Hit(int x, int y)
{
	if (Collide2DCircle(_x, _y, x, y,30) == true)
	{
   		_hit = true;
		hp -= 100;
	}
}

void Monster::Attack_House(int x, int y)
{
	if (Collide2DCircle(_x, _y, x, y, 30) == true)
	{
		_attack = true;
	}
}

void Monster::ChangeTargetPos(list<Coordinate*> point)
{
	_point = point;
	_iter = _point.begin();
}

void Monster::GetPos(int& x, int& y)
{
	x = _x;
	y = _y;
}

void Monster::Update(int tileSizeX, int tileSizeY)
{
	if (_attack == true)
	{
		_attackAniCount++;
		if (_attackAniCount > 6)
		{
			_attackAniCount = 0;
			_attack = false;
		}
	}

	if (_hit == true)
	{
		_hitAniCount++;
		if (_hitAniCount > 6)
		{
			_hitAniCount = 0;
			_hit = false;
		}
	}
	else
	{
		if (_iter != _point.end())
		{
			float ptX =(*_iter)->x * tileSizeX;
			float ptY =(*_iter)->y * tileSizeY;
		
			float moveX = 1;
			float moveY = 1;
		
			if (ptX < _x)
			{
				_x -= moveX;
			}
			else if (ptX > _x)
			{
				_x += moveX;
			}
		
			if (ptY < _y)
			{
				_y -= moveY;
			}
			else if (ptY > _y)
			{
				_y += moveY;
			}
		
			if (static_cast<int>(ptX) == static_cast<int>(_x) && static_cast<int>(ptY) == static_cast<int>(_y))
			{
				if(_iter != _point.end())
					_iter++;
			}
		}
	}
}

void Monster::Init(int x,int y)
{
	_x = x;
	_y = y;
	hp = 1000;
}

void Monster::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 7;
	_bossImg.Draw(hdc, _x, _y, _width, _height, 170 * anicount, 0, 174, 174);
	if (_hit == true)
	{
		_bossHitImg.Draw(hdc, _x, _y, _width, _height, 512 * _hitAniCount, 0, 512, 512);
	}

	if (_attack == true)
	{
		_bossAttackImg.Draw(hdc, _x, _y, _width, _height, 517 * _attackAniCount, 0, 517, 328);
	}
}
