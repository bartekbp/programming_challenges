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

#define alls(NUMBER) (NUMBER * ((dices[0] == NUMBER) + (dices[1] == NUMBER) + (dices[2] == NUMBER) + (dices[3] == NUMBER) + (dices[4] == NUMBER)))


typedef unsigned int (*strategy)(vector<unsigned int>&);
const unsigned int DICES_IN_ROUND = 5;
const unsigned int NUMBER_OF_ROUNDS = 13;
const unsigned int SIX = 6;
const unsigned int BONUS = 35;
const unsigned int BONUS_LOWER_BOUND = 63;


strategy strategies[NUMBER_OF_ROUNDS];

unsigned int ones(vector<unsigned int>& dices)
{
	return alls(1);
}


unsigned int twos(vector<unsigned int>& dices)
{
	return alls(2);
}


unsigned int threes(vector<unsigned int>& dices)
{
	return alls(3);
}


unsigned int fours(vector<unsigned int>& dices)
{
	return alls(4);
}


unsigned int fives(vector<unsigned int>& dices)
{
	return alls(5);
}


unsigned int sixes(vector<unsigned int>& dices)
{
	return alls(6);
}


unsigned int chance(vector<unsigned int>& dices)
{
	unsigned int sum = 0;
	for(unsigned int i = 0; i < DICES_IN_ROUND; i++)
	{
		sum += dices[i];
	}

	return sum;
}


pair<unsigned int, unsigned int> calculateSumAndMaximumOccurrence(vector<unsigned int>& dices)
{
	unsigned int sum = 0;
	unsigned int maximumCount = 0;
	map<unsigned int, unsigned int> values;

	for(unsigned int i = 0; i < DICES_IN_ROUND; i++)
	{
		sum += dices[i];
		values[dices[i]]++;

		if(values[dices[i]] > maximumCount)
		{
			maximumCount++;
		}
	}

	return pair<unsigned int, unsigned int>(sum, maximumCount);
}


unsigned int threeOfAKind(vector<unsigned int>& dices)
{
	pair<unsigned int, unsigned int> sumAndMaximumCount = calculateSumAndMaximumOccurrence(dices);
	return sumAndMaximumCount.second >= 3 ? sumAndMaximumCount.first : 0;
}


unsigned int fourOfAKind(vector<unsigned int>& dices)
{
	pair<unsigned int, unsigned int> sumAndMaximumCount = calculateSumAndMaximumOccurrence(dices);
	return sumAndMaximumCount.second >= 4 ? sumAndMaximumCount.first : 0;
}


unsigned int fiveOfAKind(vector<unsigned int>& dices)
{
	return (dices[0] == dices[1]) && (dices[1] == dices[2]) && 
		   (dices[2] == dices[3]) && (dices[3] == dices[4]) ? 50 : 0;
}


unsigned int shortStraight(vector<unsigned int>& dices)
{
	for(unsigned int i = 0; i < 2; i++)
	{
		if((dices[i] + 1 == dices[i + 1]) && (dices[i + 1] + 1 == dices[i + 2]) && (dices[i + 2] + 1 == dices[i + 3]))
		{
			return 25;
		}
	}
	
	return 0;
}


unsigned int longStraight(vector<unsigned int>& dices)
{
	if((dices[0] + 1 == dices[1]) && (dices[1] + 1 == dices[2]) && (dices[2] + 1 == dices[3]) && (dices[3] + 1 == dices[4]))
	{
		return 35;
	}

	return 0;
}


unsigned int fullHouse(vector<unsigned int>& dices)
{
	unsigned int sum = 0;
	map<unsigned int, unsigned int> values;

	for(unsigned int i = 0; i < DICES_IN_ROUND; i++)
	{
		sum += dices[i];
		values[dices[i]]++;
	}

	for(unsigned int i = 0; i < SIX; i++)
	{
		if(values[i] == 1 || values[i] == 4 || values[i] == 5)
		{
			return 0;
		}
	}
	
	return 40;
}


void initializeStrategies()
{
	strategies[0] = ones;
	strategies[1] = twos;
	strategies[2] = threes;
	strategies[3] = fours;
	strategies[4] = fives;
	strategies[5] = sixes;
	strategies[6] = chance;
	strategies[7] = threeOfAKind;
	strategies[8] = fourOfAKind;
	strategies[9] = fiveOfAKind;
	strategies[10] = shortStraight;
	strategies[11] = longStraight;
	strategies[12] = fullHouse;
}


unsigned int calculateCostOfSolution(map<pair<unsigned int, unsigned int>, unsigned int>& costs, unsigned int* currentSolution)
{
	unsigned int currentSum = 0;
	for(unsigned int j = 0; j < NUMBER_OF_ROUNDS; j++)
	{
		currentSum += costs[pair<unsigned int, unsigned int>(currentSolution[j], j)];

		if(j == 4 && currentSum >= BONUS_LOWER_BOUND)
		{
			currentSum += BONUS;
		}
	}

	return currentSum;
}


void updateSolution(unsigned int currentSum, unsigned int& max, unsigned int* currentSolution, unsigned int* solution)
{
	max = currentSum;
	for(unsigned int j = 0; j < NUMBER_OF_ROUNDS; j++)
	{
		solution[j] = currentSolution[j];
	}
}


void calculateSolution_internal(int i, const vector<vector<unsigned int> >& dices, map<pair<unsigned int, unsigned int>, unsigned int>& costs, 
								unsigned int* currentSolution, unsigned int& max, unsigned int* solution)
{
	if(i >= 13)
	{
		unsigned int currentSum = calculateCostOfSolution(costs, currentSolution);

		if(currentSum > max)
		{
			updateSolution(currentSum, max, currentSolution, solution);	
		}
	}
	else
	{
		for(unsigned int j = 0; j < NUMBER_OF_ROUNDS; j++)
		{
			swap(currentSolution[i], currentSolution[j]);
			calculateSolution_internal(i + 1, dices, costs, currentSolution, max, solution);
			swap(currentSolution[i], currentSolution[j]);
		}
	}
}


void calculateSolution(vector<vector<unsigned int> >& dices, map<pair<unsigned int, unsigned int>, unsigned int>& costs, unsigned int* solution)
{
	unsigned int currentSolution[NUMBER_OF_ROUNDS];
	for(unsigned int i = 0; i < NUMBER_OF_ROUNDS; i++)
	{
		currentSolution[i] = i;
	}

	for(unsigned int i = 0; i < NUMBER_OF_ROUNDS; i++)
	{
		strategy strategy = strategies[i];
		for(unsigned int j = 0; j < NUMBER_OF_ROUNDS; j++)
		{
			costs[pair<unsigned int, unsigned int>(i, j)] = strategy(dices[j]);
		}
	}

	unsigned int max = 0;
	calculateSolution_internal(0, dices, costs, currentSolution, max, solution);
}


void printSolution(bool first, const vector<vector<unsigned int> >& dices, map<pair<unsigned int, unsigned int>, unsigned int>& costs, unsigned int* solution)
{
	if(first == false)
	{
		cout << endl;
	}

	unsigned int currentSum = 0;
	unsigned int sumOfFirst5 = 0;
	for(unsigned int i = 0; i < NUMBER_OF_ROUNDS; i++)
	{
		unsigned int tmp = costs[pair<unsigned int, unsigned int>(solution[i], i)];
		cout << tmp << " ";
		
		currentSum += tmp;

		if(i == 4)
		{
			sumOfFirst5 = currentSum;
		}
	}

	unsigned int bonus = (sumOfFirst5 > BONUS_LOWER_BOUND) ? BONUS : 0;
	cout << bonus << " " << currentSum + bonus;
}


int main_Yahtzee() 
{
	string tmp;
	bool first = true;
	initializeStrategies();
	getline(cin, tmp);

	while(cin.good())
	{
		vector<vector<unsigned int> > dices;
		for(unsigned int i = 0; i < NUMBER_OF_ROUNDS; i++)
		{
			dices.push_back(vector<unsigned int>());
			istringstream stream(tmp);

			for(unsigned int j = 0; j < DICES_IN_ROUND; j++)
			{
				unsigned int dice;
				stream >> dice;

				dices.back().push_back(dice);
			}

			getline(cin, tmp);
		}

		unsigned int solution[NUMBER_OF_ROUNDS];
		map<pair<unsigned int, unsigned int>, unsigned int> costs;
		calculateSolution(dices, costs, solution);

		printSolution(first, dices, costs, solution);
		first = false;
	}

	return 0;
}