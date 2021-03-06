#include "pch.h"
#include "Astar.h"

// Astar 내부의 클래스

AStar::Node::Node()
{

}

AStar::Node::Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint)
{
	point.x = _x;
	point.y = _y;
	pParent = _pParent;
	end = _EndPoint;

	if (pParent == NULL) // 부모가 없는 경우
	{
		G = 0;
	}
	else if ( // 십자 방향인 경우
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y) || // 부모가 '좌'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y) || // 부모가 '우'방향에 있거나
		(pParent->point.x == point.x && pParent->point.y == point.y - 1) || // 부모가 '상'방향에 있거나
		(pParent->point.x == point.x && pParent->point.y == point.y + 1)) // 부모가 '하'방향에 있으면		
	{
		G = pParent->G + 10;
	}
	else if ( // 대각선 방향인 경우
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y - 1) || // 부모가 '좌상'방향에 있거나
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y + 1) || // 부모가 '좌상'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y - 1) || // 부모가 '우하'방향에 있거나
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y + 1)) // 부모가 '우상'방향에 있으면
	{
		G = pParent->G + 14;
	}
	else {
		F = -100000;  H = -100000; G = -100000;
	}

	H = (abs(end.x - point.x) + abs(end.y - point.y)) * 10;

	F = G + H;
}

AStar::Node::~Node()
{

}

// Astar 내부의 함수
list<Coordinate*> AStar::FindPath(int Navi[MAP_WIDTH][MAP_HEIGHT], Coordinate StartPoint, Coordinate EndPoint) // Map 은 동적할당했기 때문에 얕은 복사 시 에러
{
	// (상,우,하,좌) 4방향 시계방향 탐색 후 결과에 따라 (우상,우하,좌하,좌상) 탐색.	
	list<Node*> OpenNode; // 열린노드
	list<Node*> CloseNode; // 닫힌노드
	Node* SNode; // 선택된 노드
	
	OpenNode.push_back(new Node(StartPoint.x, StartPoint.y, NULL, EndPoint)); // 시작지점을 열린노드에 추가

	list<Node*>::iterator iter;

	// 열린 노드가 비거나(열린노드의 시작==끝) 목적지에 도착(열린노드에서 값이 발견)한 경우 끝내야함
	// 즉 조건은 반대로 '열린 노드에 내용이 있거나 목적지를 못 찾은 경우' 반복
	while ((OpenNode.end() != OpenNode.begin()) && (OpenNode.end() == FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode)))
	{
		iter = FindNextNode(&OpenNode); // 열린노드 중 F값이 제일 작은 노드의 주소를 찾아서 iter 에 저장
		SNode = *iter; // 열린노드 중 F값이 제일 작은 노드를 SNode에 저장

					   // 선택된 SNode 주변의 8방향 노드 탐색, 값이 수정될 수 있는 것은 열린 노드 뿐이므로 열린 노드는 주소를 전달.
		ExploreNode(Navi, SNode, &OpenNode, &CloseNode, EndPoint);

		CloseNode.push_back(SNode); // 현재 탐색한 노드를 닫힌 노드에 추가
		OpenNode.erase(iter); // 닫힌 노드에 추가한 노드를 열린 노드에서 제거
	}

	if ((OpenNode.end() != OpenNode.begin())) // 길을 찾은 경우
	{
		iter = FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode); // 목적지의 노드를 찾아서 iter에 저장
		for (SNode = *iter; SNode->pParent != NULL; SNode = SNode->pParent)  // 부모가 NULL일 때까지 path에 경로 저장
		{
			_path.push_back(new Coordinate(SNode->point.x, SNode->point.y));
		}	
		_path.push_back(new Coordinate(SNode->point.x, SNode->point.y)); // 부모가 NULL인 경우의 path까지 저장(출발 지점)

		_path.reverse(); // 목적지점으부터 역순으로 입력했으므로 다시 역순으로 뒤집어 출발지점이 첫 번째가 되도록 함.

		// 길을 찾은 경우 동적할당 해제
		iter = OpenNode.begin();
		for (; iter != OpenNode.end(); iter++)
		{
			delete* iter; // 열린 노드 동적할당 해제
		}
		iter = CloseNode.begin();
		for (; iter != CloseNode.end(); iter++)
		{
			delete* iter; // 닫힌 노드 동적할당 해제
		}

		return _path; // 길을 찾은 경우 리턴
	}

	// 길을 찾지 못한 경우 동적할당 해제
	iter = CloseNode.begin();
	for (; iter != CloseNode.end(); iter++)
	{
		delete* iter; // 닫힌 노드 동적할당 해제
	}
	return _path; // 길을 찾지 못한 경우 리턴

}

void AStar::ExploreNode(int map[MAP_WIDTH][MAP_HEIGHT], Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint)
{
	bool left = true, down = true, right = true, up = true; // 이 결과에 따라 대각선 방향 탐색 여부를 결정. true == 장애물 있음, false == 없음
	list<Node*>::iterator iter;
	POINT point;

	// '좌' 방향 탐색
	point.x = SNode->point.x - 1;	point.y = SNode->point.y;
	if (SNode->point.x > 0 && map[point.x][point.y] != CLOSE) // '좌' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		left = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 좌방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 좌방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// 하나만 보면 될듯 위에꺼 상하좌우, 대각선 모두 유사함.
#pragma region repeat
	// '하' 방향 탐색
	point.x = SNode->point.x;	point.y = SNode->point.y + 1;
	if (SNode->point.y < (MAP_HEIGHT - 1) && map[point.x][point.y] != CLOSE) // '하' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		down = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 하방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 하방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '우' 방향 탐색
	point.x = SNode->point.x + 1;	point.y = SNode->point.y;
	if (SNode->point.x < (MAP_WIDTH - 1) && map[point.x][point.y] != CLOSE) // '우' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		right = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 우방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 우방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '상' 방향 탐색
	point.x = SNode->point.x;	point.y = SNode->point.y - 1;
	if (SNode->point.y > 0 && map[point.x][point.y] != CLOSE) // '상' 방향에 맵이 존재하고 장애물이 없을 경우
	{
		// 장애물이 없는 경우에 해당하므로 장애물 false 세팅
		up = false;

		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}

	// '좌하' 방향 탐색
	point.x = SNode->point.x - 1;	point.y = SNode->point.y + 1;
	if (SNode->point.x > 0 && SNode->point.y < (MAP_HEIGHT - 1) && map[point.x][point.y] != CLOSE &&
		left == false && down == false) // '좌하' 방향에 맵이 존재하고 장애물이 없으며, 우방향과 상방향에도 장애물이 없을 경우
	{
		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '우하' 방향 탐색
	point.x = SNode->point.x + 1;	point.y = SNode->point.y + 1;
	if (SNode->point.x < (MAP_WIDTH - 1) && SNode->point.y < (MAP_HEIGHT - 1) &&
		map[point.x][point.y] != CLOSE && down == false && right == false)
		// '우하' 방향에 맵이 존재하고 장애물이 없으며, 우방향과 하방향에도 장애물이 없을 경우
	{
		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 우하방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 우하방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '우상' 방향 탐색
	point.x = SNode->point.x + 1;	point.y = SNode->point.y - 1;
	if (SNode->point.x < (MAP_WIDTH - 1) && SNode->point.y > 0 && map[point.x][point.y] != CLOSE &&
		up == false && right == false) // '우상' 방향에 맵이 존재하고 장애물이 없으며, 좌방향과 하방향에도 장애물이 없을 경우
	{
		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 우상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 우상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '좌상' 방향 탐색
	point.x = SNode->point.x - 1;	point.y = SNode->point.y - 1;
	if (SNode->point.x > 0 && SNode->point.y > 0 && map[point.x][point.y] != CLOSE &&
		up == false && left == false) // '좌상' 방향에 맵이 존재하고 장애물이 없으며, 좌방향과 상방향에도 장애물이 없을 경우
	{
		// 이미 열린 노드에 있는 경우
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // 원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 비용이 더 낮아질 경우 
			{
				(*iter)->pParent = SNode; // 현재 노드를 부모로 바꿈
			}
		}

		// 닫힌 노드에 있는 경우
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// 좌상방향에 장애물이 없고 열린 노드 및 닫힌 노드에 추가되어있지 않은 경우
		// 좌상방향 노드를 열린 노드에 추가, 부모는 현재 탐색 노드로 지정.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
#pragma endregion
}

list<AStar::Node*>::iterator AStar::FindNextNode(list<AStar::Node*>* pOpenNode) // 오픈노드 중 F값이 제일 작은 노드 찾아서 반환
{
	list<Node*>::iterator iter = (*pOpenNode).begin();

	int minValue = 2000000000; // 현재 제일 작은 값을 저장
	int order = 0; // 제일 작은 값이 몇 번째인지

	for (int i = 1; iter != (*pOpenNode).end(); i++, iter++)
	{
		if ((*iter)->F <= minValue) // F값이 작거나 같은 경우를 발견하면(이렇게 구현 시 F값이 같은 경우 최근에 추가된 것이 우선)
		{
			minValue = (*iter)->F;
			order = i;
		}
	}

	iter = (*pOpenNode).begin();
	for (int i = 1; i < order; i++)
	{
		iter++;
	}

	return iter;
}

list<AStar::Node*>::iterator AStar::FindCoordNode(int _x, int _y, list<AStar::Node*>* NodeList) // 노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환. 없으면 end()반환.
{
	list<AStar::Node*>::iterator iter = NodeList->begin();

	for (int i = 1; iter != NodeList->end(); i++, iter++)
	{
		if ((*iter)->point.x == _x && (*iter)->point.y == _y)
		{
			return iter;
		}
	}

	return NodeList->end();
}

list<Coordinate*> AStar::ReturnPath(int map[MAP_WIDTH][MAP_HEIGHT], int startX, int startY, int endX, int endY)
{
	Coordinate start(startX, startY);
	Coordinate end(endX, endY);
	
	iter = _path.begin();
	for (; iter != _path.end(); iter++)
	{
		delete* iter;
	}
	_path.clear();

	return FindPath(map, start, end);
}
