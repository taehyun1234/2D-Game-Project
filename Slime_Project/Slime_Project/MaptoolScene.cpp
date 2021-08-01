#include "pch.h"
#include "MaptoolScene.h"

MaptoolScene::MaptoolScene()
{
}

MaptoolScene::~MaptoolScene()
{
}

void MaptoolScene::Init(HWND hWnd)
{
	_curIdx = SCENE::SCENE_MAPTOOL;

	_save_UI = make_unique<UI>(1150, 380,400,200);
	_save_UI->SetImage(L"..\\Resources\\images\\Maptool\\Save.png");

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			_mapData[i][j] = OPEN;
		}
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		_mapData[i][0] = CLOSE;
		_mapData[i][MAP_HEIGHT-1] = CLOSE;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		_mapData[0][i] = CLOSE;
		_mapData[MAP_WIDTH-1][i] = CLOSE;
	}

	_writeMode = CLOSE;	
	_mouseDown = false;
	_mapData[3][3] = PLAYER;
	_mapData[20][13] = BOSS;

	RECT rect;
	GetClientRect(hWnd, &rect);

	_tileSizeX = 35;//(rect.right - rect.left) / MAP_WIDTH;
	_tileSizeY = 35;//(rect.bottom - rect.top) / MAP_HEIGHT;

}

SCENE MaptoolScene::Update(HWND hWnd)
{
	::GetCursorPos(&_mousePt);
	::ScreenToClient(hWnd, &_mousePt);

	_save_UI->Update(_mousePt);

	return _curIdx;
}

void MaptoolScene::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	switch (keyMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			_curIdx = SCENE::SCENE_TITLE;
			break;
		}
	case WM_CHAR:
		switch (wParam)
		{
		case 'O':		//Open
		case 'o':
			_writeMode = OPEN;
			break;
		case 'C':		//Close
		case 'c':
			_writeMode = CLOSE;
			break;
		}
	case WM_MOUSEMOVE:
		if (_mouseDown == true) 
		{
			for (int i = 0; i < MAP_WIDTH; i++)
			{
				for (int j = 0; j < MAP_HEIGHT; j++)
				{
					int left = i * _tileSizeX;
					int right = left + _tileSizeX;
					int top = j * _tileSizeY;
					int bottom = top + _tileSizeY;

					if (_mousePt.x < right && _mousePt.x > left)
					{
						if (_mousePt.y > top && _mousePt.y < bottom)
						{
							if (!(_mapData[i][j] == PLAYER || _mapData[i][j] == BOSS))
							{
								_mapData[i][j] = _writeMode;
							}
							break;
						}
					}
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		_mouseDown = false;
		break;
	case WM_LBUTTONDOWN:
		_mouseDown = true;
		if (_save_UI->GetCollide() == true)
			SaveData();
		break;
	}
}

void MaptoolScene::Draw(HWND hWnd, HDC hdc)
{
	HBRUSH hBrush, oldBrush;

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j] == OPEN)
			{
				hBrush = CreateSolidBrush(RGB(155, 155, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i *_tileSizeX, j *_tileSizeY, i * _tileSizeX + _tileSizeX, j * _tileSizeY + _tileSizeY);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
			else if (_mapData[i][j] == CLOSE)
			{
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i * _tileSizeX, j * _tileSizeY, i * _tileSizeX + _tileSizeX, j * _tileSizeY + _tileSizeY);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
			else if (_mapData[i][j] == PLAYER)
			{
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i * _tileSizeX, j * _tileSizeY, i * _tileSizeX + _tileSizeX, j * _tileSizeY + _tileSizeY);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
			else if (_mapData[i][j] == BOSS)
			{
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i * _tileSizeX, j * _tileSizeY, i * _tileSizeX + _tileSizeX, j * _tileSizeY + _tileSizeY);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
	}

	_save_UI->Draw(hdc);
}

void MaptoolScene::ResetScene()
{
}

void MaptoolScene::SaveData()
{
	ofstream writeFile(L"..\\Resources\\Map\\mapFile.txt");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			writeFile << _mapData[j][i];
		}
		writeFile << endl;
	}
	writeFile.close();
}