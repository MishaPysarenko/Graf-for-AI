#pragma once
#include "Vertex.h"

#include <string>
#include <memory>//����� ���������
namespace ai
{
	class Vertex;

	struct Edges
	{
		std::shared_ptr<Vertex> nextVertex;
		//������ ����� ��� ���
		std::string indexEdges;
		//��� �����, ���������
		long double weightEdges;
	};
}