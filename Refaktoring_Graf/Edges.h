#pragma once
#include <string>
#include "Vertex.h"

class Vertex;

class Edges 
{
public:
	Vertex* nextVertex;
	std::string indexEdges;//��� ���������� �����
	long double weightEdges;//��� �����, ���������
	long double tempValue;//��������� �������� ��� ���������� ��� ��������� �������, �� � ������� ������
};

