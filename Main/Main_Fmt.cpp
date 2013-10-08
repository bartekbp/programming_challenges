#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector> 
#include <sstream>


using namespace std;



const char NEW_LINE = '\n';
const string NEW_LINE_STRING = "\n";
const char SPACE = ' ';
const unsigned int LINE_WIDTH = 72;



string readInput()
{
	string read;
	string tmp;
	getline(cin, tmp);
	bool first = true;

	while(cin.good())
	{
		if(!first)
		{
			read += NEW_LINE_STRING;
		}

		read += tmp;
		getline(cin, tmp);
		first = false;
	}

	return read;
}


bool isAtTheEndOfBlankLine(string str, int position)
{
	int i = position - 1;
	while(i >= 0 && str[i] == SPACE)
	{
		i--;
	}

	return i >= 0 && str[i] == NEW_LINE;
}


bool isFollowedByASpaceOrLineBreak(string str, int position)
{
	int i = position + 1;
	return i < str.size() && ((str[i] == SPACE) || (str[i] == NEW_LINE));
}


bool newLineCanBeRemoved(string str, int position)
{
	if(!(str[position] == NEW_LINE))
	{
		return false;
	}

	if(isAtTheEndOfBlankLine(str, position))
	{
		return false;
	}
			
	return !isFollowedByASpaceOrLineBreak(str, position);
}


string removeNewLines(string input)
{
	string inputWithoutUnnecessaryNewLines = input;
	for(int i = 0; i < input.size(); i++)
	{
		if(newLineCanBeRemoved(input, i))
		{
			inputWithoutUnnecessaryNewLines[i] = SPACE;
		}
	}

	return inputWithoutUnnecessaryNewLines;
}


int newPosition(string input, int position)
{
	int i;
	for(i = position; i < input.size() && input[i] == SPACE; i++);
	return i;
}


vector<string> insertNewLines(string input)
{
	vector<string> output;

	if(input.empty())
	{
		output.push_back(input);
	}

	int position = 0;
	while(position < input.size())
	{
		string tmp = input.substr(position);

		int i = min(LINE_WIDTH, (unsigned int) (input.size() - position));
		
		if(i == LINE_WIDTH)
		{
			while(i > 0 && (input[position + i] != SPACE) && (input[position + i] != NEW_LINE))
			{
				i--;
			}
		}

		if(i <= 0)
		{
			int j;
			for(j = 0; j + position < input.size() && (input[position + j] != SPACE && input[position + j] != NEW_LINE); j++);

			output.push_back(input.substr(position, j));
			position = newPosition(input, position + j);
		}
		else
		{
			output.push_back(input.substr(position, i));
			position = newPosition(input, position + i + 1);
		}
	}


	return output;
}


void printOutput(vector<string> output)
{
	for(int i = 0; i < output.size(); i++)
	{
		cout << output[i] << endl;
	}
}


vector<string> splitOutput(string output)
{
	vector<string> newOutput;
	int i = 0;
	while(i < output.size())
	{
		int newLinePosition = output.find(NEW_LINE, i);
		if(newLinePosition != string::npos)
		{
			newOutput.push_back(output.substr(i, newLinePosition - i));
			i = newLinePosition + 1;
		}
		else
		{
			newOutput.push_back(output.substr(i));
			break;
		}
	}

	return newOutput;
}


vector<string> processOutput(vector<string> splitOutput)
{
	vector<string> newOutput;

	for(int i = 0; i < splitOutput.size(); i++)
	{
		vector<string> newLines = insertNewLines(splitOutput[i]);
		newOutput.insert(newOutput.end(), newLines.begin(), newLines.end());
	}

	return newOutput;
}


vector<string> trailOutput(vector<string> output)
{
	vector<string> newOutput;
	for(int i = 0; i < output.size(); i++)
	{
		string currentLine = output[i];
		int lastPossibleLetter = currentLine.size() - 1;
		while(lastPossibleLetter >= 0 && currentLine[lastPossibleLetter] == SPACE)
		{
			lastPossibleLetter--;
		}

		newOutput.push_back(currentLine.substr(0, lastPossibleLetter + 1));
	}

	return newOutput;
}


int main_Fmt() 
{
	string input = readInput();
	string inputWithRemovedNewLines = removeNewLines(input);
	vector<string> splitOut = splitOutput(inputWithRemovedNewLines);	
	vector<string> newOutput = processOutput(splitOut);
	vector<string> trailedOutput = trailOutput(newOutput);
	printOutput(trailedOutput);
	return 0;
}