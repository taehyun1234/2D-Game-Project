#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void										Update(HWND hWnd);								// ������Ʈ �ϸ鼭, ���� ���� ������Ʈ ��ȯ ���� 0�� �ƴ� ��� scene ü����
	void										Draw(HWND hWnd, HDC hdc);
	void										KeyInput(HWND hWnd,UINT keyMessage, WPARAM wParam, LPARAM lParam);

private:
	unique_ptr<Scene>					_scenes[SCENE_COUNT];

	SCENE									_curSceneIdx;
};