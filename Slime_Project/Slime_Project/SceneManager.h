#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void										Update(HWND hWnd);								// 업데이트 하면서, 현재 씬의 업데이트 반환 값이 0이 아닐 경우 scene 체인지
	void										Draw(HWND hWnd, HDC hdc);
	void										KeyInput(HWND hWnd,UINT keyMessage, WPARAM wParam, LPARAM lParam);

private:
	unique_ptr<Scene>					_scenes[SCENE_COUNT];

	SCENE									_curSceneIdx;
};