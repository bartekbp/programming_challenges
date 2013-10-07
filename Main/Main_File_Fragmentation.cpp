#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector> 
#include <sstream>
#include <bitset>


using namespace std;




vector<string> readInput()
{
	string tmp;
	getline(cin, tmp);

	vector<string> input;
	while(tmp.empty() == false)
	{
		input.push_back(tmp);
		getline(cin, tmp);
	}

	return input;
}


int calculateLength(vector<string> lines)
{
	int sumOfLengths = 0;
	for(int i = 0; i < lines.size(); i++)
	{
		sumOfLengths += lines[i].size();
	}

	return (2 * sumOfLengths) / lines.size();
}


map<int, vector<string> > createLengthToWordsMap(vector<string> words)
{
	map<int, vector<string> > result;
	for(int i = 0; i < words.size(); i++)
	{
		string word = words[i];
		vector<string> currentMapping = result[word.size()];
		currentMapping.push_back(word);
		result[word.size()] = currentMapping;
	}

	return result;
}


bool lowerThan(pair<int, int> lhs, pair<int, int> rhs)
{
	return lhs.first < rhs.first;
}


vector<int> calculateBestOrder(map<int, vector<string> >& lengthToWords, int fileLength)
{
	vector<pair<int, int> > lengthAndSizeOfWords;
	for(map<int, vector<string> >::iterator it = lengthToWords.begin(); it != lengthToWords.end(); it++)
	{
		lengthAndSizeOfWords.push_back(pair<int, int>(it->second.size(), it->first));
	}

	sort(lengthAndSizeOfWords.begin(), lengthAndSizeOfWords.end(), lowerThan);
	vector<int> resultWithDuplicates;
	for(vector<pair<int, int> >::iterator it = lengthAndSizeOfWords.begin(); it != lengthAndSizeOfWords.end(); it++)
	{
		resultWithDuplicates.push_back(it->second);
	}
	
	vector<int> result;
	set<int> chosenLengths;
	for(int i =  0; i < resultWithDuplicates.size(); i++)
	{
		int currentLength = resultWithDuplicates[i];
		if(currentLength > (fileLength / 2))
		{
			currentLength = fileLength - currentLength;
		}

		if(chosenLengths.find(currentLength) == chosenLengths.end())
		{	
			result.push_back(currentLength);
			chosenLengths.insert(currentLength);
		}
	}

	return result;
}


bool calculateSolution_internal(int index, int fileLength, string pattern, map<int, vector<string> >& lengthToWords, vector<int> bestOrder)
{
	int currentIndex = index;
	vector<string>& words = lengthToWords[bestOrder[currentIndex]];
	if(words.size() == 0)
	{
		currentIndex++;
	}

	if(currentIndex >= bestOrder.size())
	{
		return true;
	}

	int currentBestOrder = bestOrder[currentIndex];
	vector<string>& wordsOfSameLength = lengthToWords[currentBestOrder];
	for(int i = 0; i < wordsOfSameLength.size(); i++)
	{	
		string firstWord = wordsOfSameLength[i];
		int length = firstWord.length();
		if(pattern.substr(0, length) != firstWord && pattern.substr(pattern.length() - length) != firstWord)
		{
			continue;
		}

		wordsOfSameLength.erase(wordsOfSameLength.begin() + i, wordsOfSameLength.begin() + i + 1);
		vector<string>& wordsOfComplementaryLength = lengthToWords[fileLength - currentBestOrder];

		for(int j = 0; j < wordsOfComplementaryLength.size(); j++)
		{
			string secondWord = wordsOfComplementaryLength[j];
			wordsOfComplementaryLength.erase(wordsOfComplementaryLength.begin() + j, wordsOfComplementaryLength.begin() + j + 1);

			if(firstWord + secondWord != pattern && secondWord + firstWord != pattern)
			{
				continue;
			}

			if(firstWord + secondWord == pattern)
			{
				if(calculateSolution_internal(currentIndex, fileLength, pattern, lengthToWords, bestOrder))
				{
					return true;
				}
			}

			if(secondWord + firstWord == pattern)
			{
				if(calculateSolution_internal(currentIndex, fileLength, pattern, lengthToWords, bestOrder))
				{
					return true;
				}
			}

			wordsOfComplementaryLength.insert(wordsOfComplementaryLength.begin() + j, secondWord);
		}
		
		wordsOfSameLength.insert(wordsOfSameLength.begin() + i, firstWord);
	}


	return false;
}


string calculateSolution(int fileLength, map<int, vector<string> > lengthToWords, vector<int> bestOrder)
{
	if(bestOrder.empty())
	{
		return "";
	}

	int currentIndex = 0;
	int currentBestOrder = bestOrder[currentIndex];

	vector<string>& wordsOfSameLength = lengthToWords[currentBestOrder];
	for(int i = 0; i < wordsOfSameLength.size(); i++)
	{	
		string firstWord = wordsOfSameLength[i];
		wordsOfSameLength.erase(wordsOfSameLength.begin() + i, wordsOfSameLength.begin() + i + 1);
		vector<string>& wordsOfComplementaryLength = lengthToWords[fileLength - currentBestOrder];

		for(int j = 0; j < wordsOfComplementaryLength.size(); j++)
		{
			string secondWord = wordsOfComplementaryLength[j];
			wordsOfComplementaryLength.erase(wordsOfComplementaryLength.begin() + j, wordsOfComplementaryLength.begin() + j + 1);
			string pattern = firstWord + secondWord;

			if(calculateSolution_internal(currentIndex, fileLength, pattern, lengthToWords, bestOrder))
			{
				return pattern;
			}

			pattern = secondWord + firstWord;
			if(calculateSolution_internal(currentIndex, fileLength, pattern, lengthToWords, bestOrder))
			{
				return pattern;
			}

			wordsOfComplementaryLength.insert(wordsOfComplementaryLength.begin() + j, secondWord);
		}
		
		wordsOfSameLength.insert(wordsOfSameLength.begin() + i, firstWord);
	}

	return "";
}


int main_File_Fragmentation() 
{
	string tmp;
	getline(cin, tmp);
	int numberOfTestCases = atoi(tmp.c_str());
	getline(cin, tmp); // blank line

	for(int numberOfTestCase = 0; numberOfTestCase < numberOfTestCases; numberOfTestCase++)
	{
		vector<string> input = readInput();
		int fileLength = calculateLength(input);
		
		map<int, vector<string> > lengthToWords = createLengthToWordsMap(input);
		vector<int> bestOrder = calculateBestOrder(lengthToWords, fileLength);
		string solution = calculateSolution(fileLength, lengthToWords, bestOrder);

		cout << solution << endl;

		if(numberOfTestCase != numberOfTestCases - 1)
		{
			cout << endl;
		}
	}

	return 0;
}