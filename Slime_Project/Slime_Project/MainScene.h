#pragma once
#include "Scene.h"
#include "Monster.h"
#include "Player.h"
#include "House.h"
#include "Arrow.h"
#include "AStar.h"
#include "MonsterAttack.h"
class MainScene :	public Scene
{
public:
	MainScene();
	virtual ~MainScene();

	void Init(HWND hWnd);
	SCENE Update(HWND hWnd);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void Draw(HWND hWnd, HDC hdc);
	void LoadMap();
	void DrawMap(HDC hdc);

	void ResetScene();
private:
	float										_time;
	int											_timeCnt;
	float										_aniSpeed;

	int											_tileSizeX;
	int											_tileSizeY;

//	unique_ptr<Monster>				_monster;

	unique_ptr<House>					_house;
	
	CImage									_openMap;	
	CImage									_closeMap;
	CImage									_portal;

	list<shared_ptr<Arrow>>			_arrowList;
	list<shared_ptr<MonsterAttack>>	_monsterAttack;
	list<shared_ptr<Monster>>			_monsterList;
	
	int											_monsterGenCnt;
	int											_monsterAttackCnt;
	int											_portalCnt;

public:
	//AI 관련
	list<Coordinate*>						_coordiList;
	int											_mapData[MAP_WIDTH][MAP_HEIGHT];
	unique_ptr<Player>					_player;
	unique_ptr<AStar>					_ai;

	int											_player_Prevpos_x;
	int											_player_Prevpos_y;		

	int											_player_Curpos_x;
	int											_player_Curpos_y;		// 실시간으로 플레이어의 좌표값이 바뀔 때마다 거리를 새로 계산

	int											_monster_Prevpos_x;
	int											_monster_Prevpos_y;

	int											_monster_Curpos_x;
	int											_monster_Curpos_y;		// 실시간으로 플레이어의 좌표값이 바뀔 때마다 거리를 새로 계산
};