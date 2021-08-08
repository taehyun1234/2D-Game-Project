#pragma once

class Player
{
public:
	Player();
	~Player();

	void Update(int mapData[MAP_WIDTH][MAP_HEIGHT], int tilesizeX, int tilesizeY);
	void Init(int x, int y);
	void Draw(HDC hdc, int aniCount);
	void Input(HWND hWnd, UINT keyMessage, WPARAM wParam, LPARAM lParam);
	void GetPos(int& x, int& y);
	void GetPos(int& x, int& y, int& dir);
	void GetTilePos(int& x, int& y, int tileSizeX, int tileSizeY);

private:
	int										_hp;
	int										_x, _y, _width, _height;
	bool									_playermove;
	int										_playerSpeed;
	bool									_playerAttack;
	bool									_boundingBox;
	int										_playerAttack_cnt;


	int										_playerDirection;
	CImage								_player_Img_Basic;
	CImage								_player_Img_Attack;
};