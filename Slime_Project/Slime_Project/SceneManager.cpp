#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "MaptoolScene.h"

SceneManager::SceneManager()
{
	printf("Scenemanager »ý¼º \n");
}


SceneManager::~SceneManager()
{
	printf("Scenemanager ¼Ò¸ê \n");
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

	// sceneµé ÃÊ±âÈ­
}

void SceneManager::Update(HWND hWnd)
{
	SCENE curScene = _scenes[_curSceneIdx]->Update(hWnd);

	if (curScene != _curSceneIdx)			// ÇöÀç ¾À°ú ¹ÝÈ¯µÈ ¾ÀÀÌ ´Ù¸§. ±×·¯¸é Scene Change
	{
		_scenes[curScene]->Init(hWnd);					// ¹Ù²ð ¾À Init
		_scenes[_curSceneIdx]->ResetScene();	// ÀüÀÇ ¾À Reset
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
