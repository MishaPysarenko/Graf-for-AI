#pragma once
#include "Edges.h"
#include "Vertex.h"

//#include <list>//���� ��� ���������� �������� ����� 
#include <unordered_map>//���-������� ��� ���������� �������� �����
#include <algorithm>//�������� ������
#include <string>//��� ���������� �����. ������� ����� ����������� ��� - "1.���������� �����". �������� ��� - "-1.���������� �����". ������������� ��� - "0.���������� �����"
				 //��� ���������� �����. ����� ����������� ��� - "������ ���� � �������� ���� - ������ ���� � ������� ����"
#include <fstream>//��� ���������� � ������ � ����� ������ � ����� ��� ����������� ������� ������� ������

#include <cstdlib>//��� ��������� ��������� �����
#include <ctime>

#include <iostream>//������� ����� �������

class Graf
{
private:
	Vertex *vertex;
	Edges *edges;
	unsigned long long int amountVertex = 0;//���������� �����, ��� ����������
	unsigned long long int amountOutVertex = 0;

	unsigned long long int amountEdges = 0;//���������� �����, ��� ����������
	std::unordered_map<std::string, Vertex*> heshMapVertex;//���-������� ��� ���������� ���� ��������
	std::unordered_map<std::string, Vertex*> heshMapInVertex;//���-������� ��� ���������� ������� ��������
	std::unordered_map<std::string, Vertex*> heshMapOutVertex;//���-������ ��� ���������� �������� ��������
	std::unordered_map<std::string, Edges*> heshMapEdges;//���-������� ��� ���������� �����
	std::unordered_map<std::string, long double> valueListEdges;//���-������� �������� ���������� ����� ��� ������� �������
	//------------------------------------------------------------
	//��� ��� �������� � �������
	//------------------------------------------------------------
	void DeleteEdges(std::string nameVertex, std::string nameEdges);//�������� �����
	void AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges);//���������� �����
	void EditWeightEdges(std::string nameEdges, long double weightEdges);//��������� ���� ����� � ���� ��������
	//------------------------------------------------------------
	//��� ��� �������� � ���������/������
	//------------------------------------------------------------
	void AddInVertex();//���������� ���� ��� �����, ��� �������� �������
	void AddOutVertex();//���������� ���� ��� ��������� �������
	void AddVertex();//���������� ���� ��� �������������� �������
	void DeleteVertex(std::string nameVertex);//�������� ������� �� �����
public:
	~Graf();
	Graf();
	//------------------------------------------------------------
	//��� ��� �������� � ����������� � ��������� 
	//------------------------------------------------------------
	void CreateNetwork(unsigned long long int amountInVertex, unsigned long long int amountOutVertex);
	void Training();
	void Computation();
};

