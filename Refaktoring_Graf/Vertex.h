#pragma once
#include "Edges.h"
#include <string>
#include <list>//���� ��� ���������� �������� ����� 

class Edges;

class Vertex
{
public:
	std::string indexVertex;//��� ���������� ��������
	std::list<Edges*> listEdges;//���� ��� ���������� �������� ����� 
	bool value;
	bool ActivationFunc(long double vaule);
};

