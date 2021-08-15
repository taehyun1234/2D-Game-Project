#pragma once
#include "Scene.h"
#include "UI.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(HWND hWnd) override;
	virtual SCENE Update(HWND hWnd) override;
	virtual void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam) override;
	virtual void Draw(HWND hWnd, HDC hdc) override;
	virtual void ResetScene() override;
private:
	CImage				_img_Title;
	unique_ptr<UI>	_start_UI;
	unique_ptr<UI>	_maptool_UI;
};

