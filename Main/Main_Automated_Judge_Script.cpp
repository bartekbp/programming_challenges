#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <ctype.h>

using namespace std;


const string ACCEPTED = "Accepted";
const string PRESENTATION_ERROR = "Presentation Error";
const string WRONG_ANSWER = "Wrong Answer";
const string RUN = "Run";
const char SPACE = ' ';
const char HASH = '#';
const char COLON = ':';


string readSolution(int numberOfLines)
{
	string tmp;

	string solution;
	for(int lineNumber = 0; lineNumber < numberOfLines; lineNumber++)
	{
		getline(cin, tmp);
		solution += tmp;
		solution += '\n';
	}

	return solution;
}


string compareSolutions(string correctSolution, string submittedSolution)
{
	if(correctSolution == submittedSolution)
	{
		return ACCEPTED;
	}

	int j = 0;
	int i = 0;
	while(i < correctSolution.size() && j < submittedSolution.size())
	{
		char correct = correctSolution[i];
		char submitted = submittedSolution[j];

		if(!isdigit(correct) && !isdigit(submitted))
		{
			i++;
			j++;
		}
		else if(isdigit(correct) && !isdigit(submitted))
		{
			j++;
		} 
		else if(!isdigit(correct) && isdigit(submitted))
		{
			i++;
		}
		else if(correct != submitted)
		{
			return WRONG_ANSWER;
		}
		else
		{
			i++;
			j++;
		}
	}

	while(i < correctSolution.size() && !isdigit(correctSolution[i]))
	{
		i++;
	}

	while(j < submittedSolution.size() && !isdigit(submittedSolution[j]))
	{
		j++;
	}

	if(i >= correctSolution.size() && j >= submittedSolution.size())
	{
		return PRESENTATION_ERROR;
	}

	return WRONG_ANSWER;
}


void printResult(string result, int numberOfResultSet)
{
	cout << RUN << SPACE;
	cout << HASH << numberOfResultSet << COLON << SPACE;
	cout << result << endl;
}


int main_Automated_Judge_Script() 
{
	string tmp;
	int inputSetNumber = 1;
	getline(cin, tmp);
	

	while(tmp != "0")
	{
		int numberOfLinesOfCorrectSolution = atoi(tmp.c_str());
	
		string correctSolution = readSolution(numberOfLinesOfCorrectSolution);
		getline(cin, tmp);

		int numberOfLinesOfSubmittedSolution = atoi(tmp.c_str());
		string submittedSolution = readSolution(numberOfLinesOfSubmittedSolution);
		string result = compareSolutions(correctSolution, submittedSolution);

		printResult(result, inputSetNumber);

		getline(cin, tmp);
		inputSetNumber++;
	}

	return 0;
}