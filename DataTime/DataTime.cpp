#include "DataTime.h"

DataTime::DataTime()
{
	str = "";
	day = 0;
	month = 0;
	year = 0;
}

DataTime::DataTime(std::string str)
{
	this->str = str;
	char* c_str = new char[str.length() + 1];
	strcpy_s(c_str, str.length() + 1, str.c_str());
	
	char* next_token = NULL; 
	char* pch = strtok_s(c_str, " .:", &next_token);
	for(int i=0;i<3;i++)
	{
		if (i == 0) day = std::stoi(pch);
		if (i == 1 and strlen(pch) < 3) month = std::stoi(pch);
		else if(i == 1) month = getNumberOfMonth(pch);
		if (i == 2 and strlen(pch) == 2) year = std::stoi(pch) + 2000;
		else if(i == 2) year = std::stoi(pch);
		pch = strtok_s(NULL, " .:", &next_token);
	}
	checkData();
}

DataTime::DataTime(int amountOfDays)
{
	this-> amountOfDays = amountOfDays;
	int a = amountOfDays + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;

	day = e - (153 * m + 2) / 5 + 1;
	month = m + 3 - 12 * (m / 10);
	year = 100 * b + d - 4800 + (m / 10);
	checkData();
}

DataTime::DataTime(std::string sample, std::string str)
{
	if (!checkSample(sample))
	{
		this->str = str;
		char* c_str = new char[str.length() + 1];
		strcpy_s(c_str, str.length() + 1, str.c_str());

		char* c_sample = new char[sample.length() + 1];
		strcpy_s(c_sample, sample.length() + 1, sample.c_str());

		char* next_token1 = NULL;
		char* next_token2 = NULL;

		char* pch1 = strtok_s(c_sample, " .:-T", &next_token1);
		char* pch2 = strtok_s(c_str, " .:-T", &next_token2);

		std::string pch1_str;

		int counter = 0;

		while (pch1 != NULL || pch2 != NULL)
		{
			if (pch1 != NULL || pch2 != NULL) {

				pch1_str = pch1;

				if (counter < 3)
				{
					if (pch1_str == "dd" or pch1_str == "DD") day = std::stoi(pch2);
					else if (pch1_str == "mm" or pch1_str == "MM")
					{
						if (strlen(pch2) < 3) month = std::stoi(pch2);
						else month = getNumberOfMonth(pch2);
					}
					else if (pch1_str == "yy" or pch1_str == "YY") year = std::stoi(pch2) + 2000;
					else if (pch1_str == "yyyy" or pch1_str == "YYYY") year = std::stoi(pch2);

					pch1 = strtok_s(NULL, " .:T-", &next_token1);
					pch2 = strtok_s(NULL, " .:T-", &next_token2);
				}
				if (counter > 2)
				{
					if (pch1_str == "mm" or pch1_str == "MM") mm = std::stoi(pch2);
					else if (pch1_str == "hh" or pch1_str == "HH")hh = std::stoi(pch2);
					else if (pch1_str == "ss" or pch1_str == "SS")ss = std::stoi(pch2);

					pch1 = strtok_s(NULL, " .:T-", &next_token1);
					pch2 = strtok_s(NULL, " .:T-", &next_token2);
				}
				counter++;
			}
		}
		checkData();
		if (strchr(str.c_str(), 'T')) checkTime();
	}
}

DataTime::~DataTime()
{
}

void DataTime::PrintData()
{
	if (day < 10) std::cout << "0" << day;
	else std::cout << day;

	if (month < 10)std::cout << ".0" <<  month;
	else std::cout << "." << month;

	std::cout << "." << year << "\n";
}

void DataTime::PrintData(std::string sample)
{
	if (!checkSample(sample))
	{
		char* c_str = new char[sample.length() + 1];
		strcpy_s(c_str, sample.length() + 1, sample.c_str());

		char* next_token = NULL;
		char* pch = strtok_s(c_str, " .:T-", &next_token);

		std::string pch1_str;


		bool flag = strchr(sample.c_str(), 'T');
		bool flag1 = strchr(sample.c_str(), ' ');
		bool flag2 = strchr(sample.c_str(), '-');
		bool flag3 = strchr(sample.c_str(), ':');

		int counter = 0;

		while (pch != NULL)
		{
			if (pch != NULL)
			{
				pch1_str = pch;
				if (counter < 3)
				{
					if (pch1_str == "dd" or pch1_str == "DD")
					{
						if (day < 10) std::cout << "0" << day;
						else std::cout << day;
					}
					else if (pch1_str == "mm" or pch1_str == "MM")
					{
						if (month < 10)std::cout << "0" << month;
						else std::cout << month;
					}
					else if (pch1_str == "yy" or pch1_str == "YY") std::cout << year - 2000;
					else if (pch1_str == "yyyy" or pch1_str == "YYYY") std::cout << year;
					else if (pch1_str == "месяц" or pch1_str == "month") std::cout << "" << getNameOfMonth(month);
				}
				counter++;
				if (counter > 0 and counter < 3 and pch != NULL and flag1 != true and flag2 != true and flag3 != true) std::cout << ".";
				else if (counter > 0 and counter < 3 and pch != NULL)
				{
					if (flag1) std::cout << " ";
					else if (flag2) std::cout << "-";
					else if (flag3) std::cout << ":";
				}

				if (counter == 3 and flag) std::cout << "T";

				if (flag and counter > 2)
				{
					if (pch1_str == "mm" or pch1_str == "MM")
					{
						if (mm > 9) std::cout << mm;
						else std::cout << "0" << mm;
					}
					else if (pch1_str == "hh" or pch1_str == "HH")
					{
						if (hh > 9) std::cout << hh;
						else std::cout << "0" << hh;
					}
					else if (pch1_str == "ss" or pch1_str == "SS")
					{
						if (ss > 9) std::cout << ss;
						else std::cout << "0" << ss;
					}
				}
				if (counter > 3 and counter < 6 and flag) std::cout << ":";
				pch = strtok_s(NULL, " .:T-", &next_token);
			}
		}
		std::cout << "\n";
	}
}

int DataTime::GetJDN()
{
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	
	return day + (int)((153 * m + 2) / static_cast <double>(5)) + 365 * y + (int)(y / static_cast <double>(4)) - (int)(y / static_cast <double>(100)) + (int)(y / static_cast <double>(400)) - 32045;
}

double DataTime::GetJD() 
{
	return GetJDN() + ((hh - static_cast<double>(12)) / 24) + (mm / static_cast<double>(1440)) + (ss / static_cast<double>(86400));
}

std::string DataTime::DayOfTheWeek(DayOfTheWeekFormat state)
{
	int a, y, m, num;
	a = (14 - month) / 12;
	y = year - a;
	m = month + 12 * a - 2;
	num = (7000 + (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
	if (num == 0) num = 7;
	if (state == DayOfTheWeekFormat::number) return std::to_string(num);
	else if (state == DayOfTheWeekFormat::name) return getNameOfDay(num);
}

int DataTime::operator-(DataTime& other)
{
	return std::abs((int)(GetJDN() - other.GetJDN()));
}



int DataTime::getNumberOfMonth(char * month)
{
	int numOfMonth = 0;

	std::string str = month;

	if (str == "января") numOfMonth = 1;
	else if (str == "февраля") numOfMonth = 2;
	else if (str == "марта") numOfMonth = 3;
	else if (str == "апреля") numOfMonth = 4;
	else if (str == "мая") numOfMonth = 5;
	else if (str == "июня") numOfMonth = 6;
	else if (str == "июля") numOfMonth = 7;
	else if (str == "августа") numOfMonth = 8;
	else if (str == "сентебря") numOfMonth = 9;
	else if (str == "октября") numOfMonth = 10;
	else if (str == "ноября") numOfMonth = 11;
	else if (str == "декабря") numOfMonth = 12;

	return numOfMonth;
}

std::string DataTime::getNameOfDay(int num)
{
	std::string str = "";

	if (num == 1) str = "Понедельник";
	if (num == 2) str = "Вторник";
	if (num == 3) str = "Среда";
	if (num == 4) str = "Четверг";
	if (num == 5) str = "Пятница";
	if (num == 6) str = "Суббота";
	if (num == 7) str = "Воскресенье";
	return str;
}

std::string DataTime::getNameOfMonth(int month)
{
	std::string str;

	if (month == 1) str = "января";
	else if (month == 2) str = "февраля";
	else if (month == 3) str = "марта";
	else if (month == 4) str = "апреля";
	else if (month == 5) str = "мая";
	else if (month == 6) str = "июня";
	else if (month == 7) str = "июля";
	else if (month == 8) str = "августа";
	else if (month == 9) str = "сентебря";
	else if (month == 10) str = "октября";
	else if (month == 11) str = "ноября";
	else if (month == 12) str = "декабря";

	return str;
}

bool DataTime::yearIsLeap(int year)
{
	if ((year % 400) == 0) return true;
	else if (((year % 100) != 0) and ((year % 4) == 0)) return true;
	return false;
}

void DataTime::checkData()
{
	try
	{
		checkDataFoo();
	}
	catch (const std::exception&)
	{
		std::cout << "Wrong data!\n";
	}
}
void DataTime::checkDataFoo()
{
	if (day < 1 or day > 31 or month < 1 or month > 12 or year < 1 or amountOfDays < 0) throw std::exception("");
}

void DataTime::checkTime()
{
	try
	{
		checkTimeFoo();
	}
	catch (const std::exception&)
	{
		std::cout << "Wrong time!\n";
	}
}

void DataTime::checkTimeFoo()
{
	if (hh < 0 or hh > 24 or ss < 0 or ss > 60 or mm < 0 or mm > 60) throw std::exception("");
}

bool DataTime::checkSample(std::string sample)
{
	try
	{
		checkSampleFoo(sample);
		return false;
	}
	catch (const std::exception&)
	{
		std::cout << "Wrong sample!\n";
		return true;
	}
}

void DataTime::checkSampleFoo(std::string sample)
{
	if (sample != "")
	{
		char* c_sample = new char[sample.length() + 1];
		strcpy_s(c_sample, sample.length() + 1, sample.c_str());

		char* next_token = NULL;

		char* pch = strtok_s(c_sample, " .:-T", &next_token);

		std::string pch_str;

		int counter = 0;
		
		int correctDataCounter = 0;
		int correctTimeCounter = 0;

		while (pch != NULL)
		{
			if (pch != NULL)
			{
				pch_str = pch;
				if (counter < 3)
				{
					if (pch_str == "dd" or pch_str == "DD") correctDataCounter++;
					else if (pch_str == "mm" or pch_str == "MM") correctDataCounter++;
					else if (pch_str == "yy" or pch_str == "YY") correctDataCounter++;
					else if (pch_str == "yyyy" or pch_str == "YYYY") correctDataCounter++;
					else if (pch_str == "месяц" or pch_str == "month") correctDataCounter++;
				}
				counter++;

				if (strchr(sample.c_str(),'T') and counter > 2)
				{
					if (pch_str == "mm" or pch_str == "MM") correctTimeCounter++;
					else if (pch_str == "hh" or pch_str == "HH") correctTimeCounter++;
					else if (pch_str == "ss" or pch_str == "SS") correctTimeCounter++;
				}
				pch = strtok_s(NULL, " .:-T", &next_token);
			}
		}
		if(counter < 3 or (counter > 3 and counter < 6)) throw std::exception("");
		else if(correctDataCounter !=3) throw std::exception("");
		else if (correctTimeCounter != 3 and (strchr(sample.c_str(), 'T'))) throw std::exception("");
	}
}

void DataTime::foundEaster()
{
	int a = year % 19;
	int b = year % 4;
	int c = year % 7;
	int k = year / 100;
	int d = (19 * a + 15) % 30;
	int e = (2 * b + 4 * c + 6 * d + 6) % 7;

	int f = d + e;

	if (f > 26) std::cout << "Дата пасхи: " << (f - 26) << " " << getNameOfMonth(5) << "\n";
	else if (f <= 26)std::cout << "Дата пасхи: " << (f + 4) << " " << getNameOfMonth(4) << "\n";
}