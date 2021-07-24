#pragma once
#include "Time.h"
#include "SceneManager.h"
class GameClient
{
public:
	GameClient();
	~GameClient();

	void										Init(HWND win_info);
	void										Update();

	void										Draw();
	void										KeyInput(UINT keyMessage,WPARAM wParam, LPARAM lParam );
	
	HWND									_hWnd;
private:
	unique_ptr<SceneManager>		_sceneManager;
};

