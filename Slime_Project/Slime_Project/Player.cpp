#include "pch.h"
#include "Player.h"

Player::Player()
{
	_player_Img_Basic.Load(L"..\\Resources\\images\\Main\\그린엘프_기본.png");
	_player_Img_Attack.Load(L"..\\Resources\\images\\Main\\그린엘프_공격.png");
	_x = 0, _y = 0, _width = 64, _height = 64;
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

void Player::Update(int mapData[MAP_WIDTH][MAP_HEIGHT], int tilesizeX, int tilesizeY)
{
	// 충돌체크
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (mapData[i][j] == CLOSE)
			{
				int left = i * tilesizeX;
				int right = left + tilesizeX;
				int top = j * tilesizeY;
				int bottom = top + tilesizeY;

				if (!(_y > bottom || _y + _height < top))
				{
					if ((_x < right) && (_x + _width > left) )
					{
						if (_playerDirection == LEFT)
							_x += _playerSpeed;
						if (_playerDirection == RIGHT)
							_x -= _playerSpeed;
					}
				}


				if (!(_x + _width < left || _x > right))
				{
					if ((_y < bottom) && (_y + _height > top))
					{
						if (_playerDirection == FRONT)
							_y -= _playerSpeed;
						if (_playerDirection == BACK)
							_y += _playerSpeed;
					}
				}
			}
		}
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
	
	if (_playerAttack == true)
	{
		_playerAttack_cnt++;
		if (_playerAttack_cnt > 10)
		{
			_playerAttack_cnt = 0;
			_playerAttack = false;
		}
	}
}

void Player::Init(int x, int y)
{
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
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

void Player::GetPos(int& x, int& y, int& dir)
{
	x = _x;
	y = _y;
	dir = _playerDirection;
}

void Player::Draw(HDC hdc, int aniCount)
{
	int anicount = aniCount % 4;

	if (_boundingBox == true)
	{
		Rectangle(hdc, _x, _y, _x + _width, _y + _height);
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
