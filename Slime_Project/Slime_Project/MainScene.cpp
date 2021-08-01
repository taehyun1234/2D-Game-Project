#include "pch.h"
#include "MainScene.h"
#include "Time.h"

MainScene::MainScene()
{
	_curIdx = SCENE::SCENE_MAIN;
	_boss = make_unique<Boss>();						// memory leak
	_player = make_unique<Player>();					// memory leak
	_time = 0;
	_openMap.Load(L"..\\Resources\\images\\Main\\Open.png");
	_closeMap.Load(L"..\\Resources\\images\\Main\\Close.png");
}

MainScene::~MainScene()
{
}

void MainScene::Init(HWND hWnd)
{
	_curIdx = SCENE::SCENE_MAIN;
	_time = 0;
	_aniSpeed = 10;
	LoadMap();
	RECT rect;
	GetClientRect(hWnd, &rect);

	_tileSizeX = (rect.right - rect.left) / MAP_WIDTH;
	_tileSizeY = (rect.bottom - rect.top) / MAP_HEIGHT;

	//20 13
	_boss->Init(20 * _tileSizeX, 13 * _tileSizeY);
	_player->Init(3 * _tileSizeX, 3 * _tileSizeY);
}

SCENE MainScene::Update(HWND hWnd)
{
	_boss->Update(_tileSizeX,_tileSizeY);
	_player->Update(_mapData,_tileSizeX,_tileSizeY);
	return _curIdx;
}

void MainScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	_player->Input(hWnd, keyMessage, wParam, lParam);

	switch (keyMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			_curIdx = SCENE::SCENE_TITLE;
			break;
		}
	}	
}

void MainScene::Draw(HWND hWnd, HDC hdc)
{
	_time += static_cast<float>(GET_SINGLE(Time)->GetDeltaTime());
	DrawMap(hdc);
	_boss->Draw(hdc, static_cast<int>(_time * _aniSpeed));
	_player->Draw(hdc, static_cast<int>(_time * _aniSpeed));
}

void MainScene::LoadMap()
{
	ifstream readFile;
	readFile.open(L"..\\Resources\\Map\\mapFile.txt");

	if (readFile.is_open())
	{
		int w = 0, h = 0;
		char c;
		while (readFile.get(c))
		{
			if (!(c == '0' || c == '1' || c == '2' || c == '3'))		// 공백문자
			{
				continue;
			}

			_mapData[w][h] = atoi(&c);
			if (w < MAP_WIDTH - 1)
			{
				w++;
			}
			else
			{
				w=0;
				h++;
			}
		}
	}

	_boss->AStar(_mapData);
}

void MainScene::DrawMap(HDC hdc)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j] == OPEN || _mapData[i][j] == BOSS || _mapData[i][j] == PLAYER)
			{
				_openMap.StretchBlt(hdc, 
					i * _tileSizeX, j * _tileSizeY, _tileSizeX, _tileSizeY
					, 0, 0, 57,57);
			}
			if (_mapData[i][j] == CLOSE)
			{
				_closeMap.StretchBlt(hdc,
					i * _tileSizeX, j * _tileSizeY, _tileSizeX, _tileSizeY
					, 0, 0, 57, 57);
			}
		}
	}
}

void MainScene::ResetScene()
{
}
