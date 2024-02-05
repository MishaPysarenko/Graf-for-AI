#pragma once
#include "Edges.h"
#include "Vertex.h"

//#include <list>//���� ��� ���������� �������� ����� 
#include <unordered_map>//���-������� ��� ���������� �������� �����
#include <algorithm>//�������� ������
#include <vector>
#include <string>//��� ���������� �����. ������� ����� ����������� ��� - "1.���������� �����". �������� ��� - "-1.���������� �����". ������������� ��� - "0.���������� �����"
				 //��� ���������� �����. ����� ����������� ��� - "������ ���� � �������� ���� - ������ ���� � ������� ����"
#include <fstream>//��� ���������� � ������ � ����� ������ � ����� ��� ����������� ������� ������� ������

#include <cstdlib>//��� ��������� ��������� �����
#include <ctime>

#include <iostream>//������� ����� �������

struct StorageCell
{
	long double weight;
	unsigned int amoutnTry;
};

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

	std::unordered_map<std::string, long double> valueListEdges;//���-������� �������� ���������� ����� ��� ������� �������
	//------------------------------------------------------------
	//��� ��� �������� � �������
	//------------------------------------------------------------
	std::unordered_map<std::string, Edges*> heshMapEdges;//���-������� ��� ���������� �����

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
	//------------------------------------------------------------
	//��� ��� �������� � ����������� � ��������� 
	//------------------------------------------------------------
	
	//���-������� ��� ���������� ����� ������� ���� ������ �������� � ���������� �������� ��� �� �������������
	std::unordered_map<std::string, std::list<StorageCell*>*> heshMapTrainingEdges;

	std::list<StorageCell*> *listStorageCell;
	Edges *beforeEdges;
	std::string nameEdges;
	StorageCell *cell;

	unsigned long long int amountTraing = 0;
	unsigned int amountGoodTry = 0;

	
public:
	~Graf();
	Graf();
	void CreateNetwork(unsigned long long int amountInVertex, unsigned long long int amountOutVertex);
	void Training1();
	void Training2(bool result);
	void Training3(bool result);
	bool Computation(std::list<bool> vaules);
};

