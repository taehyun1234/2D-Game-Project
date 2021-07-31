#pragma once
#include "PathFinding.h"
class Boss
{
public:
	Boss();
	~Boss();

	void									Update();
	void									Init(int x, int y);
	void									Draw(HDC hdc, int aniCount);
	void									AStar(int map[MAP_WIDTH][MAP_HEIGHT]);

private:
	int										hp;
	int										_x, _y, _width, _height;
	CImage								_bossImg;
	unique_ptr<PathFinding>		_ai;
	vector<Point2D*>						_point;
	float									_time;
};