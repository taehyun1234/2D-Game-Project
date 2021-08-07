#pragma once
#include "Scene.h"
#include "Monster.h"
#include "Player.h"
#include "House.h"
#include "Arrow.h"
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
	float									_time;
	int										_timeCnt;
	float									_aniSpeed;

	int										_tileSizeX;
	int										_tileSizeY;

	unique_ptr<Monster>			_monster;
	unique_ptr<Player>				_player;
	unique_ptr<House>				_house;

	CImage								_openMap;
	CImage								_closeMap;

	list<shared_ptr<Arrow>>		_arrowList;
	int										_mapData[MAP_WIDTH][MAP_HEIGHT];
};