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
	long double value;
	bool ActivationFunc(long double vaule);
};

