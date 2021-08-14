#include "pch.h"
#include "Player.h"

Player::Player()
{
	_player_Img_Basic.Load(L"..\\Resources\\images\\Main\\그린엘프_기본.png");
	_player_Img_Attack.Load(L"..\\Resources\\images\\Main\\그린엘프_공격.png");
	_hpBar.Load(L"..\\Resources\\images\\Main\\hp_bar.png");
	_hpfill.Load(L"..\\Resources\\images\\Main\\hp.png");
	_x = 0, _y = 0, _width = 49, _height = 49;
	_hp = 1000;
	_playerAttack = false;
	_playerDirection = FRONT;
	_playerSpeed = 1;
	_boundingBox = false;
	_playermove = false;
	_playerAttack_cnt = 0;
}

Player::~Player()
{
}

bool Player::Update(int mapData[MAP_WIDTH][MAP_HEIGHT], int tilesizeX, int tilesizeY)
{
	bool bRet = false;
	if (_hp <= 0)
	{
		bRet = true;
	}

	if (_playermove == true)
	{
		if (_playerDirection == LEFT)
		{
			_x -= _playerSpeed;
		}
		else if (_playerDirection == RIGHT)
		{
			_x += _playerSpeed;
		}
		else if (_playerDirection == BACK)
		{
			_y -= _playerSpeed;
		}
		else if (_playerDirection == FRONT)
		{
			_y += _playerSpeed;
		}
	}


	if (OutOfScreen(_x,_y,_width,_height) == true)
	{
		if (_playerDirection == LEFT)
		{
			_x += _playerSpeed;
		}
		else if (_playerDirection == RIGHT)
		{
			_x -= _playerSpeed;
		}
		else if (_playerDirection == BACK)
		{
			_y += _playerSpeed;
		}
		else if (_playerDirection == FRONT)
		{
			_y -= _playerSpeed;
		}
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (mapData[i][j] == CLOSE)
			{
				int left = i * tilesizeX;
				int top = j * tilesizeY;

				if (RectCollision(_x, _y, _width, _height, left, top, tilesizeX, tilesizeY) == true)
				{
					if (_playerDirection == LEFT)
					{
						_x += _playerSpeed;
					}
					else if (_playerDirection == RIGHT)
					{
						_x -= _playerSpeed;
					}
					else if (_playerDirection == BACK)
					{
						_y += _playerSpeed;
					}
					else if (_playerDirection == FRONT)
					{
						_y -= _playerSpeed;
					}
				}
			}
		}
	}


	if (_playerAttack == true)
	{
		_playerAttack_cnt++;
		if (_playerAttack_cnt > 10)
		{
			_playerAttack_cnt = 0;
			_playerAttack = false;
		}
	}

	return bRet;
}

void Player::Init(int x, int y)
{
	_x = x;
	_y = y;
	_hp = 1000;
	_playerAttack = false;
	_playerDirection = FRONT;
	_playerSpeed = 3;
}


void Player::Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	switch (keyMessage)
	{
	case WM_CHAR:		
	{
		switch (wParam)
		{
		case 'M':
			if (_boundingBox == false)
				_boundingBox = true;
			else
				_boundingBox = false;
			break;
		case 'W':
		case 'w':
			_playermove = true;
			_playerDirection = BACK;
			break;
		case 'A':
		case 'a':
			_playermove = true;
			_playerDirection = LEFT;
			break;
		case 'S':
		case 's':
			_playermove = true;
			_playerDirection = FRONT;
			break;
		case 'D':
		case 'd':
			_playermove = true;
			_playerDirection = RIGHT;
			break;
		}
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_SPACE) < 0)
		{
			_playerAttack = true;
		}
		break;
	}
	case WM_KEYUP:
		_playermove = false;
		break;
	}
}

void Player::GetPos(int& x, int& y)
{
	x = _x;
	y = _y;
}
void Player::GetPos(int& x, int& y, int& dir)
{
	x = _x;
	y = _y;
	dir = _playerDirection;
}

void Player::GetTilePos(int& x, int& y, int tileSizeX, int tileSizeY)
{
	x = (_x - _width / 2) / tileSizeX;
	y = (_y - _height / 2) / tileSizeY;

}

bool Player::Hit(int x, int y)
{
	bool bRet = false;
	if (Collide2DCircle(_x, _y, x, y, 30) == true)
	{
		_hit = true;
		_hp -= 50;
		bRet = true;
	}
	return bRet;
}

void Player::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 4;

	if (_boundingBox == true)
	{
		Rectangle(hdc, _x, _y, _x + _width, _y + _height);
	}

	int bar = (1000 - _hp) * 40 / 1000;

	if (40 - bar > 0) 
	{
		_hpBar.Draw(hdc, _x, _y - _height / 3, 40, 10, 0, 0, 901, 241);
		_hpfill.Draw(hdc, _x, _y - _height / 3, 40 - bar, 10, 0, 0, 901, 241);
	}

	if (_playermove == true)
	{
		if (_playerAttack == false)		//공격 중이지 않을 때
		{
			switch (_playerDirection)
			{
			case FRONT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 0, 64, 64);
				break;
			case LEFT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 64, 64, 64);
				break;
			case RIGHT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 128, 64, 64);
				break;
			case BACK:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 192, 64, 64);
				break;
			}
		}
		else
		{
			switch (_playerDirection)
			{
			case FRONT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 0, 64, 64);
				break;
			case LEFT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 64, 64, 64);
				break;
			case RIGHT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 128, 64, 64);
				break;
			case BACK:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 192, 64, 64);
				break;
			}
		}
	}
	else
	{
		if (_playerAttack == true)		
		{
			switch (_playerDirection)
			{
			case FRONT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 0, 64, 64);
				break;
			case LEFT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 64, 64, 64);
				break;
			case RIGHT:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 128, 64, 64);
				break;
			case BACK:
				_player_Img_Attack.Draw(hdc, _x, _y, _width, _height, 64 * anicount, 192, 64, 64);
				break;
			}
		}
		else
		{
			switch (_playerDirection)
			{
			case FRONT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64, 0, 64, 64);
				break;
			case LEFT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64, 64, 64, 64);
				break;
			case RIGHT:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64, 128, 64, 64);
				break;
			case BACK:
				_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64, 192, 64, 64);
				break;
			}
		}
	}

}
