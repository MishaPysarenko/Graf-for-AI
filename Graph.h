#include <list>//���� ��� ���������� �������� ����� 
#include <vector>//����� ��� ���������� �������� �����
#include <algorithm>//�������� ������
#include <string>//��� ���������� ����� (������� � ��� ����� �������� ��� �������� ���� � ���������� ����� � ����� ����� ��������� �� ���� ��
				 //� ����� �� �����, �������� ��� ��������� ���� �������� ��������������� ������ "56,1,25" � ���� 2 ������ ������ 54� ������ 
				 //�� ������� 1� � ����� �� ���� ��� ���� 25�)
#include <fstream>//��� ���������� � ������ � ����� ������ � ����� ��� ����������� ������� ������� ������

#include <iostream>//������� ����� �������

class Graph
{
	class Vertex//����/�������
	{
	private:
		//------------------------------------
		class Edges//�����
		{
		public:
			Vertex* nextVertex;
			std::string indexEdges;//��� ���������� �����
			int weightEdges;//��� ����� 
		};
		//------------------------------------
		Edges* edgesPoint;
		std::list<Edges*> ListVertex;//���� ��� ���������� �������� ����� 
	public:
		unsigned int getAmountEdges();
		void addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges = 0);//���������� �����
		void deleteEdges(Edges* deletedEdges);//�������� �����
		std::string nameVertex;//��� ���������� ����
		unsigned int precipitationAmount;//���������� ���������, ��� ����� 
	};
	
	std::vector<Vertex*> vectorVertex;
	Vertex* vertex;//������ ����� ������ ����
	unsigned int iAmountVertex = 0;//���������� �����
	void deleteVertex(Vertex* deletedVertex);//�������� ������� �� ��������
public:
	Graph();//����������� ����������� ����� 
	~Graph();//����������� �������� �����
	void addVertex();//���������� ������� ��� �����
	void vertexBinding(std::string nameVertex);//���������� ������� � ������������ 
	void deleteVertex(std::string nameVertex);//�������� ������� �� �����
	void connectNodes(std::string nodeConnected, std::string nodeAttached, unsigned int weightEdges = 0);//���������� ���� ����� �����
	unsigned int amountVertex();//����������� ������� ����� � �����
	void takeTheEasiestPath();//���� �� ������ ������� ����
	void takeTheHardPath();//���� �� ������ �������� ����
	Vertex* getVertex(std::string nameVertex);//����� ��� ���������� ��������� �� ���� � ����� 

	void showAllVertex();//������� ����� �������
};