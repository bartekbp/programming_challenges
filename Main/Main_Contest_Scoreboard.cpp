#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector> 
#include <sstream>

using namespace std;

const char CORRECT = 'C';
const char INCORRECT = 'I';

const unsigned int INCORRECT_RESULT_PENALTY = 20;


struct Score 
{
	unsigned int teamNumber;
	unsigned int penaltyTime;
	set<unsigned int> solvedTasks;
	map<unsigned int, unsigned int> tackledProblems;

	Score() : teamNumber(0), penaltyTime(0) { }
};


void readScores(map<unsigned int, Score>& scores)
{
	string tmp;
	getline(cin, tmp);
	while(cin.good() && tmp.empty() == false)
	{
		istringstream stream(tmp);
		unsigned int teamNumber;
		unsigned int taskNumber;
		unsigned int time;
		char result;
		stream >> teamNumber;
		stream >> taskNumber;
		stream >> time;
		stream >> result;

		Score& score = scores[teamNumber];
		score.teamNumber = teamNumber;
		set<unsigned int>& solvedTasks = score.solvedTasks;
		if(solvedTasks.find(taskNumber) == solvedTasks.end())
		{
			if(result == CORRECT)
			{
				unsigned int penalty = score.tackledProblems[taskNumber];
				solvedTasks.insert(taskNumber);
				score.penaltyTime += time + penalty;
			}
			else if(result == INCORRECT)
			{
				score.tackledProblems[taskNumber] += INCORRECT_RESULT_PENALTY;
			}
		}

		getline(cin, tmp);
	}
}

bool lowerTeamNumber(Score lhs, Score rhs)
{
	return lhs.teamNumber < rhs.teamNumber;
}


bool lessPenaltyTimePredicate(Score lhs, Score rhs)
{
	return lhs.penaltyTime < rhs.penaltyTime;
}


bool moreSolvedProblems(Score lhs, Score rhs)
{
	return lhs.solvedTasks.size() > rhs.solvedTasks.size();
}


void sortResults(vector<Score>& scores)
{
	sort(scores.begin(), scores.end(), lowerTeamNumber);
	stable_sort(scores.begin(), scores.end(), lessPenaltyTimePredicate);
	stable_sort(scores.begin(), scores.end(), moreSolvedProblems);
}


void printSolutions(vector<Score> scores)
{
	for(unsigned int i = 0; i < scores.size(); i++)
	{
		Score score = scores[i];
		cout << score.teamNumber << " ";
		cout << score.solvedTasks.size() << " ";
		cout << score.penaltyTime << endl;
	}

}

int main_Contest_Scoreboard() 
{
	unsigned int numberOfCases;
	cin >> numberOfCases;

	string tmp;
	getline(cin, tmp);
	getline(cin, tmp);
	for(unsigned int i = 0; i < numberOfCases; i++)
	{
		map<unsigned int, Score> scores;
		readScores(scores);

		vector<Score> results;
		for(map<unsigned int, Score>::iterator it = scores.begin(); it != scores.end(); it++)
		{
			results.push_back(it->second);
		}

		sortResults(results);

		if(i > 0)
		{
			cout << endl;
		}

		printSolutions(results);
	}

	return 0;
}