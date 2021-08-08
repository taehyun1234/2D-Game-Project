#include "pch.h"
#include "MainScene.h"
#include "Time.h"

MainScene::MainScene()
{
	_curIdx = SCENE::SCENE_MAIN;
	_player = make_unique<Player>();				
	_house = make_unique < House>();
	_ai = make_unique<AStar>();

	_time = 0;
	_timeCnt = 0;
	_openMap.Load(L"..\\Resources\\images\\Main\\Open.png");
	_closeMap.Load(L"..\\Resources\\images\\Main\\Close.png");
	printf("mainScene 생성 \n");
	_player_Curpos_x = 0;
	_player_Curpos_y = 0;
	_player_Prevpos_x = 0;
	_player_Prevpos_y = 0;
	_monsterGenCnt = 0;
}

MainScene::~MainScene()
{
	printf("mainScene 소멸 \n");
}

void MainScene::Init(HWND hWnd)
{
	_curIdx = SCENE::SCENE_MAIN;
	_time = 0;
	_aniSpeed = 0.1;
	RECT rect;
	GetClientRect(hWnd, &rect);

	_tileSizeX = (rect.right - rect.left) / MAP_WIDTH;
	_tileSizeY = (rect.bottom - rect.top) / MAP_HEIGHT;

	ResetScene();
}

SCENE MainScene::Update(HWND hWnd)
{
	_player->Update(_mapData,_tileSizeX,_tileSizeY);
		
	if (_monsterAttack.size() > 0) {
		for (list<shared_ptr<MonsterAttack>>::iterator it = _monsterAttack.begin(); it != _monsterAttack.end();)
		{
			shared_ptr<MonsterAttack> arr = *it;
			arr->Update();
			int x, y;
			arr->GetCoord(x, y);

//			_player->Hit(x, y);

			if (arr->GetAliveTime() > 50)
			{
				_monsterAttack.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}

	if (_monsterGenCnt > 300)
	{
		shared_ptr<Monster> m = make_shared<Monster>();
		m->Init(20 * _tileSizeX, 13 * _tileSizeY);
		m->ChangeTargetPos(_coordiList);
		_monsterList.push_back(m);
		_monsterGenCnt = 0;		
	}
	else
	{
		_monsterGenCnt++;
	}


	if (_arrowList.size() > 0) {
		for (list<shared_ptr<Arrow>>::iterator a_it = _arrowList.begin(); a_it != _arrowList.end();)
		{
			bool hit = false;
			shared_ptr<Arrow> arr = *a_it;
			arr->Update();
			int x, y;
			arr->GetCoord(x, y);
			for (auto p : _monsterList)
			{
				hit = p->Hit(x, y);
				if (hit == true)
				{
					_arrowList.erase(a_it++);
					break;
				}
			}
			if (hit == true)
			{
				break;
			}
			if (arr->GetAliveTime() > 50)
			{
				_arrowList.erase(a_it++);
			}
			else
			{
				a_it++;
			}
		}
	}
	

	for (list<shared_ptr<Monster>>::iterator it = _monsterList.begin(); it != _monsterList.end();)
	{
		(*it)->Update(_tileSizeX, _tileSizeY);
		int px, py;
		int mx, my;

		_player->GetPos(px, py);
		(*it)->GetPos(mx, my);
		if (sqrt((px - mx) * (px - mx) + (py - my) * (py - my)) < 100)
		{
			_monsterAttackCnt++;
			if (_monsterAttackCnt > 50)
			{
				shared_ptr<MonsterAttack> maLeft = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maRight = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maFront = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maBack = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maLeftFront = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maLeftBack = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maRightFront = make_shared<MonsterAttack>();
				shared_ptr<MonsterAttack> maRightBack = make_shared<MonsterAttack>();

				maLeft->Init(mx, my, LEFT);
				maRight->Init(mx, my, RIGHT);
				maFront->Init(mx, my, FRONT);
				maBack->Init(mx, my, BACK);
				maLeftFront->Init(mx, my, LEFT_FRONT);
				maLeftBack->Init(mx, my, LEFT_BACK);
				maRightFront->Init(mx, my, RIGHT_FRONT);
				maRightBack->Init(mx, my, RIGHT_BACK);

				_monsterAttack.push_back(maLeft);
				_monsterAttack.push_back(maRight);
				_monsterAttack.push_back(maFront);
				_monsterAttack.push_back(maBack);
				_monsterAttack.push_back(maLeftFront);
				_monsterAttack.push_back(maLeftBack);
				_monsterAttack.push_back(maRightFront);
				_monsterAttack.push_back(maRightBack);
				_monsterAttackCnt = 0;
			}
		}
		int x, y;
		_house->GetCoord(x, y);
		(*it)->Attack_House(x, y);

		if ((*it)->GetHP() < 0)
		{
			_monsterList.erase(it++);
			// 지우는 조건
		}
		else
		{
			it++;
		}
	}
	
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
		case VK_SPACE:
			shared_ptr<Arrow> arrow = make_shared<Arrow>();
			int x, y, dir;
			_player->GetPos(x, y, dir);
			arrow->Init(x, y, dir);

			_arrowList.push_back(arrow);
			break;
		}
	}	
}

void MainScene::Draw(HWND hWnd, HDC hdc)
{
	_time += static_cast<float>(GET_SINGLE(Time)->GetDeltaTime());
	DrawMap(hdc);

	if (_time > 1.f * _aniSpeed)
	{
		_timeCnt++;
		_time = 0;
	}

	_house->Draw(hdc);

	for (shared_ptr<Monster> p: _monsterList)
	{
		p->Draw(hdc, static_cast<int>(_timeCnt));
	}
	_player->Draw(hdc, static_cast<int>(_timeCnt));
	for (shared_ptr<Arrow> p : _arrowList)
	{
		p->Draw(hdc);
	}

	for (shared_ptr<MonsterAttack> p : _monsterAttack)
	{
		p->Draw(hdc);
	}

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

	_coordiList = _ai->ReturnPath(_mapData, 20, 13, 3, 3);
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
	
	//for (auto p : _coordiList)
	//{
	//	Rectangle(hdc, p->x * _tileSizeX, p->y * _tileSizeY, p->x * _tileSizeX + _tileSizeX, p->y * _tileSizeY + _tileSizeY);
	//}

}

void MainScene::ResetScene()
{
	LoadMap();
	//20 13
	_house->Init(3 * _tileSizeX, 3 * _tileSizeY);
	_player->Init(3 * _tileSizeX, 3 * _tileSizeY);


	for (list<shared_ptr<Monster>>::iterator it = _monsterList.begin(); it != _monsterList.end();)
	{
		_monsterList.erase(it++);
	}

}

