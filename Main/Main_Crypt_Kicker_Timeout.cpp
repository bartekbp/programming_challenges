#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>

using namespace std;


pair<bool, map<char, char> > trySolve_internal(map<pair<int, int>, set<string> >& wordsInDictionary, vector<pair<pair<int, int>, string> >& wordsInText, int i, map<char, char>& charMapping)
{
	if(i >= wordsInText.size())
	{
		return pair<bool, map<char, char> >(true, charMapping);
	}

	set<string> wordsOfSameNumberOfDifferentLetters = wordsInDictionary[wordsInText[i].first];
	for(set<string>::iterator it = wordsOfSameNumberOfDifferentLetters.begin(); it != wordsOfSameNumberOfDifferentLetters.end(); it++)
	{
		string word = *it;
		bool possibleMapping = true;
		map<char, char> tmp = charMapping;
		for(int j = 0; j < word.size() && possibleMapping; j++)
		{
			if(tmp[wordsInText[i].second[j]] != '\0' && tmp[wordsInText[i].second[j]] != word[j])
			{
				possibleMapping = false;
				break;
			}
			else
			{
				tmp[wordsInText[i].second[j]] = word[j];
			}
		}

		if(possibleMapping == false)
		{
			continue;
		}
		
		pair<bool, map<char, char> > result = trySolve_internal(wordsInDictionary, wordsInText, i + 1, tmp);
		if(result.first)
		{
			return result;
		}
	}

	return pair<bool, map<char, char> >(false, map<char, char>());
}


map<char, char> trySolve(map<pair<int, int>, set<string> > wordsInDictionary, vector<pair<pair<int, int>, string> > wordsInText)
{
	map<char, char> charMapping;
	pair<bool, map<char, char> > result = trySolve_internal(wordsInDictionary, wordsInText, 0, charMapping);
	if(result.first)
	{
		return result.second;
	}

	for(int i = 0; i < wordsInText.size(); i++)
	{
		for(int j = 0; j < wordsInText[i].second.size(); j++)
		{
			charMapping[wordsInText[i].second[j]] = '*';
		}
	}

	return charMapping;
}

string compactWord(string word)
{
	bool occurrences[25];
	for(int j = 0; j < 25; j++)
	{
		occurrences[j] = false;
	}

	string compactedWord;
	for(int i = 0; i < word.length(); i++)
	{
		if(occurrences[word[i] - 'a'] == false)
		{
			occurrences[word[i] - 'a'] = true;
			compactedWord += word[i];
		}
	}

	return compactedWord;
}

vector<pair<pair<int, int>, string> > compactWords(vector<string>& words)
{
	vector<pair<pair<int, int>, string> > result;
	for(int i = 0; i < words.size(); i++)
	{
		string compactedWord = compactWord(words[i]);
		pair<int, int> key(words[i].size(), compactedWord.size());
		result.push_back(pair<pair<int, int>, string>(key, compactedWord));
	}

	return result;
}


map<pair<int, int>, set<string> > wordsInDictionary;

void updateDifferentWordsMap(map<pair<int, int>, set<string> >& wordsInDictionary, string word)
{
	string compactedWord = compactWord(word);
	pair<int, int> wordIndex = pair<int, int>(word.size(), compactedWord.length());
	set<string> wordsOfSameLenght = wordsInDictionary[wordIndex];
	wordsOfSameLenght.insert(compactedWord);
	wordsInDictionary[wordIndex] = wordsOfSameLenght;
}


int main_Crypt_Kicker() 
{
	int word_count;
	string word;
	getline(cin, word);
	word_count = atoi(word.c_str());

	for(int word_number = 0; word_number < word_count; word_number++)
	{
		getline(cin, word);
		updateDifferentWordsMap(wordsInDictionary, word);
	}

	while(cin.good())
	{
		string line;

		getline(cin, line); 
		istringstream lineStream(line);
		vector<string> wordsInText;
		while(lineStream.good())
		{
			string word;
			lineStream >> word;
			wordsInText.push_back(word);
		}

		vector<pair<pair<int, int>, string> > tmp = compactWords(wordsInText);
		sort(tmp.begin(), tmp.end());

		std::vector<pair<pair<int, int>, string> >::iterator it = unique(tmp.begin(), tmp.end());
		tmp.resize(distance(tmp.begin(), it));

		map<char, char> solution = trySolve(wordsInDictionary, tmp);

		for(int i = 0; i < wordsInText.size(); i++)
		{
			if(i > 0)
			{
				cout << " ";
			}

			for(int j = 0; j < wordsInText[i].size(); j++)
			{
				cout << solution[wordsInText[i][j]];
			}
		}

		cout << endl;
	}

	return 0;
}