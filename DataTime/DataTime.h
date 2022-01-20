#pragma once
#include <iostream>
#include <string>

class DataTime
{
	

public:
	enum class DayOfTheWeekFormat
	{
		number,
		name
	};

	DataTime();
	DataTime(int amountOfDays);
	DataTime(std::string str);
	DataTime(std::string sample, std::string str);
	~DataTime();

	std::string DayOfTheWeek(DayOfTheWeekFormat state);

	void PrintData();
	void PrintData(std::string sample);

	int GetJDN();
	double GetJD();

	int operator - (DataTime &other);

private:
	std::string getNameOfMonth(int month);
	std::string getNameOfDay(int num);
	int getNumberOfMonth(char* month);
	bool yearIsLeap(int year);

	void checkData();
	void checkDataFoo();
	void checkTime();
	void checkTimeFoo();
	bool checkSample(std::string sample);
	void checkSampleFoo(std::string sample);
	
	std::string str;
	int day;
	int month;
	int year;
	int hh = 0;
	int mm = 0;
	int ss = 0;
	int amountOfDays = 1;
};

