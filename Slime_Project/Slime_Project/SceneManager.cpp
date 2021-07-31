#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "MaptoolScene.h"

SceneManager::SceneManager()
{
	_curSceneIdx = SCENE_TITLE;

	unique_ptr<Scene> titleScene = make_unique<TitleScene>();						// memory leak
	unique_ptr<Scene> mainScene = make_unique<MainScene>();					// memory leak
	unique_ptr<Scene> maptoolScene = make_unique<MaptoolScene>();			// memory leak

	_scenes[SCENE_TITLE] = move(titleScene);
	_scenes[SCENE_MAIN] = move(mainScene);
	_scenes[SCENE_MAPTOOL] = move(maptoolScene);
	// scene�� �ʱ�ȭ
}


SceneManager::~SceneManager()
{
}

void SceneManager::Update(HWND hWnd)
{
	SCENE curScene = _scenes[_curSceneIdx]->Update(hWnd);

	if (curScene != _curSceneIdx)			// ���� ���� ��ȯ�� ���� �ٸ�. �׷��� Scene Change
	{
		_scenes[curScene]->Init(hWnd);					// �ٲ� �� Init
		_scenes[_curSceneIdx]->ResetScene();	// ���� �� Reset
		_curSceneIdx = curScene;
	}
}

void SceneManager::Draw(HWND hWnd, HDC hdc)
{
	_scenes[_curSceneIdx]->Draw(hWnd, hdc);

}

void SceneManager::KeyInput(HWND hWnd, UINT keyMessage,WPARAM wParam, LPARAM lParam)
{
	_scenes[_curSceneIdx]->Input(hWnd, keyMessage,wParam,lParam);
}
