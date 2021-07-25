#pragma once
class Boss
{
public:
	Boss();
	~Boss();

	void Update();
	void Init(int x, int y);
	void Draw(HDC hdc, int aniCount);
	void AStar();

private:
	int hp;
	int _x, _y, _width, _height;
	CImage _bossImg;
};