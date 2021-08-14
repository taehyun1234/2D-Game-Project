#include "pch.h"

bool Collide2DCircle(float x1, float y1, float x2, float y2, float r)
{
  	bool bRet = false;

	float deltaX = x1 - x2;
	float deltaY = y1 - y2;

	float length = sqrt(deltaX * deltaX + deltaY * deltaY);
	
	if (length < r)
	{
		bRet = true;
	}

	return bRet;
}

bool RectCollision(int x1,int y1,int width1, int height1, int x2, int y2, int width2, int height2)
{
	if (x1 <= x2 + width2 &&
		x1 + width1 >= x2 &&
		y1 - height1 <= y2 &&
		y1 >= y2 - height2)
		return true;

	return false;
}

bool OutOfScreen(int x, int y, int width, int height)
{
	bool bRet = false;

	if (x < 0)
	{
		bRet = true;
	}

	if (y < 0)
	{
		bRet = true;
	}
	
	if (x + width > WND_WIDTH)
	{
		bRet = true;
	}

	if (y + height > WND_HEIGHT - 30)
	{
		bRet = true;
	}

	return bRet;
}