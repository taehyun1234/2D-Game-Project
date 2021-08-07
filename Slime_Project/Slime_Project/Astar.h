#pragma once

//https://blog.naver.com/baek2sm/221141838239 ����

class Astar
{
public: // ���� Ŭ����
	class Coordinate // x, y ��ǥ Ŭ����
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
	list<Coordinate*> FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint);
	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); // ���³�� �� F���� ���� ���� ��� ã�Ƽ� ��ȯ
	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); // ��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ. ������ end()��ȯ.
	void ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint); // 8���� ��带 Ž���ϰ� ���� ��忡 �߰� �� �θ� ������ ������
	
public:
	void FindPath();
	Coordinate GetPos(int order); // order��° ����� ��ǥ�� �޾ƿ�
	list<Coordinate*> GetPath() { return path; } // ��θ� Coordinate* ����Ʈ�� ��°�� �޾ƿ�
	void SetFree(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ����
	void SetObstacle(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ��ġ
	void PrintPath();
	void PrintMap();
	void PrintNavi();

private:
	Coordinate StartPoint; // �������
	Coordinate EndPoint; // ��ǥ����
	list<Coordinate*> path; // ���
	list<Coordinate*>::iterator iter; // ��� iterator

public:
	Astar(Coordinate _StartPoint, Coordinate _EndPoint) 
	{
		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
		FindPath();
	}
	~Astar() 
	{ // path �����Ҵ� ����
		iter = path.begin(); 
		for (; iter != path.end(); iter++)
		{
			delete *iter;
		}
	}
};

