#pragma once
class House
{
public:
	House();
	~House();

	void Draw(HDC hdc);
	void Init(int x, int y);
	bool Damaged(int damage);
	void GetCoord(int& x, int& y);
private:
	int _hp;
	int _x, _y,_width,_height;
	CImage								_houseImg;

	CImage								_hpBar;
	CImage								_hpfill;
};