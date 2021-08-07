#include "pch.h"
#include "Astar.h"
// Astar ������ Ŭ����

Astar::Node::Node()
{

}

Astar::Node::Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint)
{
	point.x = _x;
	point.y = _y;
	pParent = _pParent;
	end = _EndPoint;

	if (pParent == NULL) // �θ� ���� ���
	{
		G = 0;
	}
	else if ( // ���� ������ ���
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y) || // �θ� '��'���⿡ �ְų�
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y) || // �θ� '��'���⿡ �ְų�
		(pParent->point.x == point.x && pParent->point.y == point.y - 1) || // �θ� '��'���⿡ �ְų�
		(pParent->point.x == point.x && pParent->point.y == point.y + 1)) // �θ� '��'���⿡ ������		
	{
		G = pParent->G + 10;
	}
	else if ( // �밢�� ������ ���
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y - 1) || // �θ� '�»�'���⿡ �ְų�
		(pParent->point.x == point.x - 1 && pParent->point.y == point.y + 1) || // �θ� '���'���⿡ �ְų�
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y - 1) || // �θ� '����'���⿡ �ְų�
		(pParent->point.x == point.x + 1 && pParent->point.y == point.y + 1)) // �θ� '����'���⿡ ������
	{
		G = pParent->G + 14;
	}
	else {
		F = -100000;  H = -100000; G = -100000;
	}

	H = (abs(end.x - point.x) + abs(end.y - point.y)) * 10;

	F = G + H;
}

Astar::Node::~Node()
{

}

// Astar ������ �Լ�
list<Astar::Coordinate*> Astar::FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint) // Map �� �����Ҵ��߱� ������ ���� ���� �� ����
{
	// (��,��,��,��) 4���� �ð���� Ž�� �� ����� ���� (���,����,����,�»�) Ž��.	
	list<Node*> OpenNode; // �������
	list<Node*> CloseNode; // �������
	Node* SNode; // ���õ� ���
	list<Coordinate*> path;

	OpenNode.push_back(new Node(StartPoint.x, StartPoint.y, NULL, EndPoint)); // ���������� ������忡 �߰�

	list<Node*>::iterator iter;

	// ���� ��尡 ��ų�(��������� ����==��) �������� ����(������忡�� ���� �߰�)�� ��� ��������
	// �� ������ �ݴ�� '���� ��忡 ������ �ְų� �������� �� ã�� ���' �ݺ�
	while ((OpenNode.end() != OpenNode.begin()) && (OpenNode.end() == FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode)))
	{
		iter = FindNextNode(&OpenNode); // ������� �� F���� ���� ���� ����� �ּҸ� ã�Ƽ� iter �� ����
		SNode = *iter; // ������� �� F���� ���� ���� ��带 SNode�� ����

					   // ���õ� SNode �ֺ��� 8���� ��� Ž��, ���� ������ �� �ִ� ���� ���� ��� ���̹Ƿ� ���� ���� �ּҸ� ����.
		ExploreNode(Navi, SNode, &OpenNode, &CloseNode, EndPoint);

		CloseNode.push_back(SNode); // ���� Ž���� ��带 ���� ��忡 �߰�
		OpenNode.erase(iter); // ���� ��忡 �߰��� ��带 ���� ��忡�� ����
	}

	if ((OpenNode.end() != OpenNode.begin())) // ���� ã�� ���
	{
		iter = FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode); // �������� ��带 ã�Ƽ� iter�� ����
		for (SNode = *iter; SNode->pParent != NULL; SNode = SNode->pParent)  // �θ� NULL�� ������ path�� ��� ����
		{
			path.push_back(new Coordinate(SNode->point.x, SNode->point.y));
		}	path.push_back(new Coordinate(SNode->point.x, SNode->point.y)); // �θ� NULL�� ����� path���� ����(��� ����)

		path.reverse(); // �������������� �������� �Է������Ƿ� �ٽ� �������� ������ ��������� ù ��°�� �ǵ��� ��.

		// ���� ã�� ��� �����Ҵ� ����
		iter = OpenNode.begin();
		for (; iter != OpenNode.end(); iter++)
		{
			delete* iter; // ���� ��� �����Ҵ� ����
		}
		iter = CloseNode.begin();
		for (; iter != CloseNode.end(); iter++)
		{
			delete* iter; // ���� ��� �����Ҵ� ����
		}

		return path; // ���� ã�� ��� ����
	}

	// ���� ã�� ���� ��� �����Ҵ� ����
	iter = CloseNode.begin();
	for (; iter != CloseNode.end(); iter++)
	{
		delete* iter; // ���� ��� �����Ҵ� ����
	}
	return path; // ���� ã�� ���� ��� ����

}

void Astar::ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint)
{
	bool up = true, right = true, down = true, left = true; // �� ����� ���� �밢�� ���� Ž�� ���θ� ����. true == ��ֹ� ����, false == ����
	list<Node*>::iterator iter;
	POINT point;

	// '��' ���� Ž��
	point.x = SNode->point.x - 1;	point.y = SNode->point.y;
	if (SNode->point.x > 0 && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		up = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point.x = SNode->point.x;	point.y = SNode->point.y + 1;
	if (SNode->point.y < (Navi->sizeY - 1) && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		right = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point.x = SNode->point.x + 1;	point.y = SNode->point.y;
	if (SNode->point.x < (Navi->sizeX - 1) && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		down = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point.x = SNode->point.x;	point.y = SNode->point.y - 1;
	if (SNode->point.y > 0 && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		left = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}

	// '���' ���� Ž��
	point.x = SNode->point.x - 1;	point.y = SNode->point.y + 1;
	if (SNode->point.x > 0 && SNode->point.y < (Navi->sizeY - 1) && Navi->map[point.x][point.y] == 0 &&
		up == false && right == false) // '���' ���⿡ ���� �����ϰ� ��ֹ��� ������, ������ ����⿡�� ��ֹ��� ���� ���
	{
		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '����' ���� Ž��
	point.x = SNode->point.x + 1;	point.y = SNode->point.y + 1;
	if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y < (Navi->sizeY - 1) &&
		Navi->map[point.x][point.y] == 0 && right == false && down == false)
		// '����' ���⿡ ���� �����ϰ� ��ֹ��� ������, ������ �Ϲ��⿡�� ��ֹ��� ���� ���
	{
		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '����' ���� Ž��
	point.x = SNode->point.x + 1;	point.y = SNode->point.y - 1;
	if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y > 0 && Navi->map[point.x][point.y] == 0 &&
		left == false && down == false) // '����' ���⿡ ���� �����ϰ� ��ֹ��� ������, �¹���� �Ϲ��⿡�� ��ֹ��� ���� ���
	{
		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
	// '�»�' ���� Ž��
	point.x = SNode->point.x - 1;	point.y = SNode->point.y - 1;
	if (SNode->point.x > 0 && SNode->point.y > 0 && Navi->map[point.x][point.y] == 0 &&
		left == false && up == false) // '�»�' ���⿡ ���� �����ϰ� ��ֹ��� ������, �¹���� ����⿡�� ��ֹ��� ���� ���
	{
		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new Node(point.x, point.y, SNode, EndPoint));
		}
	}
}

list<Astar::Node*>::iterator Astar::FindNextNode(list<Astar::Node*>* pOpenNode) // ���³�� �� F���� ���� ���� ��� ã�Ƽ� ��ȯ
{
	list<Node*>::iterator iter = (*pOpenNode).begin();

	int minValue = 2000000000; // ���� ���� ���� ���� ����
	int order = 0; // ���� ���� ���� �� ��°����

	for (int i = 1; iter != (*pOpenNode).end(); i++, iter++)
	{
		if ((*iter)->F <= minValue) // F���� �۰ų� ���� ��츦 �߰��ϸ�(�̷��� ���� �� F���� ���� ��� �ֱٿ� �߰��� ���� �켱)
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

list<Astar::Node*>::iterator Astar::FindCoordNode(int _x, int _y, list<Astar::Node*>* NodeList) // ��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ. ������ end()��ȯ.
{
	list<Astar::Node*>::iterator iter = NodeList->begin();

	for (int i = 1; iter != NodeList->end(); i++, iter++)
	{
		if ((*iter)->point.x == _x && (*iter)->point.y == _y)
		{
			return iter;
		}
	}

	return NodeList->end();
}

void Astar::FindPath()
{
	path = FindPath(&Navi, StartPoint, EndPoint);
	iter = path.begin(); // iter �� ������� �����ֱ�
}

Astar::Coordinate Astar::GetPos(int order)
{
	Coordinate pos;
	for (int i = 1; i < order; i++)
	{
		iter++;
	}
	pos.x = (*iter)->x;
	pos.y = (*iter)->y;
	iter = path.begin();
	return pos;
}

void Astar::SetFree(int _x, int _y)
{
	Navi.map[_x][_y] = 0;
}

void Astar::SetObstacle(int _x, int _y)
{
	Navi.map[_x][_y] = 1;
}

void Astar::PrintPath()
{
	for (int i = 0; iter != path.end(); iter++)
	{
	//	cout << (*iter)->x << (*iter)->y << endl;
	}
	iter = path.begin(); // iter �� ������� �����ֱ�
}

void Astar::PrintMap()
{
	Navi.PrintMap();
}

void Astar::PrintNavi()
{
	printNavi.Copy(&Navi);

	for (int i = 0; iter != path.end(); iter++) // �ʿ��� ��ο� �ش��ϴ� ���� 7�� ǥ��
	{
		printNavi.map[(*iter)->x][(*iter)->y] = 7;
	}
	iter = path.begin(); // iter �� ������� �����ֱ�

	printNavi.PrintMap();
}