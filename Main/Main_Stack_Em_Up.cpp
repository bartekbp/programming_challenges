#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include <sstream>

using namespace std;


const int NUMBER_OF_CARDS_IN_DECK = 52;


void readKnownShuffles(vector<short*>& knownShuffles)
{
	int numberOfShuffles;
	string tmp;
	getline(cin, tmp);
	numberOfShuffles = atoi(tmp.c_str());

	for(int i = 0; i < numberOfShuffles; i++)
	{
		short* currentShuffle = new short[NUMBER_OF_CARDS_IN_DECK];

		for(int j = 0; j < NUMBER_OF_CARDS_IN_DECK; j++)
		{
			cin >> currentShuffle[j];
		}

		knownShuffles.push_back(currentShuffle);
	}
	
	getline(cin, tmp); // eat new line
}


void readPerformedShuffles(deque<short>& performedShuffles)
{
	string tmp;
	while(cin.good())
	{
		getline(cin, tmp);
		if(tmp == "") // empty line or EOF finishes input
		{
			break;
		}

		performedShuffles.push_back(atoi(tmp.c_str()));
	}
}


void initializeDeck(short* deck)
{
	for(int i = 0; i < NUMBER_OF_CARDS_IN_DECK; i++)
	{
		deck[i] = i + 1;
	}
}


const string nameOfSuits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string nameOfSuit(int numberOfCard)
{
	return nameOfSuits[(numberOfCard  - 1)/ 13];
}


const string nameOfCards[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
string nameOfCard(int numberOfCard)
{
	return nameOfCards[(numberOfCard - 1) % 13];
}


void printSolution(short* solution)
{
	for(int i = 0; i < NUMBER_OF_CARDS_IN_DECK; i++)
	{
		cout << nameOfCard(solution[i]) + " of " + nameOfSuit(solution[i]) << endl;
	}
}


void performShuffles(vector<short*>& knownShuffles, deque<short>& performedShuffles)
{
	short* deck = new short[NUMBER_OF_CARDS_IN_DECK];
	initializeDeck(deck);
	short* tmpArray = new short[NUMBER_OF_CARDS_IN_DECK];

	while(performedShuffles.empty() == false)
	{
		int currentShuffleNumber = performedShuffles.front();
		performedShuffles.pop_front();

		short* currentShuffle = knownShuffles[currentShuffleNumber - 1];
		for(int i = 0; i < NUMBER_OF_CARDS_IN_DECK; i++)
		{
			tmpArray[i] = deck[currentShuffle[i] - 1];
		}

		swap(tmpArray, deck);
	}

	printSolution(deck);
	
	delete[] tmpArray;
	delete[] deck;
}


void deleteMemory(vector<short*> data)
{
	for(int i = 0; i < data.size(); i++)
	{
		delete[] data[i];
	}
}


int main_Stack_Em_Up() 
{
	string tmp;
	int numberOfTestCases;
	getline(cin, tmp);
	numberOfTestCases = atoi(tmp.c_str());

	getline(cin, tmp);
	for(int i = 0; i < numberOfTestCases; i++)
	{
		if(i > 0)
		{
			cout << endl;
		}

		vector<short*> knownShuffles;
		readKnownShuffles(knownShuffles);

		deque<short> performedShuffles;
		readPerformedShuffles(performedShuffles);

		performShuffles(knownShuffles, performedShuffles);
		
		deleteMemory(knownShuffles);
	}

	return 0;
}