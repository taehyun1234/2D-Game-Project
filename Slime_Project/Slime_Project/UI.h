#pragma once
class UI
{
public:
	UI(int x = 0, int y = 0, int width = 0, int height = 0);
	~UI();
	
	void  SetImage(LPCTSTR str);
	void	Draw(HDC hdc);
	void	Update(POINT mousePt);
	bool	GetCollide();
private:
	int _x, _y, _width, _height;
	bool _collide;

	CImage _img;
};