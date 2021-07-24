#pragma once
#include "pch.h"
class Scene
{
public:
	virtual void Init() = 0;
	virtual SCENE Update(HWND hWnd) = 0;
	virtual void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Draw(HWND hWnd, HDC hdc) = 0;
	virtual void ResetScene() = 0;
protected:
	SCENE _curIdx;
};