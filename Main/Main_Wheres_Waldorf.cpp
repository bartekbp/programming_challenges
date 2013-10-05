#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector> 
#include <sstream>


using namespace std;


template <class T>
class Array
{
	const int _size;
	T* _data;
	Array<T>& operator=(const Array<T>& other) { throw "IllegalAccessException"; }
public:
	Array(const Array<T>& array) : _size(array._size), _data(array._data) { }
	Array(T* data, int size) : _data(data), _size(size) { }
	T* data() { return _data; }
	int size() const { return _size; }
	T& operator[](int index) { return data()[index]; }
	T& operator[](int index) const { return _data[index]; }
};


typedef bool (*Matching)(const Array<string>& data, int row, int column, string word);
const int NUMBER_OF_MATCHING_STRATEGIES = 8;


bool tryMatchingRowForwardWord(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();
	if(row >= data.size())
	{
		return false;
	}

	if(column + sizeOfWord > data[row].size())
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row][column + i] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingRowReversedWord(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();
	if(row >= data.size())
	{
		return false;
	}

	if(column - sizeOfWord + 1 < 0)
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row][column - i] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingLowerColumn(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row + sizeOfWord > data.size())
	{
		return false;
	}

	if(column >= data[row].size())
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row + i][column] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingUpperColumn(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row - sizeOfWord + 1<  0)
	{
		return false;
	}

	if(column >= data[row].size())
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row - i][column] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingFirstDiagonal(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row - sizeOfWord + 1 < 0)
	{
		return false;
	}

	if(column - sizeOfWord + 1 < 0)
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row - i][column - i] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingSecondDiagonal(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row - sizeOfWord + 1 < 0)
	{
		return false;
	}

	if(column + sizeOfWord > data[row].size())
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row - i][column + i] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingThirdDiagonal(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row + sizeOfWord > data.size())
	{
		return false;
	}

	if(column + sizeOfWord > data[row].size())
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row + i][column + i] == word[i]; i++);

	return i == sizeOfWord;
}


bool tryMatchingFourthDiagonal(const Array<string>& data, int row, int column, string word)
{
	int sizeOfWord = word.size();

	if(row + sizeOfWord > data.size())
	{
		return false;
	}

	if(column - sizeOfWord - 1 < 0)
	{
		return false;
	}

	int i;
	for(i = 0; i < sizeOfWord && data[row + i][column - i] == word[i]; i++);

	return i == sizeOfWord;
}


string* readLines(int rows)
{
	string* data = new string[rows];
	for(int i = 0; i < rows; i++)
	{
		string tmp;
		getline(cin, tmp);
		data[i] = tmp;
	}

	return data;
}


void normalize(string* data, int rows)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < data[i].size(); j++)
		{
			data[i][j] = data[i][j] & ~0x20;
		}
	}
}


Array<string> readGrid()
{
	string tmp;
	getline(cin, tmp);

	istringstream stream(tmp);
	int rows, columns;

	stream >> rows;
	stream >> columns;

	string* data = readLines(rows);
	normalize(data, rows);

	return Array<string>(data, rows);
}


Array<string> readWords()
{
	string tmp;
	int numberOfWords;
	getline(cin, tmp);

	numberOfWords = atoi(tmp.c_str());
	string* words = readLines(numberOfWords);
	normalize(words, numberOfWords);

	return Array<string>(words, numberOfWords);
}


Array<Matching> prepareStrategies()
{
	Matching* matching = new Matching[NUMBER_OF_MATCHING_STRATEGIES];
	matching[0] = tryMatchingRowForwardWord;
	matching[1] = tryMatchingRowReversedWord;
	matching[2] = tryMatchingLowerColumn;
	matching[3] = tryMatchingUpperColumn;
	matching[4] = tryMatchingFirstDiagonal;
	matching[5] = tryMatchingSecondDiagonal;
	matching[6] = tryMatchingThirdDiagonal;
	matching[7] = tryMatchingFourthDiagonal;

	return Array<Matching>(matching, NUMBER_OF_MATCHING_STRATEGIES);
}


Array<pair<int, int> > findMatching(Array<string> data, Array<string> words, Array<Matching> matchingStrategies)
{
	pair<int, int>* pairs = new pair<int, int>[words.size()];
	Array<pair<int, int> > matching(pairs, words.size());

	for(int i = 0; i < data.size(); i++)
	{
		for(int j = 0; j < data[i].size(); j++)
		{
			for(int k = 0; k < words.size(); k++)
			{
				if(words[k] != "")
				{
					for(int m = 0; m < matchingStrategies.size(); m++)
					{
						if(matchingStrategies[m](data, i, j, words[k]))
						{
							matching[k] = pair<int, int>(i, j);
							words[k] = "";
							break;
						}
					}
				}
			}
		}
	}

	return matching;
}


void printMatching(Array<pair<int, int> > matching)
{
	for(int i = 0; i < matching.size(); i++)
	{
		pair<int, int> currentMatching = matching[i];
		cout << currentMatching.first + 1 << " " << currentMatching.second + 1 << endl;
	}
}


int main_Wheres_Waldorf() 
{
	string tmp;
	getline(cin, tmp);
	int numberOfCases = atoi(tmp.c_str());

	Array<Matching> matchingStrategies = prepareStrategies();
	for(int i = 0; i < numberOfCases; i++)
	{
		getline(cin, tmp); // blank line
		Array<string> data = readGrid();
		Array<string> words = readWords();

		Array<pair<int, int> > matching = findMatching(data, words, matchingStrategies);
		printMatching(matching);

		delete[] matching.data();
		delete[] data.data();
		delete[] words.data();
		
		if(i != numberOfCases - 1)
		{
			cout << endl;
		}
	}

	delete[] matchingStrategies.data();
	
	return 0;
}