#include "pch.h"
#include "EndingScene.h"

EndingScene::EndingScene()
{
	_img_Title.Load(L"..\\Resources\\images\\Ending\\gameover.jpg");
}

EndingScene::~EndingScene()
{
}

void EndingScene::Init(HWND hWnd)
{
	_curIdx = SCENE::SCENE_ENDING;
	_Restart_UI = make_unique<UI>(600, 200, 400, 200);
	_Restart_UI->SetImage(L"..\\Resources\\images\\Ending\\Restart_UI.png");
}

SCENE EndingScene::Update(HWND hWnd)
{
	::GetCursorPos(&_mousePt);
	::ScreenToClient(hWnd, &_mousePt);
	_Restart_UI->Update(_mousePt);
	return _curIdx;
}

void EndingScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	switch (keyMessage)
	{
	case WM_LBUTTONDOWN:
		if (_Restart_UI->GetCollide() == true)
			_curIdx = SCENE::SCENE_TITLE;
		break;
	}
}

void EndingScene::Draw(HWND hWnd, HDC hdc)
{
	_img_Title.Draw(hdc, 0, 0, WND_WIDTH, WND_HEIGHT,0,0,1280,720);
	_Restart_UI->Draw(hdc);
}

void EndingScene::ResetScene()
{
}
