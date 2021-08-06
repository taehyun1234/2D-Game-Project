#include "pch.h"
#include "PathFinding.h"

PathFinding::PathFinding()
{
	printf("pathfinding 생성 \n");
}

PathFinding::~PathFinding()
{
	printf("pathfinding 소멸 \n");
}

void PathFinding::LoadMap(int x, int y, int value)
{
	_map[x][y] = value;
}

Point2D* PathFinding::GetMinFPoint()
{
	// F = (g+h)의 가장 작은 값을 리턴
	int idx = 0, valueF = -9999;

	for (int i = 0; i < _openVec.size(); i++)
	{
		if (_openVec[i]->_f < valueF)
		{
			valueF = _openVec[i]->_f;
			idx = i;
		}
	}

	return _openVec[idx];
}

bool PathFinding::RemoveFromOpenVec(Point2D* point)
{
	for (vector<Point2D*>::iterator it = _openVec.begin(); it != _openVec.end(); ++it)
	{
		if ((*it)->_x == point->_x && (*it)->_y == point->_y)
		{
			_openVec.erase(it);
			return true;
		}
	}
	return false;
}

bool PathFinding::canReach(int x, int y)
{
	return (OPEN == _map[x][y] || PLAYER == _map[x][y]);			// 열려있는지?
}

bool PathFinding::IsAccessiblePoint(Point2D* point, int x, int y, bool isIgnoreCorner)
{
	if (!canReach(x, y) || IsInCloseVec(x, y))
		return false;
	else
	{
		//도달 가능한 지점
		if (abs(x - point->_x) + abs(y - point->_y) == 1)    // 상하 좌우
			return true;
		else
		{
			if (canReach(abs(x - 1), y) && canReach(x, abs(y - 1)))   // 대각선
				return true;
			else
				return isIgnoreCorner;   // 대각선을 무시하는 경우
		}
	}
}

vector<Point2D*> PathFinding::GetAdjacentPoints(Point2D* point, bool isIgnoreCorner)		// 인접점 검사
{
	vector<Point2D*> adjacentPoints;
	for (int x = point->_x - 1; x <= point->_x + 1; ++x)
	{
		for (int y = point->_y - 1; y <= point->_y + 1; ++y)
		{
			if (IsAccessiblePoint(point, x, y, isIgnoreCorner))
			{
				Point2D* tmpPoint = new Point2D(x, y);
				adjacentPoints.push_back(tmpPoint);
			}
		}
	}
	return adjacentPoints;
}

bool PathFinding::IsInOpenVec(int x, int y)
{
	for (vector<Point2D*>::iterator it = _openVec.begin(); it != _openVec.end(); ++it)
	{
		if ((*it)->_x == x && (*it)->_y == y)
			return true;
	}
	return false;
}

bool PathFinding::IsInCloseVec(int x, int y)
{
	for (vector<Point2D*>::iterator it = _closeVec.begin(); it != _closeVec.end(); ++it)
	{
		if ((*it)->_x == x && (*it)->_y == y)
			return true;
	}
	return false;
}

void PathFinding::RefreshPoint(Point2D* tmpStart, Point2D* point)
{
	int valueG = CalcG(tmpStart, point);
	if (valueG < point->_g)
	{
		point->_parentPoint = tmpStart;
		point->_g = valueG;
		point->CalcF();
	}
}

void PathFinding::NotFoundPoint(Point2D* tmpStart, Point2D* end, Point2D* point)
{
	point->_parentPoint = tmpStart;
	point->_g = CalcG(tmpStart, point);
	point->_g = CalcH(end, point);
	point->CalcF();
	_openVec.push_back(point);
}

void PathFinding::ResetVector()
{
	_openVec.clear();
	_closeVec.clear();
}

int PathFinding::CalcG(Point2D* start, Point2D* point)			// 목표에서부터 시작점으로부터의 거리
{
	int G = (abs(point->_x - start->_x) + abs(point->_y - start->_y)) == 2 ? STEP : OBLIQUE;
	int parentG = point->_parentPoint != NULL ? point->_parentPoint->_g : 0;
	return G + parentG;
}

int PathFinding::CalcH(Point2D* end, Point2D* point)			// 현재점부터 타겟까지의 거리
{
	int step = abs(point->_x - end->_x) + abs(point->_y - end->_y);
	return STEP * step;
}

Point2D* PathFinding::FindPath(Point2D* start, Point2D* end, bool isIgnoreCorner)
{
	_openVec.push_back(start);

	while (0 != _openVec.size())
	{
		Point2D* tmpStart = GetMinFPoint();
		RemoveFromOpenVec(tmpStart);
		_closeVec.push_back(tmpStart);

		vector<Point2D*> adjacentPoints = GetAdjacentPoints(tmpStart, isIgnoreCorner);
		for (vector<Point2D*>::iterator it = adjacentPoints.begin(); it != adjacentPoints.end(); ++it)
		{
			Point2D* point = *it;
			if (IsInOpenVec(point->_x, point->_y))   // 오픈리스트에 있는지
				RefreshPoint(tmpStart, point);
//				노드의 g 값을 확인하고 새로 계산된 경로 비용이 g 값보다 낮으면 노드를 다시 엽니다(즉, 다시 OPEN 세트에 넣습니다).				//}
			else
				NotFoundPoint(tmpStart, end, point);
		}
		if (IsInOpenVec(end->_x, end->_y)) // 대상 지점은 이미 열려 있는 목록에 있습니다.
		{
			for (int i = 0; i < _openVec.size(); ++i)
			{
				if (end->_x == _openVec[i]->_x && end->_x == _openVec[i]->_y)
					return _openVec[i];
			}
		}
	}
	return end;
}

vector<Point2D*> PathFinding::GetShortestPath(int startX, int startY, int endX, int endY)
{
	Point2D* s = new Point2D(startX,startY);
	Point2D* e = new Point2D(endX,endY);

	_openVec.clear();
	_closeVec.clear();

	Point2D* point = FindPath(s, e, false);

	vector<Point2D*> temp;

	while (point != NULL)
	{
		temp.push_back(point);
		point = point->_parentPoint;
	}
	return temp;
}
