#include "perceptron.h"

void ai::perceptron::EditWeightEdges(std::string nameEdges, long double weightEdges)
{
	//����� �� ���-������� � �������� ���� � �����
	heshMapEdges.find(nameEdges)->second->weightEdges = weightEdges;
}

void ai::perceptron::AddLayerEdges(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected, std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerAttached)
{
	// ���������� ��� ������� � ������ ����
	for (auto itConnected = vertexLayerConnected->begin(); itConnected != vertexLayerConnected->end(); ++itConnected)
	{
		// ���������� ��� ������� �� ��������� �������
		for (auto itAttached = vertexLayerAttached->begin(); itAttached != vertexLayerAttached->end(); ++itAttached)
		{
			// ��������� ������� ������ �� connected ���� � ������� �������� �� attached ����
			AddEdges(itConnected, itAttached, RandomValue()); // ��������������, ��� weightEdges ��������� ���-�� � ����� ����
		}
	}
}

void ai::perceptron::AddVertex(std::list<std::list<std::shared_ptr<Vertex>>>::iterator vertexLayerConnected)
{
	// ������� ����� �������
	auto newVertex = std::make_shared<Vertex>();
	newVertex->indexVertex = std::to_string(std::distance(listVertex.begin(), vertexLayerConnected)) + "." + std::to_string(vertexLayerConnected->size());
	// ��������� ����� ������� � ������, �� ������� ��������� ��������
	vertexLayerConnected->push_back(newVertex);
}

void ai::perceptron::AddInVertex()
{
	// �������� ������ ���� � ������
	auto& initialLayer = listVertex.front();
	// ������� ����� ����
	auto newVertex = std::make_shared<Vertex>();
	newVertex->indexVertex = "I." + std::to_string(listVertex.front().size());
	// ��������� ����� ���� � ������ ������� ����
	initialLayer.emplace_front(std::move(newVertex));
}

void ai::perceptron::AddOutVertex()
{
	// �������� ��������� ���� � ������
	auto& outputLayer = listVertex.back();
	// ������� ����� ����
	auto newVertex = std::make_shared<Vertex>();
	newVertex->indexVertex = "O." + std::to_string(listVertex.back().size());
	// ��������� ����� ���� � ����� ���������� ����
	outputLayer.emplace_back(std::move(newVertex));
}

void ai::perceptron::AddEdges(std::list<std::shared_ptr<Vertex>>::iterator vertexConnected, std::list<std::shared_ptr<Vertex>>::iterator vertexAttached, long double weightEdges)
{
	//--------------------------------------------------------------
	//��������� ���������� ��� ������ ����� � ���-�������
	auto tempVertexConnected = vertexConnected;
	auto tempVertexAttached = vertexAttached;
	//--------------------------------------------------------------
	edges = std::make_shared<Edges>();//������� ����� ����� 
	edges->indexEdges = tempVertexConnected->get()->indexVertex + "-" + tempVertexAttached->get()->indexVertex;//���� ��� ���, �� ���� �����
	edges->nextVertex = *tempVertexAttached;//���������� ��������� ���������� �������/���� 
	edges->weightEdges = weightEdges;//���������� ��� �����
	heshMapEdges[edges->indexEdges] = edges;//��������� � ���-������� �����
	edges.get()->nextVertex.get()->counterPrt++;

	tempVertexConnected->get()->listEdges->push_back(edges);
}

void ai::perceptron::AddLayerVertex()
{
	// �������� �������� �� ��������� ����
	auto lastLayerIter = std::prev(listVertex.end());

	// ������� ����� ����
	std::list<std::shared_ptr<Vertex>> newLayer;

	// ��������� ����� ���� ����� ��������� �����
	listVertex.insert(lastLayerIter, std::move(newLayer));
}

void ai::perceptron::AddLayerInVertex()
{
	// ������� ����� ������� ����
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// ��������� ������� ���� � ������ ������
	listVertex.emplace_front(std::move(inputLayer));
}

void ai::perceptron::AddLayerOutVertex()
{
	// ������� ����� ������� ����
	std::list<std::shared_ptr<Vertex>> inputLayer;

	// ��������� ������� ���� � ����� ������
	listVertex.emplace_back(std::move(inputLayer));
}

void ai::perceptron::CreateNetwork(size_t amountInVertex, size_t amountOutVertex, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
{
	this->activationFuncPtr = activationFuncPtr;
	this->activationOutFuncPtr = activationOutFuncPtr;

	AddLayerInVertex();
	AddLayerOutVertex();
	for (size_t i = 0; i < amountInVertex; i++)
	{
		AddInVertex();
	}
	for (size_t i = 0; i < amountOutVertex; i++)
	{
		AddOutVertex();
	}

	AddLayerEdges(listVertex.begin(), std::prev(listVertex.end()));
	SaveNetwork();
}

void ai::perceptron::CreateNetwork(std::string nameFile, bool(*activationFuncPtr)(long double), bool(*activationOutFuncPtr)(long double))
{
}

std::list<bool> ai::perceptron::Computation(std::list<bool> vaules)
{
	return std::list<bool>();
}

void ai::perceptron::Training(bool result)
{
}

void ai::perceptron::Logging(std::string nameProjectFile)
{
}

void ai::perceptron::SaveNetwork()
{
	if (nameProjectFile.size() == 0 || nameProjectLogFile.size() == 0)
	{
		nameProjectFile = "AI-.txt";
		nameProjectLogFile = "AI- LOG " + GetLocalTime() + ".txt";
	}

	std::ofstream outputFile(nameProjectFile, std::ios::out);

	outputFile << "P\n";//��� �������� ����

	outputFile << listVertex.size() << '\n';

	for (const auto& pair : listVertex)
	{
		outputFile << pair.size() << '\n';
		for (const auto& it : pair)
		{
			for (const auto& element : *it->listEdges) {
				outputFile << element->indexEdges << "=" << element->weightEdges << '\n';
			}
		}
	}


	outputFile.close();
}
