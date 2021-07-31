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
	// sceneµé ÃÊ±âÈ­
}


SceneManager::~SceneManager()
{
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
