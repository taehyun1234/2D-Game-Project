#include "pch.h"
#include "MaptoolScene.h"

void MaptoolScene::Init()
{
	_curIdx = SCENE::SCENE_MAPTOOL;
}

SCENE MaptoolScene::Update(HWND hWnd)
{
	return _curIdx;
}

void MaptoolScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	switch (keyMessage)
	{
	case WM_LBUTTONDOWN:
		break;
	}
}

void MaptoolScene::Draw(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	int sizeX = (rect.right - rect.left) / 16;
	int sizeY = (rect.bottom - rect.top) / 9;
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Rectangle(hdc, i *sizeX, j *sizeY, i * sizeX + sizeX, j * sizeY + sizeY);
		}
	}

}

void MaptoolScene::ResetScene()
{
}
