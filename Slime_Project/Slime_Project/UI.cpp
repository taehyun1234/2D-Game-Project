#include "pch.h"
#include "UI.h"

UI::UI(int x, int y, int width, int height)
{
	_collide = false;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

UI::~UI()
{
}

void UI::SetImage(LPCTSTR str)
{
	_img.Load(str);
}

void UI::Draw(HDC hdc)
{
	if(_collide == false)
		_img.Draw(hdc, _x, _y, _width, _height);
	else
		_img.AlphaBlend(hdc, _x, _y, 200);
}

void UI::Update(POINT mousePt)
{
	_collide = false;
	
	int left = _x;
	int right = _x + _width;
	int top = _y;
	int bottom = _y + _height;

	if(mousePt.x < right && mousePt.x > left)
	{
		if (mousePt.y > top && mousePt.y < bottom)
		{
			_collide = true;
		}
	}
}

bool UI::GetCollide()
{
	return _collide;
}
