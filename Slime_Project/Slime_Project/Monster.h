#pragma once
#include "PathFinding.h"
class Monster
{
public:
	Monster();
	~Monster();

	void									Update(int tileSizeX, int tileSizeY);
	void									Init(int x, int y);
	void									Draw(HDC hdc, int aniCount);
	void									AStar(int map[MAP_WIDTH][MAP_HEIGHT]);

	void									Hit(int x, int y);			// �÷��̾��� ȭ�쿡 �¾��� ���
	void									Attack(int x, int y);									// ���� ������ ���
private:
	int										hp;
	float									_x, _y;
	int										_width, _height;
	CImage								_bossImg;
	CImage								_bossHitImg;
	CImage								_bossAttackImg;
	unique_ptr<PathFinding>		_ai;
	vector<Point2D*>					_point;
	int										_pointIdx;
	float									_time;

	bool									_hit;
	int										_hitAniCount;

	bool									_attack;
	int										_attackAniCount;
};