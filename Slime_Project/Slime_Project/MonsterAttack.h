#pragma once
class MonsterAttack
{
public:
	MonsterAttack();
	~MonsterAttack();


	void	Init(int x, int y, int dir);
	void	Draw(HDC hdc);
	void	Update();
	void	GetCoord(int& x, int& y);
	int		GetAliveTime();
private:
	CImage _img;
	CImage _img2;
	int _x, _y;
	int _width, _height;
	int _aliveTime;
	int _dir;
	int _speed;
	int _aniCount;
};

