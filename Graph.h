#include <list>//���� ��� ���������� �������� ����� 
#include <unordered_map>//����� ��� ���������� �������� �����
#include <algorithm>//�������� ������
#include <string>//��� ���������� ����� (������� � ��� ����� �������� ��� �������� ���� � ���������� ����� � ����� ����� ��������� �� ���� ��
				 //� ����� �� �����, �������� ��� ��������� ���� �������� ��������������� ������ "56,1,25" � ���� 2 ������ ������ 54� ������ 
				 //�� ������� 1� � ����� �� ���� ��� ���� 25�)
#include <fstream>//��� ���������� � ������ � ����� ������ � ����� ��� ����������� ������� ������� ������

#include <iostream>//������� ����� �������

class Graph
{
public:
	//--------------------
	// 
	// 
	//----------------------------------------
private:
	class Vertex//����/�������
	{
	public:
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
		unsigned int getAmountEdges();
		//void addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges = 0);//���������� �����
		Graph::Vertex::Edges* addEdges(Vertex* newVerte1, Vertex* newVertex2, int weightEdges);
		void deleteEdges(Edges* deletedEdges);//�������� �����
		std::string nameVertex;//��� ���������� ����
		unsigned int precipitationAmount;//���������� ���������, ��� ����� 
	};

	std::unordered_map<std::string,Vertex::Edges*> heshMapEdges;
	std::unordered_map<std::string,Vertex*> vectorVertex;

	Vertex* vertex;//������ ����� ������ ����
	unsigned int iAmountVertex = 0;//���������� �����
	void deleteVertex(Vertex* deletedVertex);//�������� ������� �� ��������
public:
//	Graph();//����������� ����������� ����� 
	~Graph();//����������� �������� �����
	void addVertex();//���������� ������� ��� �����
	void vertexBinding(std::string nameVertex);//���������� ������� � ������������ 
	void deleteVertex(std::string nameVertex);//�������� ������� �� �����
	void connectNodes(std::string nodeConnected, std::string nodeAttached, unsigned int weightEdges = 0);//���������� ���� ����� �����
	unsigned int amountVertex();//����������� ������� ����� � �����
	void takeTheEasiestPath();//���� �� ������ ������� ����
	void takeTheHardPath();//���� �� ������ �������� ����
	Vertex* getVertex(std::string nameVertex);//����� ��� ���������� ��������� �� ���� � ����� 


	void drawAllVertex();
	void showAllVertex();//������� ����� �������
};