#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector> 
#include <sstream>
#include <map>
#include <ctype.h>


using namespace std;

const string SPACE = " ";
const string DOLLAR_SIGN = "$";
const string DOT = ".";
const int HOURS_IN_DAY = 24;
const int MINUTES_IN_HOUR = 60;
const int LENGTH_OF_TIME_RECORD = 11;
const int TRIP_COST = 100;
const int ACCOUNT_CHARGE = 200;




enum Type
{
	UNDEFINED, ENTER, EXIT
};


struct Record
{
	string plate;
	long time;
	Type type;
	int distance;
	static Record fromStr(string str);
	Record(string plate, long time, Type type, int distance) : plate(plate), time(time), 
														  type(type), distance(distance) { }
};


int parseTime(string time)
{
	int day = atoi(time.substr(3, 2).c_str());
	int hour = atoi(time.substr(6, 2).c_str());
	int minute = atoi(time.substr(9, 2).c_str());

	int timestamp = day * HOURS_IN_DAY * MINUTES_IN_HOUR;
	timestamp += hour * MINUTES_IN_HOUR;
	timestamp += minute;

	return timestamp;
}


int hours(int timestamp)
{
	return (timestamp / MINUTES_IN_HOUR) % HOURS_IN_DAY;

}


Record Record::fromStr(string str)
{
	istringstream stream(str);
	string plateStr, timeStr, typeStr, distanceStr;
	stream >> plateStr >> timeStr >> typeStr >> distanceStr;

	string plate = plateStr;
	long time = parseTime(timeStr);
	Type type = typeStr == "enter" ? ENTER : EXIT;
	long distance = atol(distanceStr.c_str());

	return Record(plate, time, type, distance);
}


vector<int> readTolls()
{
	vector<int> tolls;
	string tmp;
	getline(cin, tmp);
	istringstream stream(tmp);

	for(int i = 0; i < HOURS_IN_DAY; i++)
	{
		int toll;
		stream >> toll;
		tolls.push_back(toll);
	}

	return tolls;
}


vector<Record> readRecords()
{
	vector<Record> records;
	string tmp;
	getline(cin, tmp);
	while(tmp.empty() == false)
	{
		records.push_back(Record::fromStr(tmp));
		getline(cin, tmp);
	}

	return records;
}


bool timeSorter(Record lhs, Record rhs)
{
	return lhs.time < rhs.time;
}


bool isPossibleMatchingRecord(int i, const vector<Record>& records)
{
	return (i + 1) < records.size();
}


vector<pair<string, int> > calculateSolution(vector<int> tolls, vector<Record> records)
{
	sort(records.begin(), records.end(), timeSorter);
	map<string, vector<Record> > plateToRecords;

	for(int i = 0; i < records.size(); i++)
	{
		string name = records[i].plate;
		vector<Record>& recordsForCurrentPlate = plateToRecords[name];
		recordsForCurrentPlate.push_back(records[i]);
	}

	vector<pair<string, int> > solution;
	for(map<string, vector<Record> >::iterator it = plateToRecords.begin(); it != plateToRecords.end(); it++)
	{
		vector<Record> records = it->second;
		int totalBill = 0;
		bool found = false;
		for(int i = 0; i < records.size(); i++)
		{
			while(isPossibleMatchingRecord(i, records) && records[i].type == EXIT)
			{
				i++;
			}

			if(isPossibleMatchingRecord(i, records))
			{
				Record first = records[i];
				Record second = records[i + 1];
				if(second.type == EXIT)
				{
					i++;
					found = true;
					int distance = abs(first.distance - second.distance);
					int entranceTime = first.time;
					int entranceHour = hours(entranceTime);
					int price = tolls[entranceHour];
					totalBill += price * distance + TRIP_COST;
				}
			}
		}

		if(found)
		{
			totalBill += ACCOUNT_CHARGE;
			solution.push_back(pair<string, int>(it->first, totalBill));
		}
	}

	return solution;
}


bool firstElementComparator(pair<string, int> lhs, pair<string, int> rhs)
{
	return lhs.first < rhs.first;
}


void printSolution(vector<pair<string, int> > solution)
{
	for(int i = 0; i < solution.size(); i++)
	{
		cout << solution[i].first << SPACE << DOLLAR_SIGN;

		int dollars = solution[i].second / 100;
		cout << dollars << DOT;

		int cents = solution[i].second % 100;
		if(cents < 10)
		{
			cout << "0";
		}

		cout << cents << endl;
	}

}


int main_CDVII() 
{
	string tmp;
	getline(cin, tmp);
	int numberOfTestCases = atoi(tmp.c_str());
	getline(cin, tmp);

	for(int i = 0; i < numberOfTestCases; i++)
	{

		vector<int> tolls = readTolls();
		vector<Record> records = readRecords();
		vector<pair<string, int> > solution = calculateSolution(tolls, records);
		printSolution(solution);

		if(i != (numberOfTestCases - 1))
		{
			cout << endl;
		}
	}

	return 0;
}