#pragma once

#define STEP			10		// 상하좌우 1
#define OBLIQUE		14		// 대각선		1.414(피타고라스정리)


class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void										LoadMap(int x, int y, int value);

	Point2D*									GetMinFPoint();
	bool										RemoveFromOpenVec(Point2D* point);
	bool										canReach(int x, int y);
	bool										IsAccessiblePoint(Point2D* point, int x, int y, bool isIgnoreCorner);
	vector<Point2D*>						GetAdjacentPoints(Point2D* point, bool isIgnoreCorner);
	bool										IsInOpenVec(int x, int y);
	bool										IsInCloseVec(int x, int y);
	void										RefreshPoint(Point2D* tmpStart, Point2D* point);
	void										NotFoundPoint(Point2D* tmpStrart, Point2D* end, Point2D* point);
	void										ResetVector();

	int											CalcG(Point2D* start, Point2D* point);
	int											CalcH(Point2D* end, Point2D* point);

	Point2D*									FindPath(Point2D* start, Point2D* end, bool isIgnoreCorner);

	vector<Point2D*>						GetShortestPath(int startX, int startY, int endX, int endY);
private:
	int _map[MAP_WIDTH][MAP_HEIGHT];
	vector<Point2D*> _openVec;
	vector<Point2D*> _closeVec;
};
