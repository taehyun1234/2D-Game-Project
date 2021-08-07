#pragma once

//https://blog.naver.com/baek2sm/221141838239 참고

class Astar
{
public: // 내부 클래스
	class Coordinate // x, y 좌표 클래스
	{
	public:
		int x;
		int y;
	public:
		void Set(int _x=0, int _y=0)
		{
			x = _x; y = _y;
		}
	public:
		Coordinate() {}
		Coordinate(int _x, int _y) : x(_x), y(_y) {}
	};

	class Node // 노드 클래스
	{
	public:
		Coordinate point;
		int F, G, H; // F = 비용, G = 지난 거리, H = 남은 거리

		Coordinate end;
		Node* pParent;

	public:
		Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint);
		Node();
		~Node();
	};
	   	 
private: // 내부 함수
	list<Coordinate*> FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint);
	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); // 오픈노드 중 F값이 제일 작은 노드 찾아서 반환
	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); // 노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환. 없으면 end()반환.
	void ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint); // 8방향 노드를 탐색하고 열린 노드에 추가 및 부모 변경을 실행함
	
public:
	void FindPath();
	Coordinate GetPos(int order); // order번째 경로의 좌표를 받아옴
	list<Coordinate*> GetPath() { return path; } // 경로를 Coordinate* 리스트로 통째로 받아옴
	void SetFree(int _x, int _y); // 해당 좌표의 장애물을 없앰
	void SetObstacle(int _x, int _y); // 해당 좌표에 장애물을 설치
	void PrintPath();
	void PrintMap();
	void PrintNavi();

private:
	Coordinate StartPoint; // 출발지점
	Coordinate EndPoint; // 목표지점
	list<Coordinate*> path; // 경로
	list<Coordinate*>::iterator iter; // 경로 iterator

public:
	Astar(Coordinate _StartPoint, Coordinate _EndPoint) 
	{
		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
		FindPath();
	}
	~Astar() 
	{ // path 동적할당 해제
		iter = path.begin(); 
		for (; iter != path.end(); iter++)
		{
			delete *iter;
		}
	}
};

