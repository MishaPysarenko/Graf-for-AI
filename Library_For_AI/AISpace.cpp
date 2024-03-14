#include "AI.h"
#include <cstdlib>//��� ��������� ��������� �����
#include <ctime>
#include <chrono>//��� �������, �������� ��� �����
namespace ai
{
	long double RandomValue(long double localMax, long double localMin)
	{
		double randomFraction = static_cast<double>(std::rand()) / RAND_MAX; // ��������� ��������� ������� ����� [0, 1)
		return localMin + (randomFraction * (localMax - localMin)); // ��������� ����� � �������� ���������
	}

	std::string GetLocalTime()
	{
		//��� ��������� ��������� �����
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// �������� ������� �����
		auto now = std::chrono::system_clock::now();

		// ����������� ����� � ��������� �����
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// ���������� localtime_s ��� ����������� �������������� �������
		std::tm tm_time;
		localtime_s(&tm_time, &now_time);

		// ����������� ����� � ������
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &tm_time);
		std::string LocalTime = buffer;
		return LocalTime;
	}
}