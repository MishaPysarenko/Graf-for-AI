#pragma once
#include "Graf.h"
namespace ai
{
	class freeNetwork : public Graf
	{
		struct StorageCell
		{
			long double weight;
			unsigned int amoutnTry;
		};

		struct StorageCellForComputation
		{
			long double value;
			unsigned long long int amountOfCalculations;
		};

		std::shared_ptr<std::list<StorageCell>> listStorageCell;
		std::shared_ptr<Edges> beforeEdges;
		std::string nameEdges;
		std::shared_ptr<StorageCell> cell;
		std::shared_ptr<StorageCellForComputation> cellForCompulation;

		unsigned long long int amountGoodTry = 0;
		unsigned long long int counterForAddVertex = 0;
		unsigned long long int amountTraing = 0;
		unsigned long long int counterTraing = 0;
		bool flag = 0;

		//----------------------------------------------------------------------------------------------
		//���-������� ��� ���������� ������������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInterVertex;
		//���-������� ��� ���������� ������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapInVertex;
		//���-������ ��� ���������� �������� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapOutVertex;
		//���-������� ��� ���������� ����� ������� ���� ������ �������� � ���������� �������� ��� �� �������������
		std::unordered_map<std::string, std::shared_ptr<std::list<StorageCell>>> heshMapTrainingEdges;
		//���-������� ��� ���������� ���� ��������
		std::unordered_map<std::string, std::shared_ptr<Vertex>> heshMapVertex;
		//���-������� ��� ���������� �����
		std::unordered_map<std::string, std::shared_ptr<Edges>> heshMapEdges;
		//���-������� �������� ���������� ����� ��� ������� �������
		std::unordered_map<std::string, std::shared_ptr<StorageCellForComputation>> valueListEdges;
		//----------------------------------------------------------------------------------------------
		//������� �����
		void DeleteEdges(std::string nameVertex, std::string nameEdges);
		//���������� �����
		void AddEdges(std::string vertexConnected, std::string vertexAttached, long double weightEdges);
		//��������� ���� ����� � ���� ��������
		void EditWeightEdges(std::string nameEdges, long double weightEdges);
		//----------------------------------------------------------------------------------------------
		//��������� ����� ������� ������
		void AddInVertex();
		//��������� ����� �������� ������
		void AddOutVertex();
		//��������� ����� ������������� ������ ����� ����� �������
		void AddVertex(std::string vertexConnected, std::string vertexAttached);
		//��������� ����� ������������� ������
		void AddVertex();
		//������� ������������� ������
		void DeleteVertex(std::string nameVertex);

	public:
		void CreateNetwork(size_t amountInVertex, size_t amountOutVertex, bool (*activationFuncPtr)(long double) = nullptr, bool(*activationOutFuncPtr)(long double) = nullptr) override;
		void CreateNetwork(std::string nameFile, bool (*activationFuncPtr)(long double) = nullptr, bool(*activationOutFuncPtr)(long double) = nullptr)override;
		std::list<bool> Computation(std::list<bool> vaules) override;
		void Training(bool result) override;
		void Logging(std::string nameProjectFile) override;
		void SaveNetwork() override;
		~freeNetwork()
		{
			SaveNetwork();
		}
		freeNetwork(std::string nameFile, std::string nameLogFile)
		{
			nameProjectFile = nameFile;
			nameProjectLogFile = nameLogFile;
		}
	};
}