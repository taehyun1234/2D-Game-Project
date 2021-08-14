#include "pch.h"
#include "Monster.h"
#include "Time.h"
Monster::Monster()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\슬라임_Sprite.png");
	_bossHitImg.Load(L"..\\Resources\\images\\Main\\슬라임_Hit.png");
	_bossAttackImg.Load(L"..\\Resources\\images\\Main\\슬라임_Attack.png");
	_hpBar.Load(L"..\\Resources\\images\\Main\\hp_bar.png");
	_hpfill.Load(L"..\\Resources\\images\\Main\\hp.png");
	_spawnAni.Load(L"..\\Resources\\images\\Main\\spawn.png");
	_x = 0, _y = 0, _width = 49, _height = 49;
	_hp = 1000;
	_hitAniCnt = 0;
	_hit = false;
	_attack = false;
	printf("몬스터 생성 \n");
	_iter = _point.begin();
	_spawn = false;
	_attackAniCnt = 0;
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

bool Monster::Hit(int x, int y)
{
	bool bRet = false;
	if (Collide2DCircle(_x, _y, x, y,30) == true)
	{
   		_hit = true;
		_hp -= 100;
		bRet = true;
	}
	return bRet;
}

bool Monster::Attack_House(int x, int y)
{
	bool bRet = false;

	if (Collide2DCircle(_x, _y, x, y, 30) == true)
	{
		bRet = true;
		_attack = true;
	}
	return bRet;
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

int Monster::GetHP()
{
	return _hp;
}

void Monster::Update(int tileSizeX, int tileSizeY)
{
	if (_attack == true)
	{
		_attackAniCnt++;
		if (_attackAniCnt > 6)
		{
			_attackAniCnt = 0;
			_attack = false;
		}
	}

	if (_spawn == true)
	{
		_spawnCnt++;
		if (_spawnCnt > 10)
		{
			_spawnCnt = 0;
			_spawn = false;
		}
	}


	if (_hit == true)
	{
		_hitAniCnt++;
		if (_hitAniCnt > 6)
		{
			_hitAniCnt = 0;
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
	_hp = 1000;
	_spawn = true;
	_hitAniCnt = 0;
	_spawnCnt = 0;
}

void Monster::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 7;
	_bossImg.Draw(hdc, _x, _y, _width, _height, 170 * anicount, 0, 174, 174);
		
	int bar = (1000 - _hp) * 60 / 1000;

	if (60 - bar > 0)
	{
		_hpBar.Draw(hdc, _x, _y - _height / 3, 60, 15, 0, 0, 901, 241);
		_hpfill.Draw(hdc, _x, _y - _height / 3, 60 - bar, 15, 0, 0, 901, 241);
	}


	if (_hit == true)
	{
		_bossHitImg.Draw(hdc, _x, _y, _width, _height, 512 * _hitAniCnt, 0, 512, 512);
	}

	if (_attack == true)
	{
		_bossAttackImg.Draw(hdc, _x, _y, _width, _height, 517 * _attackAniCnt, 0, 517, 328);
	}

	if (_spawn == true)
	{
		_spawnAni.Draw(hdc, 49 * 20, 49 * 13, _width+20, _height + 20, 341 * _spawnCnt, 0, 341, 277);
	}
}
