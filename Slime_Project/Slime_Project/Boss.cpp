#include "pch.h"
#include "Boss.h"
#include "Time.h"
Boss::Boss()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\������_Sprite.png");
	_x = 0, _y = 0, _width = 64, _height = 64;
	hp = 1000;

	_ai = make_unique<PathFinding>();		// memory leak
}

Boss::~Boss()
{
}


void Boss::AStar(int map[MAP_WIDTH][MAP_HEIGHT])
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

void Boss::Update(int tileSizeX, int tileSizeY)
{
	if (_point.size() > 0)
	{
		float ptX = _point[_pointIdx]->_x* tileSizeX;
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

void Boss::Init(int x,int y)
{
	_x = x;
	_y = y;
	hp = 1000;
}

void Boss::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 7;
	Rectangle(hdc, _x, _y, _x + 64, _y + 64);
	_bossImg.Draw(hdc, _x, _y, _width, _height, 235 * anicount, 0, 235, 254);
//	int left = _x/20* _point[0]->_x;
//	int right = left + _x / 20;
//	int top = _y / 13 * _point[0]->_y;
//	int bottom = top + _y / 13;
//
//	Rectangle(hdc, left, top, right, bottom);
//
//	left = _x / 20 * _point[_point.size()-1]->_x;
//	right = left + _x / 20;
//	top = _y / 13 * _point[_point.size() - 1]->_y;
//	bottom = top + _y / 13;
//
//	Rectangle(hdc, left, top, right, bottom);
}
