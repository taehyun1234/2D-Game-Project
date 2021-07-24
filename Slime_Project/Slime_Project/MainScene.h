#pragma once
#include "Scene.h"
#include "Boss.h"
class MainScene :	public Scene
{
public:
	MainScene();
	~MainScene();

	void Init();
	SCENE Update(HWND hWnd);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void Draw(HWND hWnd, HDC hdc);
	void ResetScene();
private:
	float									_time;
	int										_aniSpeed;
	unique_ptr<Boss>					_boss;
};