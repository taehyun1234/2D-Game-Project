#pragma once

enum DIR
{
	RIGHT = 0,
	LEFT,
	FRONT,
	BACK
};

class Arrow
{
public:
	Arrow();
	~Arrow();

	void Init(int x, int y,int dir);
	void Draw(HDC hdc);
	void Update();

private:
	int _x, _y;
	int _width, _height;
	int _dir;
	int _speed;
	CImage _arrowImg;
};