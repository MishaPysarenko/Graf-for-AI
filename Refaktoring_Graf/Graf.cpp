#include "Graf.h"

void Graf::CreateNetwork(unsigned long long int amountInVertex, unsigned long long int amountOutVertex)
{
	for (unsigned long long int  i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (unsigned long long int i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}
	//���������� ���������� ������� � �������� ��������
	std::srand(static_cast<unsigned int>(std::time(nullptr)));//��� ��������� ��������� �����
	for (unsigned long long int i = 0; i < amountInVertex; i++)
	{
		for (unsigned long long int j = amountInVertex; j < amountOutVertex + amountInVertex;j++)
		{
			double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // ��������� ��������� ������� ����� [0, 1)
			auto vaule = 2.0 * randomFraction - 1.0; // ��������������� � �������� ��� ��������� (-1, 1)
			AddEdges("1." + std::to_string(i), "-1." + std::to_string(j), vaule);
		}
	}

	// ������� ������ ofstream � ��������� ���� ��� ������ (std::ios::out)
	std::ofstream outputFile("1.txt", std::ios::out);

	for (const auto& pair : heshMapVertex) {
		outputFile << pair.first << "\n";
		for (const auto& element : pair.second->listEdges) {
			outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
		}
	}

}

void Graf::Training()
{

}
//������ ����� ���������� ���������� ���� ����� ����� ����� �������� �������� ��� ��� ��� ����� �� ������ ����, 
//���� ����� ���-�� ������� ��� ����� ���������� ���-�� �� ������
void Graf::Computation() 
{
	
	//������� ������� ���������� � ���� �������� ��� ��������� ��������
	for (const auto& pair : heshMapInVertex) {
		long double vaule = 0;
		for (const auto& element : pair.second->listEdges) {//���������� �����
			//�������� � ��������� ����������� 
			vaule = (pair.second->value * element->weightEdges);
			valueListEdges[element->nextVertex->indexVertex] += vaule;
		}
	
	}

	//�� ����������� ���� ����, � ��� ��� � ����
	//������������� ������� � �� ��������
	if (heshMapVertex.size() > heshMapInVertex.size() + heshMapOutVertex.size())
	{
		for (const auto& pair : heshMapVertex) {
			//���������� �� ���� �������� �� ����������� ��� ������� ��������� ��� ������� � ��������
			if (heshMapInVertex.find(pair.first) == heshMapInVertex.end() || heshMapOutVertex.find(pair.first) == heshMapOutVertex.end()) {
				for (const auto& element : pair.second->listEdges) {//���������� �����
					//���������� ������
					pair.second->ActivationFunc(valueListEdges.find(pair.first)->second);
					//�������� � ��������� ����������� 
					valueListEdges[pair.first] += (pair.second->value * element->weightEdges);
				}
			}
		}
	}

	//�������� �������
	for (const auto& pair : heshMapOutVertex) {
		//���������� ������
		std::cout << pair.second->ActivationFunc(valueListEdges.find(pair.first)->second) << '\t' << valueListEdges.find(pair.first)->second << '\n';
	}
}

Graf::~Graf()
{
	for (const auto& pair : heshMapVertex) {
		for (const auto& element : pair.second->listEdges) {//���������� �����
			delete element;
		}
		delete pair.second;
	}
}

void Graf::DeleteEdges(std::string nameVertex, std::string nameEdges)
{
	auto temp = heshMapVertex.find(nameVertex)->second;//������� ���� �� �������� ���� ������� �����
	
	for (const auto& element : temp->listEdges) {//���������� � ���� �����
		if (element->indexEdges == nameEdges)//���� �������
		{
			temp->listEdges.remove(element);//������� �� ����� 
			delete element;//�������
		}
	}
}

void Graf::AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//��������� ���������� ��� ������ ����� � ���-�������
	auto tempVertexConnected = heshMapVertex.find(vertexConnected);
	auto tempVertexAttached = heshMapVertex.find(vertexAttached);
	//--------------------------------------------------------------

	edges = new Edges;//������� ����� ����� 
	edges->indexEdges = tempVertexConnected->second->indexVertex + "-" + tempVertexAttached->second->indexVertex;//���� ��� ���, �� ���� �����
	edges->nextVertex = tempVertexAttached->second;//���������� ��������� ���������� �������/���� 
	edges->weightEdges = weightEdges;//���������� ��� �����
	heshMapEdges[edges->indexEdges] = edges;//��������� � ���-������� �����
	amountEdges++;//��������� � �������� +1

	tempVertexConnected->second->listEdges.push_back(edges);//� ������� �� �������� �����, ��������� �����
}

void Graf::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//����� �� ���-������� � �������� ���� � �����
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void Graf::AddInVertex()
{
	vertex = new Vertex;//������� � ����� ������ ����� ������
	vertex->indexVertex = "1." + std::to_string(amountVertex);//���� ��� ��� �������� ���� ��� ������� ����� � ��������� "1."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapInVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� ������� ��������
	amountVertex++;//��������� � �������� +1
}

void Graf::AddOutVertex()
{
	vertex = new Vertex;//������� � ����� ������ ����� ������
	vertex->indexVertex = "-1." + std::to_string(amountVertex);//���� ��� ��� �������� ���� ��� �������� ����� � ��������� "-1."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	heshMapOutVertex[vertex->indexVertex] = vertex;//���������� � ���-������� ��� �������� ��������
	amountVertex++;//��������� � �������� +1
}

void Graf::AddVertex()
{
	vertex = new Vertex;//������� � ����� ������ ����� ������
	vertex->indexVertex = "0." + std::to_string(amountVertex);//���� ��� ��� �������� ���� ��� �������� ����� � ��������� "-1."
	heshMapVertex[vertex->indexVertex] = vertex;//���������� � ���-�������
	amountVertex++;//��������� � �������� +1
}

void Graf::DeleteVertex(std::string nameVertex)
{
	delete heshMapVertex.find(nameVertex)->second;//������� ���� ������� ���� �������
	auto iter = heshMapVertex.find(nameVertex);
	if (iter != heshMapVertex.end()) {
		heshMapVertex.erase(iter);//������� ������� �� ���-�������
	}
}

Graf::Graf()
{

}
