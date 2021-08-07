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