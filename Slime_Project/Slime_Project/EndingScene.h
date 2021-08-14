#pragma once
#include "Scene.h"
#include "UI.h"
class EndingScene : public Scene
{
public:
	EndingScene();
	virtual ~EndingScene();

	void Init(HWND hWnd);
	SCENE Update(HWND hWnd);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void Draw(HWND hWnd, HDC hdc);
	void ResetScene();
private:
	CImage				_img_Title;
	unique_ptr<UI>	_Restart_UI;
	POINT				_mousePt;
};

