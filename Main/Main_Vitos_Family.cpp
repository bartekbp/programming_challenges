#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;



vector<int> readInput()
{
	int numberOfRelatives;
	cin >> numberOfRelatives;

	vector<int> result;
	for(int relative = 0; relative < numberOfRelatives; relative++)
	{
		int streetNumber;
		cin >> streetNumber;
		result.push_back(streetNumber);
	}

	return result;
}


int processInput(vector<int> input)
{
	sort(input.begin(), input.end());

	int mean = 0;
	int middleIndex = input.size() / 2;
	if((input.size() % 2) != 0)
	{
		mean = input[middleIndex];
	}
	else
	{
		mean = (input[middleIndex - 1] + input[middleIndex]) / 2;
	}

	int mean1 = mean;
	int mean2 = mean + 1;

	int diff1 = 0;
	int diff2 = 0;
	for(int i = 0; i < input.size(); i++)
	{
		diff1 += abs(input[i] - mean1);
		diff2 += abs(input[i] - mean2);
	}

	return min(diff1, diff2);
}


int main_Vitos_Family() 
{
	int numberOfTestCases;
	cin >> numberOfTestCases;

	for(int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++)
	{
		vector<int> input = readInput();
		int output = processInput(input);
		cout << output << endl;
	}

	return 0;
}