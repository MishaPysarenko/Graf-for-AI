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
	outputFile.close();
}

//���������� ������ ����������, ��� ������� ���� ��������� ��������
void Graf::Training1() 
{
	auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());
	double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // ��������� ��������� ������� ����� [0, 1)
	auto vaule = 2.0 * randomFraction - 1.0; // ��������������� � �������� ��� ��������� (-1, 1)

	valueListEdges.clear();

	EditWeightEdges(randomIter->first, vaule);

	// ������� ������ ofstream � ��������� ���� ��� ������ (std::ios::out)
	std::ofstream outputFile("1.txt", std::ios::out);

	for (const auto& pair : heshMapVertex) {
		outputFile << pair.first << "\n";
		for (const auto& element : pair.second->listEdges) {
			outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
		}
	}
	outputFile.close();
}

//���������� ������ ����������, ��� ������� ��� ���� ������� ���� ������ ��������, ����� ��������� � �������� �������������� 
void Graf::Training2(bool result)
{
	valueListEdges.clear();
	if(result)
	{
		if (nameEdges.size() != 0 && beforeEdges != nullptr) {
			auto temp = heshMapEdges.find(beforeEdges->indexEdges);
			temp->second->weightEdges = (temp->second->weightEdges + beforeEdges->weightEdges) / 2;
			std::cout << result << '\t' << temp->first << '\t' << temp->second->weightEdges << '\n';



			std::ofstream outputFile("1.txt", std::ios::out);
			for (const auto& pair : heshMapVertex) {
				outputFile << pair.first << "\n";
				for (const auto& element : pair.second->listEdges) {
					outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
				}
			}
			outputFile.close();
		}
	}
	else
	{
		if (beforeEdges != nullptr)
		{
			heshMapEdges.find(beforeEdges->indexEdges)->second->weightEdges = beforeEdges->weightEdges;
			delete beforeEdges;
		}
		beforeEdges = nullptr;
		beforeEdges = new Edges;
		auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; //��������� ��������� ������� �����(0, 1)
		auto vaule = 2.0 * randomFraction - 1.0;

		beforeEdges->weightEdges = randomIter->second->weightEdges;
		beforeEdges->indexEdges = randomIter->second->indexEdges;

		EditWeightEdges(randomIter->first, vaule);
		nameEdges = randomIter->first;

		std::cout << result << '\t' << randomIter->first << '\t' << randomIter->second->weightEdges << '\n';



		// ������� ������ ofstream � ��������� ���� ��� ������ (std::ios::out)
		std::ofstream outputFile("1.txt", std::ios::out);
		for (const auto& pair : heshMapVertex) {
			outputFile << pair.first << "\n";
			for (const auto& element : pair.second->listEdges) {
				outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
			}
		}
		outputFile.close();
	}

}

void Graf::Training3(bool result)
{
	counter++;
	counterForAddVertex++;
	valueListEdges.clear();
	if (result)
	{
		amountGoodTry++;

		auto temp = heshMapEdges.find(nameEdges);

		cell = new StorageCell;

		if (heshMapTrainingEdges.find(temp->first) != heshMapTrainingEdges.end())
		{
			auto temp1 = heshMapTrainingEdges.find(temp->first);

			auto goodEdges = heshMapTrainingEdges.find(temp1->first);

			cell->amoutnTry = amountGoodTry;
			cell->weight = temp->second->weightEdges;

			goodEdges->second->push_back(cell);
		}
		else
		{
			listStorageCell = new std::list<StorageCell*>;

			cell->amoutnTry = amountGoodTry;
			cell->weight = temp->second->weightEdges;
			listStorageCell->push_back(cell);

			heshMapTrainingEdges[temp->first] = listStorageCell;
		}

	}
	else
	{
		auto randomIter = std::next(heshMapEdges.begin(), std::rand() % heshMapEdges.size());
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // ��������� ��������� ������� ����� [0, 1)
		auto vaule = 2.0 * randomFraction - 1.0; // ��������������� � �������� ��� ��������� (-1, 1)

		beforeEdges = randomIter->second;

		valueListEdges.clear();

		EditWeightEdges(randomIter->first, vaule);

		nameEdges = randomIter->first;

		amountGoodTry = 0;

		if (amountTraing >= 100)
		{
			std::unordered_map<std::string, std::list<StorageCell*>*> temp;

			std::ofstream outputFile("log.txt", std::ios::app);
			outputFile << counter << "\n\n";
			for (const auto& pair : heshMapTrainingEdges)//�������� ����� �������� ������� ����, ��� �������� �� ������� � �� �������� � ����������
			{
				cell = new StorageCell;
				listStorageCell = new std::list<StorageCell*>;
				outputFile << "-----------------------\n";
				outputFile << pair.first << '\n';
				outputFile << "amountTraing " << amountTraing << '\n';
				outputFile << "-----------------------\n";

				long double vaule = 0;
				unsigned int iter = 0;
				for (const auto& element : *pair.second)
				{
					outputFile << element->weight << " - " << element->amoutnTry << '\n';
					vaule += (element->weight * element->amoutnTry);
					iter += element->amoutnTry;
				}
				outputFile << "-----------------------\n";
				outputFile << "vaule - " << vaule << " iter - " << iter << "\n";
				vaule = vaule / iter;
				outputFile << "vaule - " << vaule << "\n";
				outputFile << "-----------------------\n\n\n";
				heshMapEdges.find(pair.first)->second->weightEdges = vaule;

				cell->amoutnTry = 10;
				cell->weight = vaule;
				listStorageCell->push_back(cell);
				temp[pair.first] = listStorageCell;
			}
			outputFile << "\n\n";
			for (const auto& pair : heshMapVertex) {
				outputFile << pair.first << "\n";
				for (const auto& element : pair.second->listEdges) {
					outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
				}
			}
			outputFile << "----------------------------------------------------------------------\n";
			outputFile.close();
			heshMapTrainingEdges.clear();
			heshMapTrainingEdges = temp; 
			temp.clear();				 

			amountTraing = 0;
		}
		if (counterForAddVertex >= 1000)
		{

		}
	}
	amountTraing++;
	std::ofstream outputFile("1.txt", std::ios::out);
	//outputFile << counter << "\n\n";
	for (const auto& pair : heshMapVertex) {
		outputFile << pair.first << "\n";
		for (const auto& element : pair.second->listEdges) {
			outputFile << "\t" << element->indexEdges << " " << element->weightEdges << "\n";
		}
	}
	outputFile.close();
}

//������ ����� ���������� ���������� ���� ����� ����� ����� �������� �������� ��� ��� ��� ����� �� ������ ����, 
//���� ����� ���-�� ������� ��� ����� ���������� ���-�� �� ������
bool Graf::Computation(std::list<bool> vaules)
{
	
	//������� ������� ���������� � ���� �������� ��� ��������� ��������
	for (const auto& pair : heshMapInVertex) {
		long double vaule = 0;
		pair.second->value = *vaules.begin();
		vaules.pop_front();
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
		return pair.second->ActivationFunc(valueListEdges.find(pair.first)->second);//������ ����� �������
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
	for (const auto& pair : heshMapTrainingEdges) {
		for (const auto& element : *pair.second) {//���������� �����
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
