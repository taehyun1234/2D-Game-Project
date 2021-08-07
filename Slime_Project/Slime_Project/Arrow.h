#pragma once

class Arrow
{
public:
	Arrow();
	~Arrow();

	void	Init(int x, int y,int dir);
	void	Draw(HDC hdc);
	void	Update();
	void	GetCoord(int& x, int& y);
	int		GetAliveTime();

private:
	int _x, _y;
	int _width, _height;
	int _dir;
	int _speed;
	int _aliveTime;
	CImage _arrowImg;
};