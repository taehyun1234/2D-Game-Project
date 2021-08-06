#include "pch.h"
#include "Arrow.h"

Arrow::Arrow()
{
	_arrowImg.Load(L"..\\Resources\\images\\Main\\arrow.png");
	_width = 0;
	_height = 0;
}

Arrow::~Arrow()
{
}

void Arrow::Init(int x, int y, int dir)
{
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
	_dir = dir;
	_speed = 1;
}

void Arrow::Draw(HDC hdc)
{
	_arrowImg.Draw(hdc, _x, _y, _width, _height, 300, 300 * _dir,300,300);

//	_player_Img_Basic.Draw(hdc, _x, _y, _width, _height, 64, 192, 64, 64);
}

void Arrow::Update()
{
	switch (_dir)
	{
	case RIGHT:
		_x += _speed;
		break;
	case LEFT:
		_x -= _speed;
		break;
	case FRONT:
		_y += _speed;
		break;
	case BACK:
		_y -= _speed;
		break;
	}
}
