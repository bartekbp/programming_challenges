#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <ctype.h>
#include <queue>


using namespace std;

const char SPACE = ' ';
const string NO_SOLUTION = "No solution.";

struct Node
{
	string word;
	set<Node*> neighbours;
};


bool differByOneLetter(string a, string b)
{
	if(a.size() != b.size())
	{
		return false;
	}

	bool changed = false;
	for(int i = 0; i < a.size(); i++)
	{
		if(a[i] != b[i])
		{
			if(!changed)
			{
				changed = true;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}


map<string, Node*> createInputDictionary(set<string> words)
{
	map<string, Node*> graph;
	for(set<string>::iterator wordIt = words.begin(); wordIt != words.end(); wordIt++)
	{
		string currentWord = *wordIt;
		Node* currentNode = graph[currentWord];		
		if(currentNode == NULL)
		{
			currentNode = new Node();
		}

		currentNode->word = currentWord;
		set<Node*>& neighbours = currentNode->neighbours;

		for(set<string>::iterator nextWordIt = words.begin(); nextWordIt != words.end(); nextWordIt++)
		{
			string nextWord = *nextWordIt;
			if(nextWord == currentWord)
			{
				continue;
			}

			if(differByOneLetter(nextWord, currentWord))
			{
				Node* neighbour = graph[nextWord];
				if(neighbour == NULL)
				{
					neighbour = new Node();
					graph[nextWord] = neighbour;
				}

				neighbours.insert(neighbour);
			}
		}

		graph[currentWord] = currentNode;
	}


	return graph;
}


set<string> readDictionary()
{
	string tmp;
	getline(cin, tmp);
	set<string> words;
	while(tmp.empty() == false)
	{
		words.insert(tmp);
		getline(cin, tmp);
	}

	return words;
}


vector<pair<string, string> > readInputWordPairs()
{
	string tmp;
	getline(cin, tmp);

	vector<pair<string, string> > wordPairs;
	while(tmp.empty() == false)
	{
		string firstAndSecondWord = tmp;

		int delimiterPosition = tmp.find(SPACE);

		string firstWord = firstAndSecondWord.substr(0, delimiterPosition);
		string secondWord = firstAndSecondWord.substr(delimiterPosition + 1);
		wordPairs.push_back(pair<string, string>(firstWord, secondWord));

		getline(cin, tmp);
	}

	return wordPairs;
}


vector<string> calculateSolution(pair<string, string> wordPairs, map<string, Node*> inputDictionary)
{
	set<Node*> visitedNodes;
	map<Node*, Node*> parent;
	Node* startingNode = inputDictionary[wordPairs.first];
	visitedNodes.insert(startingNode);

	queue<Node*> q;
	q.push(startingNode);
	while(q.empty() == false)
	{
		Node* nextNode = q.front();
		q.pop();

		for(set<Node*>::iterator neighbourIt = nextNode->neighbours.begin(); neighbourIt != nextNode->neighbours.end(); neighbourIt++)
		{
			if(visitedNodes.find(*neighbourIt) == visitedNodes.end())
			{
				parent[*neighbourIt] = nextNode;
				q.push(*neighbourIt);
				visitedNodes.insert(*neighbourIt);
			}

			if((*neighbourIt)->word == wordPairs.second)
			{
				break;
			}
		}
	}

	vector<string> reversedSolution;
	Node* node = inputDictionary[wordPairs.second];
	while(node != NULL)
	{
		reversedSolution.push_back(node->word);
		node = parent[node];
	}

	if(reversedSolution.size() == 1)
	{
		return vector<string>();
	}

	reverse(reversedSolution.begin(), reversedSolution.end());
	
	return reversedSolution;
}


void printSolution(vector<string> solution)
{
	if(solution.empty() == true)
	{
		cout << NO_SOLUTION << endl;
		return;
	}
	

	for(int i = 0; i < solution.size(); i++)
	{
		cout << solution[i] << endl;
	}
}


void deleteDictionary(map<string, Node*> inputDictionary)
{
	for(map<string, Node*>::iterator it = inputDictionary.begin(); it != inputDictionary.end(); it++)
	{
		delete it->second;
	}
}


int main_Doublets() 
{
	set<string> words = readDictionary();
	map<string, Node*> inputDictionary = createInputDictionary(words);
	vector<pair<string, string> > inputWordPairs = readInputWordPairs();

	for(int i = 0; i < inputWordPairs.size(); i++)
	{
		vector<string> solution = calculateSolution(inputWordPairs[i], inputDictionary);
		printSolution(solution);

		if(i != inputWordPairs.size() - 1)
		{
			cout << endl;
		}
	}

	deleteDictionary(inputDictionary);

	return 0;
}