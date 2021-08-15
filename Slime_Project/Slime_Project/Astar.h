/* Astar Class Infor

// 클래스의 생성.
Astar::Coordinate SP(0,0);
Astar::Coordinate DP(0,4);
Astar astar(SP, DP); // 텍스트 맵을 불러와 초기화, 출발지와 목적지 설정 및 길 찾기 함수까지 실행.

// 출력
astar.PrintPath(); // 경로의 좌표를 순차적으로 출력. ex) 00 01 02 12 ...
astar.PrintMap(); // astar에 저장되어 있는 맵을 출력
astar.PrintNavi(); // 맵을 출력하되 astar 경로를 숫자 7로 표시

// 경로를 가져오기
/ 좌표 가져오기(GetPos(순서))
astar.GetPos(1); // 1번째 경로의 좌표를 가져옴
ex) cout << astar.GetPos(1).x << astar.GetPos(1).y << endl;
/ 경로 전체를 리스트로 가져오기(GetPath())
list<Astar::Coordinate*> path = astar.GetPath();
list<Astar::Coordinate*>::iterator iter = path.begin();

// 길 찾기
astar.FindPath(); // 길 찾기를 다시 실행(맵이 수정되었을 경우 실행해야 함)

// 맵의 수정
astar.SetFree(0, 3); // 해당 좌표의 장애물을 제거
astar.SetObstacle(0, 3); // 해당 좌표에 장애물을 설치

*/


class AStar
{
public: // 내부 클래스
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
	list<Coordinate*> FindPath(int map[MAP_WIDTH][MAP_HEIGHT], Coordinate StartPoint, Coordinate EndPoint);
	// 실질적 길찾기
	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); 
	// 오픈노드 중 F값이 제일 작은 노드 찾아서 반환
	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); 
	// 노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환. 없으면 end()반환.
	void ExploreNode(int map[MAP_WIDTH][MAP_HEIGHT], Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint);
	// 8방향 노드를 탐색하고 열린 노드에 추가 및 부모 변경을 실행함

public:
	list<Coordinate*> ReturnPath(int map[MAP_WIDTH][MAP_HEIGHT], int startX, int startY, int endX,int endY);
		
private:
	Coordinate StartPoint; // 출발지점
	Coordinate EndPoint; // 목표지점
	list<Coordinate*> _path; // 경로
	list<Coordinate*>::iterator iter; // 경로 iterator

public:
	AStar(Coordinate _StartPoint, Coordinate _EndPoint)
	{
		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
	}

	AStar(){}
	~AStar()
	{ // path 동적할당 해제
		iter = _path.begin();
		for (; iter != _path.end(); iter++)
		{
			delete* iter;
		}
	}
};

