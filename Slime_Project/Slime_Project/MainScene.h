#pragma once
#include "Scene.h"
#include "Boss.h"
#include "Player.h"
#include "House.h"
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
	int										_aniSpeed;

	int										_tileSizeX;
	int										_tileSizeY;

	unique_ptr<Boss>					_boss;
	unique_ptr<Player>				_player;
	unique_ptr<House>				_house;

	CImage								_openMap;
	CImage								_closeMap;

	int										_mapData[MAP_WIDTH][MAP_HEIGHT];
};