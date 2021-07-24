#include "pch.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	_img_Title.Load(L"..\\Resources\\images\\Title\\Ÿ��Ʋȭ��.png");
	_start_UI = make_unique<UI>(600, 380,400,200);
	_start_UI->SetImage(L"..\\Resources\\images\\Title\\GameStart_UI.png");
	_maptool_UI = make_unique<UI>(600, 650, 400, 200);
	_maptool_UI->SetImage(L"..\\Resources\\images\\Title\\MapTool_UI.png");
}

void TitleScene::Init(HWND hWnd)
{
	_curIdx = SCENE::SCENE_TITLE;
}

SCENE TitleScene::Update(HWND hWnd)
{
	POINT p;	
	::GetCursorPos(&p);
	::ScreenToClient(hWnd, &p);
	_start_UI->Update(p);
	_maptool_UI->Update(p);
	// UI Ŭ���ϵ���

	return _curIdx;
}

void TitleScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	switch (keyMessage)
	{
	case WM_LBUTTONDOWN:
		if (_start_UI->GetCollide() == true)
			_curIdx = SCENE::SCENE_MAIN;
		if(_maptool_UI->GetCollide() == true)
			_curIdx = SCENE::SCENE_MAPTOOL;
		break;
	}
}

void TitleScene::Draw(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	// ������ ũ�� �޾ƿ�

	_img_Title.StretchBlt(hdc, 0, 0,rect.right-rect.left, rect.bottom - rect.top);
	// Title Image �׸���
	_start_UI->Draw(hdc);
	// ���� ��ŸƮ UI �׸���
	_maptool_UI->Draw(hdc);
	// ���� ��ŸƮ UI �׸���
}

void TitleScene::ResetScene()
{
}
