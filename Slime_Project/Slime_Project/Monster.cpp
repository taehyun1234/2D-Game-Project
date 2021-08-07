#include "pch.h"
#include "Monster.h"
#include "Time.h"
Monster::Monster()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\슬라임_Sprite.png");
	_bossHitImg.Load(L"..\\Resources\\images\\Main\\슬라임_Hit.png");
	_bossAttackImg.Load(L"..\\Resources\\images\\Main\\슬라임_Attack.png");
	_x = 0, _y = 0, _width = 64, _height = 64;
	hp = 1000;
	_hitAniCount = 0;
	_hit = false;
	_attack = false;
	_ai = make_unique<PathFinding>();		
	printf("보스 생성 \n");
}

Monster::~Monster()
{
	printf("보스 소멸 \n");
}

void Monster::AStar(int map[MAP_WIDTH][MAP_HEIGHT])
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			_ai->LoadMap(i, j, map[i][j]);
		}
	}
	_point = _ai->GetShortestPath(20, 13, 3, 3);
	_pointIdx = _point.size() - 1;
}

void Monster::Hit(int x, int y)
{
	if (Collide2DCircle(_x, _y, x, y,30) == true)
	{
   		_hit = true;
		hp -= 100;
	}
}

void Monster::Attack(int x, int y)
{
	if (Collide2DCircle(_x, _y, x, y, 30) == true)
	{
		_attack = true;
	}
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
		if (_point.size() > 0)
		{
			float ptX = _point[_pointIdx]->_x * tileSizeX;
			float ptY = _point[_pointIdx]->_y * tileSizeY;

			float moveX = 1;//abs(ptX - _x) * 0.1;
			float moveY = 1;//abs(ptY - _y) * 0.1;

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
				if (_pointIdx > 0)
				{
					_pointIdx--;
				}
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
