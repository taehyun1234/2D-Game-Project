#pragma once
#include "Scene.h"
class MaptoolScene : public Scene
{
public:
	void Init();
	SCENE Update(HWND hWnd);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void Draw(HWND hWnd, HDC hdc);
	void ResetScene();
private:
		
};

