#include "DataTime.h"
#include <iostream>
#include <iomanip>

int main() 
{
	setlocale(LC_ALL, "rus");

	//������������ ������ �������������
	DataTime data1("11.01.2002");
	DataTime data2("12 ��� 2002");
	DataTime data3("21.01.22");
	DataTime data4("mm:dd:yyyy", "01 : 24 : 2022");
	DataTime data5("yy:mm:dd", "22 : 01 : 21");
	DataTime data6(2459600);
	DataTime data7("yyyy-MM-ddThh:mm:ss","2021-12-21T07:54:34");
	DataTime data8("yyyy-MM-ddThh:mm:ss", "2000-01-01T12:00:00");

	//����� ���� � ����������� �������
	std::cout << "==================================================\n";
	std::cout << "����� ���� � ����������� �������:\n";
	data1.PrintData();
	data2.PrintData();
	data3.PrintData();
	data4.PrintData();
	data5.PrintData();
	data6.PrintData();
	data7.PrintData();
	std::cout << "==================================================";

	//����� ���� � ������� ��������� �������
	std::cout << "\n\n==================================================\n";
	std::cout << "����� ���� � ������� ��������� �������:\n";
	data1.PrintData("mm:dd:yyyy");
	data2.PrintData("yy:mm:dd");
	data3.PrintData("yy ����� dd");
	data4.PrintData("yy month dd");
	data5.PrintData("mm:dd::yy");
	data6.PrintData("dd month yy");
	data7.PrintData("yyyy-MM-ddThh:mm:ss");
	std::cout << "==================================================";

	//������� ����� ������ � ����
	std::cout << "\n\n==================================================\n";
	std::cout << "������� ����� ������ � ����: " << data1 - data2 << "\n";
	std::cout << "������� ����� ������ � ����: " << data1 - data3 << "\n";
	std::cout << "==================================================";

	//���� ������ ��� �������� ����
	std::cout << "\n\n==================================================\n";
	std::cout << "���� ������: " << data1.DayOfTheWeek(DataTime::DayOfTheWeekFormat::number) << "\n";
	std::cout << "���� ������: " << data2.DayOfTheWeek(DataTime::DayOfTheWeekFormat::name) << "\n";
	std::cout << "==================================================";

	//������ ������ � ������� ������ ���
	std::cout << "\n\n==================================================\n";
	std::cout << std::setprecision(16) << "��������� ����: " << data7.GetJDN() << "\n";
	std::cout << std::setprecision(16) << "��������� ����: " << data8.GetJD() << "\n";
	std::cout << "==================================================";

	//�������� �� ����
	std::cout << "\n\n==================================================\n";
	DataTime wrong1("112.01.2301321");
	DataTime wrong2("yy:mm:","12.01.2301");
	DataTime wrong3("yyy-MM-ddThh:mm:Js", "2000-01-01T12:00:00");
	data7.PrintData("yy:mm:");
	std::cout << "==================================================";

	std::cout << "\n\n==================================================\n";
	DataTime EasterTest("01.01.2022");
	EasterTest.foundEaster();
	std::cout << "==================================================\n";

	return 0;
}