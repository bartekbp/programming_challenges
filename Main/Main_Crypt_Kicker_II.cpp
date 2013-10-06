#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

const string KNOWN_PLAIN_TEXT = "the quick brown fox jumps over the lazy dog";
const string NO_SOLUTION = "No solution.";
const char SPACE = ' ';


vector<string> readEncryptedText()
{
	string tmp;
	getline(cin, tmp);

	vector<string> encryptedText;
	while(tmp.empty() == false)
	{
		encryptedText.push_back(tmp);
		getline(cin, tmp);
	}

	return encryptedText;
}


map<char, char> createMapping(const vector<string> encryptedText, const string knownLine)
{
	for(int i = 0; i < encryptedText.size(); i++)
	{
		if(encryptedText[i].size() == knownLine.size())
		{
			map<char, char> mapping;
			mapping[SPACE] = SPACE;

			bool matching = true;
			for(int j = 0; j < encryptedText[i].size() && matching; j++)
			{
				char c = encryptedText[i][j];

				if(mapping.find(c) == mapping.end())
				{
					mapping[c] = knownLine[j];
				}
				else if(mapping[c] != knownLine[j])
				{
					matching = false;
				}
			}

			if(matching == true)
			{
				return mapping;
			}
		}
	}

	return map<char, char>();
}


void printSolution(vector<string> encryptedText, map<char, char> mapping)
{
	if(mapping.empty() == true)
	{
		cout << NO_SOLUTION << endl;
		return;
	}

	for(int i = 0; i < encryptedText.size(); i++)
	{
		for(int j = 0; j < encryptedText[i].size(); j++)
		{
			cout << mapping[encryptedText[i][j]];
		}

		cout << endl;
	}
}


int main_Crypt_Kicker_II() 
{
	int numberOfTestCases;
	string tmp;
	getline(cin, tmp);
	numberOfTestCases = atoi(tmp.c_str());

	getline(cin, tmp); // blank line
	for(int testCase = 0; testCase < numberOfTestCases; testCase++)
	{
		vector<string> encryptedText = readEncryptedText();
		map<char, char> mapping = createMapping(encryptedText, KNOWN_PLAIN_TEXT);
		printSolution(encryptedText, mapping);

		if(testCase != numberOfTestCases - 1)
		{
			cout << endl;
		}
	}

	return 0;
}