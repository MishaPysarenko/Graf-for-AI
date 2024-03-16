#pragma once
#include "Edges.h"

#include <string>
#include <list>//���� ��� ���������� �������� ����� 
#include <memory>//����� ���������

namespace ai
{
	struct Edges;

	class Vertex
	{
		bool (*activationFunc)(long double);
	public:
		Vertex(bool (*activationFuncPtr)(long double) = nullptr);
		//������ ������� ��� ���
		std::string indexVertex;
		//���� ��� ���������� �������� ����� 
		std::shared_ptr<std::list<std::shared_ptr<Edges>>> listEdges;
		bool ActivationFunc(long double value, bool(*activationFunc)(long double) = nullptr);
		//
		unsigned long long int counterPrt;

		bool value;
	};
}