#include "pch.h"
#include "MainScene.h"
#include "Time.h"

MainScene::MainScene()
{
	_curIdx = SCENE::SCENE_MAIN;
	_boss = make_unique<Boss>();
	_time = 0;
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	_curIdx = SCENE::SCENE_MAIN;
	_time = 0;
	_aniSpeed = 10;
}

SCENE MainScene::Update(HWND hWnd)
{
	_boss->Update();
	return _curIdx;
}

void MainScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
}

void MainScene::Draw(HWND hWnd, HDC hdc)
{
	_time += static_cast<float>(GET_SINGLE(Time)->GetDeltaTime());
	_boss->Draw(hdc, _time * _aniSpeed);
}

void MainScene::ResetScene()
{
}
