#pragma once

enum DIR
{
	FRONT	= 0,
	RIGHT,
	LEFT,
	BACK
};

class Player
{
public:
	Player();
	~Player();

	void Update(int mapData[MAP_WIDTH][MAP_HEIGHT], int tilesizeX, int tilesizeY);
	void Init(int x, int y);
	void Draw(HDC hdc, int aniCount);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);


private:
	int hp;
	int _x, _y, _width, _height;
	bool		_playermove;
	int			_playerSpeed;
	bool		_playerAttack;
	bool		_boundingBox;
	DIR		_playerDirection;
	CImage	_player_Img_Basic;
	CImage	_player_Img_Attack;
};