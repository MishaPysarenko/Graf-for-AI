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
	std::ifstream AIFile(nameFile);

	// ��������, �������� �� ���� �������
	if (!AIFile) {
		return;//����� �� �������
	}

	this->activationFuncPtr = activationFuncPtr;
	this->activationOutFuncPtr = activationOutFuncPtr;

	nameProjectFile = nameFile;
	nameProjectLogFile = nameFile.substr(0, nameFile.find('.')) + " LOG " + GetLocalTime() + ".txt";

	std::string strAmountLayer;
	std::string temp;
	std::string value;
	std::getline(AIFile, temp);//��� ��������� ������� ���� �������� 
	std::getline(AIFile, strAmountLayer);
	if (std::stoi(strAmountLayer) < 2)
	{
		return;
	}
	AddLayerInVertex();
	AddLayerOutVertex();
	std::getline(AIFile, value);
	for (size_t i = 0; i < std::stoi(value); i++)
	{
		AddInVertex();
	}
	std::getline(AIFile, value);
	for (size_t i = 0; i < std::stoi(value); i++)
	{
		AddOutVertex();
	}
	for (size_t i = 0; i < (std::stoi(strAmountLayer) - 2); i++)
	{
		AddLayerVertex();
		std::getline(AIFile, value);
		for (size_t i = 0; i < std::stoi(value); i++)
		{
			AddVertex(std::prev(std::prev(listVertex.end())));
		}
	}
	std::string line;
	while (std::getline(AIFile, line)) {
		std::string firstVertex = line.substr(0, line.find('-'));
		size_t length = line.find('=') - line.find('-') - 1;
		std::string secondVertex = line.substr(line.find('-') + 1, length);
		long double value = std::stod(line.substr(line.find('=') + 1));
		
		std::list<std::shared_ptr<Vertex>>::iterator firstNodeIterator;
		std::list<std::shared_ptr<Vertex>>::iterator secondNodeIterator;

		auto itLayer = listVertex.begin();
		// ����� ������� ����
		for (; itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == firstVertex) {
					firstNodeIterator = itVertex;
					break;
				}
			}
		}

		// ����� ������� ����
		for (itLayer = listVertex.begin(); itLayer != listVertex.end(); ++itLayer) {
			for (auto itVertex = itLayer->begin(); itVertex != itLayer->end(); ++itVertex) {
				if ((*itVertex)->indexVertex == secondVertex) {
					secondNodeIterator = itVertex;
					break;
				}
			}
		}

		// ���� ��� ���� �������, ��������� �����
		if (firstNodeIterator->get()->indexVertex != "" && secondNodeIterator->get()->indexVertex != "") {//��� ������
			AddEdges(firstNodeIterator, secondNodeIterator, value);
		}
	}
	std::ofstream LogFile(nameProjectLogFile, std::ios::out);
	LogFile.close();
	AIFile.close();
}

std::list<bool> ai::perceptron::Computation(std::list<bool> vaules)
{
	valueListEdges.clear();
	std::list<bool> result;
	if (vaules.size() != listVertex.front().size())
		return result;

	for(const auto& Node : listVertex.front())
	{
		valueListEdges[Node->indexVertex] = vaules.front();
		vaules.pop_front();
	}

	for(const auto &Layer : listVertex)
	{
		for (const auto& Node : Layer)
		{
			auto tempValue = Node->ActivationFunc(valueListEdges.find(Node->indexVertex)->second);
			auto list = Node->listEdges;
			for (auto& tempList : *list)
			{
				if (valueListEdges.find(tempList->nextVertex->indexVertex) == valueListEdges.end())
				{
					valueListEdges[tempList->nextVertex->indexVertex] = tempValue * tempList->weightEdges;
				}
				else
				{
					valueListEdges.find(tempList->nextVertex->indexVertex)->second += tempValue * tempList->weightEdges;
				}
			}
		}
	}

	for (const auto& Res : listVertex.back())
	{
		result.push_front(Res->ActivationFunc(valueListEdges.find(Res->indexVertex)->second));
	}

	return result;
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
	}

	for (const auto& pair : heshMapEdges) {
		outputFile << pair.first << "=" << pair.second->weightEdges << '\n';
	}

	outputFile.close();
}
