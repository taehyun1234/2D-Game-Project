#pragma once
#include "PathFinding.h"
class Boss
{
public:
	Boss();
	~Boss();

	void									Update(int tileSizeX, int tileSizeY);
	void									Init(int x, int y);
	void									Draw(HDC hdc, int aniCount);
	void									AStar(int map[MAP_WIDTH][MAP_HEIGHT]);

private:
	int										hp;
	float									_x, _y;
	int										_width, _height;
	CImage								_bossImg;
	CImage								_bossAttackImg;
	unique_ptr<PathFinding>		_ai;
	vector<Point2D*>					_point;
	int										_pointIdx;
	float									_time;
};