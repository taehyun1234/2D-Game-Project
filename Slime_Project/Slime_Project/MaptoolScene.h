#pragma once
#include "Scene.h"
#include "UI.h"
class MaptoolScene : public Scene
{
public:
	MaptoolScene();
	virtual ~MaptoolScene();

	virtual void			Init(HWND hWnd) override;
	virtual SCENE		Update(HWND hWnd) override;
	virtual void			Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam) override;
	virtual void			Draw(HWND hWnd, HDC hdc) override;
	virtual void			ResetScene() override;
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