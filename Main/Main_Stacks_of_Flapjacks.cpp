#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>



using namespace std;

const char SPACE = ' ';


vector<int> readInput(string input)
{
	istringstream stream(input);
	vector<int> result;

	while(stream.good())
	{
		int diameter;
		stream >> diameter;
		result.push_back(diameter);
	}

	return result;
}


void swapElements(vector<int>& data, int index)
{
	int end = index;

	for(int start = 0; start < end; start++, end--)
	{
		swap(data[start], data[end]);
	}
}


vector<int> processData(vector<int> pancakes)
{
	vector<int> tmp = pancakes;
	vector<int> result;
	for(int i = tmp.size() - 1; i >= 0; i--)
	{
		int max = i;
		for(int j = i - 1; j >= 0; j--)
		{
			if(tmp[j] > tmp[max])
			{
				max = j;
			}
		}

		if(max != i)
		{
			if(max != 0)
			{
				swapElements(tmp, max);
				result.push_back(tmp.size() - max);
			}

			swapElements(tmp, i);
			result.push_back(tmp.size() - i);
		}

	}

	result.push_back(0);
	return result;
}


void printData(vector<int> result)
{
	for(int i = 0; i < result.size(); i++)
	{
		cout << result[i];

		if(i != result.size() - 1)
		{
			cout << SPACE;
		}
	}

	cout << endl;
}


int main_Stacks_of_Flapjacks() 
{
	string tmp;
	getline(cin, tmp);
	while(cin.good())
	{
		vector<int> pancakes = readInput(tmp);
		vector<int> result = processData(pancakes);
		printData(pancakes);
		printData(result);

		getline(cin, tmp);
	}

	return 0;
}