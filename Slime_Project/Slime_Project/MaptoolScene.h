#pragma once
#include "Scene.h"
#include "UI.h"
class MaptoolScene : public Scene
{
public:
	MaptoolScene();
	~MaptoolScene();

	void					Init(HWND hWnd);
	SCENE				Update(HWND hWnd);
	void					Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void					Draw(HWND hWnd, HDC hdc);
	void					ResetScene();
	void					SaveData();

private:
	bool					_mouseDown;
	int						_tileSizeX;
	int						_tileSizeY;
	int						_writeMode;
	int						_mapData[MAP_WIDTH][MAP_HEIGHT];
	POINT				_mousePt;
	unique_ptr<UI>	_save_UI;
};