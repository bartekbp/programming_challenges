#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector> 
#include <sstream>


using namespace std;



const string SPACE = " ";
const string COLON = ":";
const int MINUTES_IN_HOUR = 60;
const int STARTING_HOUR = 10;
const int ENDING_HOUR = 18;
const int MAX_INDEX = MINUTES_IN_HOUR * (ENDING_HOUR - STARTING_HOUR);





static pair<int, int> readTime(string str)
{
	string hours = str.substr(0, 2);
	string minutes = str.substr(3, 2);

	return pair<int, int>(atoi(hours.c_str()), atoi(minutes.c_str()));
}


class Nap
{
	string _time;
	int _length;
public:
	Nap(string time, int length): _time(time), _length(length) { }
	string strTime();
	string strLength();
};


string Nap::strTime()
{
	return _time;
};


string Nap::strLength()
{
	ostringstream stream;
	int hour = 0;
	int minute = 0;

	hour = _length / MINUTES_IN_HOUR;
	minute = _length % MINUTES_IN_HOUR;

	if(hour != 0)
	{
		stream << hour << " hours and ";
	}

	stream << minute << " minutes";
	
	return stream.str();
}


bool* readAppointments(int numberOfAppointments)
{
	bool* filledTime = new bool[MAX_INDEX]();

	for(int appointmentNumber = 0; appointmentNumber < numberOfAppointments; appointmentNumber++)
	{
		string tmp;
		getline(cin, tmp);
		pair<int, int> startingTime = readTime(tmp.substr(0, 5));
		pair<int, int> endingTime = readTime(tmp.substr(6, 5));
		int startingIndex = (startingTime.first - STARTING_HOUR) * MINUTES_IN_HOUR + startingTime.second;
		int endingIndex = (endingTime.first - STARTING_HOUR) * MINUTES_IN_HOUR + endingTime.second;

		for(int i = startingIndex; i < endingIndex; i++)
		{
			filledTime[i] = true;
		}
	}

	return filledTime;
}


Nap findLongestNap(bool* filledTime)
{
	int lastFilledIndex = -1;
	int longestNapLength = 0;
	int longestNapIndex = 0;
	for(int i = 0; i < MAX_INDEX; i++)
	{
		if(filledTime[i] == true)
		{
			lastFilledIndex = i;
		}
		else
		{
			int currentNapLength = i - lastFilledIndex;
			if(currentNapLength > longestNapLength)
			{
				longestNapLength = currentNapLength;
				longestNapIndex = lastFilledIndex + 1;
			}
		}
	}

	int hour = (longestNapIndex / MINUTES_IN_HOUR) + STARTING_HOUR;
	int minute = longestNapIndex % MINUTES_IN_HOUR;
	ostringstream out;
	out << hour << COLON;

	if(minute < 10)
	{
		out << "0";
	}
	
	out << minute;

	return Nap(out.str(), longestNapLength);
}


void printSolution(Nap nap, int day)
{
	cout << "Day #" << day << ": the longest nap starts at " << nap.strTime();
	cout << " and will last for " << nap.strLength() << "." << endl;
}


int main_Longest_Nap() 
{
	string tmp;
	getline(cin, tmp);

	int dayNumber = 1;
	while(cin.good() == true)
	{
		int numberOfAppointments = atoi(tmp.c_str());
		bool* filledTime = readAppointments(numberOfAppointments);
		Nap nap = findLongestNap(filledTime);
		printSolution(nap, dayNumber);

		dayNumber++;
		delete[] filledTime;
		getline(cin, tmp);
	}

	return 0;
}