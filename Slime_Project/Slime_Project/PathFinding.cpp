#include "pch.h"
#include "PathFinding.h"

PathFinding::PathFinding()
{
	printf("pathfinding ���� \n");
}

PathFinding::~PathFinding()
{
	printf("pathfinding �Ҹ� \n");
}

void PathFinding::LoadMap(int x, int y, int value)
{
	_map[x][y] = value;
}

Point2D* PathFinding::GetMinFPoint()
{
	// F = (g+h)�� ���� ���� ���� ����
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
	return (OPEN == _map[x][y] || PLAYER == _map[x][y]);			// �����ִ���?
}

bool PathFinding::IsAccessiblePoint(Point2D* point, int x, int y, bool isIgnoreCorner)
{
	if (!canReach(x, y) || IsInCloseVec(x, y))
		return false;
	else
	{
		//���� ������ ����
		if (abs(x - point->_x) + abs(y - point->_y) == 1)    // ���� �¿�
			return true;
		else
		{
			if (canReach(abs(x - 1), y) && canReach(x, abs(y - 1)))   // �밢��
				return true;
			else
				return isIgnoreCorner;   // �밢���� �����ϴ� ���
		}
	}
}

vector<Point2D*> PathFinding::GetAdjacentPoints(Point2D* point, bool isIgnoreCorner)		// ������ �˻�
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

int PathFinding::CalcG(Point2D* start, Point2D* point)			// ��ǥ�������� ���������κ����� �Ÿ�
{
	int G = (abs(point->_x - start->_x) + abs(point->_y - start->_y)) == 2 ? STEP : OBLIQUE;
	int parentG = point->_parentPoint != NULL ? point->_parentPoint->_g : 0;
	return G + parentG;
}

int PathFinding::CalcH(Point2D* end, Point2D* point)			// ���������� Ÿ�ٱ����� �Ÿ�
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
			if (IsInOpenVec(point->_x, point->_y))   // ���¸���Ʈ�� �ִ���
				RefreshPoint(tmpStart, point);
//				����� g ���� Ȯ���ϰ� ���� ���� ��� ����� g ������ ������ ��带 �ٽ� ���ϴ�(��, �ٽ� OPEN ��Ʈ�� �ֽ��ϴ�).				//}
			else
				NotFoundPoint(tmpStart, end, point);
		}
		if (IsInOpenVec(end->_x, end->_y)) // ��� ������ �̹� ���� �ִ� ��Ͽ� �ֽ��ϴ�.
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
