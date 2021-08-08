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
	void									GetTilePos(int& x, int& y, int tileSizeX, int tileSizeY);
	bool									Hit(int x, int y);							// �÷��̾��� ȭ�쿡 �¾��� ���
	void									Attack_House(int x, int y);			// ���� ������ ���
	void									ChangeTargetPos(list<Coordinate*> point);
	void									GetPos(int& x, int& y);
	int										GetHP();
private:
	int										_hp;
	float									_x, _y;
	int										_width, _height;
	CImage								_bossImg;
	CImage								_bossHitImg;
	CImage								_bossAttackImg;
	int										_pointIdx;
	float									_time;

	bool									_hit;
	int										_hitAniCount;

	bool									_attack;
	int										_attackAniCount;

	list<Coordinate*>					_point;
	list<Coordinate*>::iterator		_iter;

};