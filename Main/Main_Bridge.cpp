#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

const string SPACE = " ";



class Crossing
{
	int _first;
	int _second;
public:
	Crossing(int first, int second): _first(first), _second(second) { }
	Crossing(int first): _first(first), _second(-1) { }
	string str() const;
};


string Crossing::str() const 
{

	ostringstream out;
	out << this->_first;

	if(this->_second != -1)
	{
		out << SPACE << this->_second;
	}

	return out.str();
}


ostream& operator<<(ostream& out, const Crossing& obj)
{ 
	return out << obj.str(); 
}


struct Solution
{
	int totalTime;
	vector<Crossing> crossings;

	Solution() : totalTime(0), crossings(vector<Crossing>()) { }
};


vector<int> readInputTimes()
{
	string tmp;
	getline(cin, tmp);
	
	
	vector<int> times;
	int n = atoi(tmp.c_str());
	for(int timeOfPerson = 0; timeOfPerson < n; timeOfPerson++)
	{
		getline(cin, tmp);

		int time = atoi(tmp.c_str());
		times.push_back(time);
	}

	return times;
}

bool moreThanTwoPersonNeedToCross(int nextIndex, const vector<int>& times)
{
	return (times.size() - nextIndex) > 1;
}


void addCrossing(vector<Crossing>& crossings, const vector<int>& times, int first, int second)
{
	Crossing crossing(times[first], times[second]);
	crossings.push_back(crossing);
}


void addCrossing(vector<Crossing>& crossings, const vector<int>& times,  int first)
{
	Crossing crossing(times[first]);
	crossings.push_back(crossing);
}


Solution processTimes(vector<int> times)
{
	Solution solution;
	sort(times.begin(), times.end());
	vector<Crossing>& detailedSolution = solution.crossings;

	if(times.size() == 0)
	{
		return solution;
	}
	else if(times.size() == 1)
	{
		addCrossing(detailedSolution, times, 0);
		solution.totalTime += times[0];
		return solution;
	}
	else if(times.size() == 2)
	{
		addCrossing(detailedSolution, times, 0, 1);
		solution.totalTime += times[1];
		return solution;

	}
	
	int nextIndex = 2;
	while(moreThanTwoPersonNeedToCross(nextIndex, times))
	{
		int firstSolution = times[nextIndex] + times[nextIndex + 1] + times[nextIndex] + times[0];
		int secondSolution = times[0] + times[1] + times[nextIndex + 1] + times[1];

		if(firstSolution < secondSolution)
		{
			addCrossing(detailedSolution, times, nextIndex, nextIndex + 1);
			addCrossing(detailedSolution, times, nextIndex);
			addCrossing(detailedSolution, times, nextIndex, 0);
			addCrossing(detailedSolution, times, 0);
			solution.totalTime += firstSolution;
		}
		else
		{
			addCrossing(detailedSolution, times, 0, 1);
			addCrossing(detailedSolution, times, 0);
			addCrossing(detailedSolution, times, nextIndex, nextIndex + 1);
			addCrossing(detailedSolution, times, 1);
			solution.totalTime += secondSolution;
		}

		nextIndex += 2;
	}

	if(nextIndex != times.size())
	{
		solution.totalTime += times[nextIndex] + times[0] + times[1];
		addCrossing(detailedSolution, times, nextIndex, 0);
		addCrossing(detailedSolution, times, 0);
		addCrossing(detailedSolution, times, 0, 1);
	}
	else
	{
		solution.totalTime += times[1];
		addCrossing(detailedSolution, times, 0, 1);
	}
	
	return solution;
}


void printSolution(Solution solution)
{
	cout << solution.totalTime << endl;
	vector<Crossing> solutionDetails = solution.crossings;
	for(int i = 0; i < solutionDetails.size(); i++)
	{
		Crossing currentCrossing = solutionDetails[i];
		cout << currentCrossing << endl;
	}
}


int main_Bridge() 
{
	string tmp;
	getline(cin, tmp);
	int numberOfTestCases = atoi(tmp.c_str());

	for(int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++)
	{
		getline(cin, tmp);

		vector<int> times = readInputTimes();
		Solution solution = processTimes(times);
		printSolution(solution);

		if(testCaseNumber != (numberOfTestCases - 1))
		{
			cout << endl;
		}
	}

	return 0;
}