#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector> 
#include <sstream>


using namespace std;

const string SPACE = " ";



struct Job
{
	int id;
	int penalty;
	int completionTime;
	static Job fromStr(string str, int id);
	Job(int id, int completionTime, int penalty) : id(id), completionTime(completionTime), penalty(penalty) { }
};


Job Job::fromStr(string str, int id) 
{ 
	istringstream stream(str); 
	int completionTime; 
	stream >> completionTime;

	int penalty;
	stream >> penalty;

	return Job(id, completionTime, penalty);
}


vector<Job> readJobs()
{
	string tmp;
	getline(cin, tmp);
	int numberOfJobs = atoi(tmp.c_str());
	vector<Job> jobs;

	for(int numberOfJob = 0; numberOfJob < numberOfJobs; numberOfJob++)
	{
		getline(cin, tmp);
		Job job = Job::fromStr(tmp, numberOfJob + 1);
		jobs.push_back(job);
	}

	return jobs;
}


bool lowerPenalty(Job lhs, Job rhs)
{
	return rhs.penalty * lhs.completionTime < lhs.penalty * rhs.completionTime ;
}


vector<int> solve(vector<Job> jobs)
{
	vector<int> solution;
	sort(jobs.begin(), jobs.end(), lowerPenalty);
	for(int i = 0; i < jobs.size(); i++)
	{
		solution.push_back(jobs[i].id);
	}

	return solution;
}



void printSolution(vector<int> solution)
{
	for(int i = 0; i < solution.size(); i++)
	{
		cout << solution[i];

		if(i != (solution.size() - 1))
		{
			cout << SPACE;
		}
	}

	cout << endl;
}


int main() 
{
	string tmp;
	getline(cin, tmp);
	int numberOfTestCases = atoi(tmp.c_str());

	for(int i = 0; i < numberOfTestCases; i++)
	{
		getline(cin, tmp);
		vector<Job> jobs = readJobs();
		vector<int> solution = solve(jobs);
		printSolution(solution);

		if(i != (numberOfTestCases - 1))
		{
			cout << endl;
		}
	}

	return 0;
}