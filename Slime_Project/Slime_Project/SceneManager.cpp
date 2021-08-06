#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "MaptoolScene.h"

SceneManager::SceneManager()
{
	printf("Scenemanager ���� \n");
}


SceneManager::~SceneManager()
{
	printf("Scenemanager �Ҹ� \n");
}

void SceneManager::Init(HWND hWnd)
{
	_curSceneIdx = SCENE_TITLE;

	_scenes[SCENE_TITLE] = make_unique<TitleScene>();
	_scenes[SCENE_MAIN] = make_unique<MainScene>();
	_scenes[SCENE_MAPTOOL] = make_unique<MaptoolScene>();

	for (int i = 0; i < SCENE_COUNT; i++)
	{
		_scenes[i]->Init(hWnd);
	}

	// scene�� �ʱ�ȭ
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
