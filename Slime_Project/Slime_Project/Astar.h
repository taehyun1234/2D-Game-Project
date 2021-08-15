/* Astar Class Infor

// Ŭ������ ����.
Astar::Coordinate SP(0,0);
Astar::Coordinate DP(0,4);
Astar astar(SP, DP); // �ؽ�Ʈ ���� �ҷ��� �ʱ�ȭ, ������� ������ ���� �� �� ã�� �Լ����� ����.

// ���
astar.PrintPath(); // ����� ��ǥ�� ���������� ���. ex) 00 01 02 12 ...
astar.PrintMap(); // astar�� ����Ǿ� �ִ� ���� ���
astar.PrintNavi(); // ���� ����ϵ� astar ��θ� ���� 7�� ǥ��

// ��θ� ��������
/ ��ǥ ��������(GetPos(����))
astar.GetPos(1); // 1��° ����� ��ǥ�� ������
ex) cout << astar.GetPos(1).x << astar.GetPos(1).y << endl;
/ ��� ��ü�� ����Ʈ�� ��������(GetPath())
list<Astar::Coordinate*> path = astar.GetPath();
list<Astar::Coordinate*>::iterator iter = path.begin();

// �� ã��
astar.FindPath(); // �� ã�⸦ �ٽ� ����(���� �����Ǿ��� ��� �����ؾ� ��)

// ���� ����
astar.SetFree(0, 3); // �ش� ��ǥ�� ��ֹ��� ����
astar.SetObstacle(0, 3); // �ش� ��ǥ�� ��ֹ��� ��ġ

*/


class AStar
{
public: // ���� Ŭ����
	class Node // ��� Ŭ����
	{
	public:
		Coordinate point;
		int F, G, H; // F = ���, G = ���� �Ÿ�, H = ���� �Ÿ�

		Coordinate end;
		Node* pParent;

	public:
		Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint);
		Node();
		~Node();
	};
	   
private: // ���� �Լ�
	list<Coordinate*> FindPath(int map[MAP_WIDTH][MAP_HEIGHT], Coordinate StartPoint, Coordinate EndPoint);
	// ������ ��ã��
	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); 
	// ���³�� �� F���� ���� ���� ��� ã�Ƽ� ��ȯ
	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); 
	// ��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ. ������ end()��ȯ.
	void ExploreNode(int map[MAP_WIDTH][MAP_HEIGHT], Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint);
	// 8���� ��带 Ž���ϰ� ���� ��忡 �߰� �� �θ� ������ ������

public:
	list<Coordinate*> ReturnPath(int map[MAP_WIDTH][MAP_HEIGHT], int startX, int startY, int endX,int endY);
		
private:
	Coordinate StartPoint; // �������
	Coordinate EndPoint; // ��ǥ����
	list<Coordinate*> _path; // ���
	list<Coordinate*>::iterator iter; // ��� iterator

public:
	AStar(Coordinate _StartPoint, Coordinate _EndPoint)
	{
		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
	}

	AStar(){}
	~AStar()
	{ // path �����Ҵ� ����
		iter = _path.begin();
		for (; iter != _path.end(); iter++)
		{
			delete* iter;
		}
	}
};

