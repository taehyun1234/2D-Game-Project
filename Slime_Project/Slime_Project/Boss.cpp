#include "pch.h"
#include "Boss.h"
#include "Time.h"
Boss::Boss()
{
	_bossImg.Load(L"..\\Resources\\images\\Main\\ΩΩ∂Û¿”_Sprite.png");
	_x = 0, _y = 0, _width = 80, _height = 100;
	hp = 1000;

	_ai = make_unique<PathFinding>();
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
}

void Boss::Update()
{
	_time += static_cast<float>(GET_SINGLE(Time)->GetDeltaTime());

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

	int left = _x/20* _point[0]->_x;
	int right = left + _x / 20;
	int top = _y / 13 * _point[0]->_y;
	int bottom = top + _y / 13;

	Rectangle(hdc, left, top, right, bottom);

	left = _x / 20 * _point[_point.size()-1]->_x;
	right = left + _x / 20;
	top = _y / 13 * _point[_point.size() - 1]->_y;
	bottom = top + _y / 13;

	Rectangle(hdc, left, top, right, bottom);
}
