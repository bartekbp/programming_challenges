#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <map>
#include <vector> 
#include <streambuf>


using namespace std;



map<char, char> prepareData()
{
	
	map<char, char> characterMapping;
	characterMapping['1'] = '`';
	characterMapping['2'] = '1';
	characterMapping['3'] = '2';
	characterMapping['4'] = '3';
	characterMapping['5'] = '4';
	characterMapping['6'] = '5';
	characterMapping['7'] = '6';
	characterMapping['8'] = '7';
	characterMapping['9'] = '8';
	characterMapping['0'] = '9';
	characterMapping['-'] = '0';
	characterMapping['='] = '-';

	characterMapping['W'] = 'Q';
	characterMapping['E'] = 'W';
	characterMapping['R'] = 'E';
	characterMapping['T'] = 'R';
	characterMapping['Y'] = 'T';
	characterMapping['U'] = 'Y';
	characterMapping['I'] = 'U';
	characterMapping['O'] = 'I';
	characterMapping['P'] = 'O';
	characterMapping['['] = 'P';
	characterMapping[']'] = '[';
	characterMapping['\\'] = ']';

	characterMapping['S'] = 'A';
	characterMapping['D'] = 'S';
	characterMapping['F'] = 'D';
	characterMapping['G'] = 'F';
	characterMapping['H'] = 'G';
	characterMapping['J'] = 'H';
	characterMapping['K'] = 'J';
	characterMapping['L'] = 'K';
	characterMapping[';'] = 'L';
	characterMapping['\''] = ';';

	characterMapping['X'] = 'Z';
	characterMapping['C'] = 'X';
	characterMapping['V'] = 'C';
	characterMapping['B'] = 'V';
	characterMapping['N'] = 'B';
	characterMapping['M'] = 'N';
	characterMapping[','] = 'M';
	characterMapping['.'] = ',';
	characterMapping['/'] = '.';

	return characterMapping;
}


int main_Wertyu() 
{
	map<char, char> mapping = prepareData();
	char c;
	cin.get(c);

	while(cin.eof() == false)
	{
		if(mapping.find(c) == mapping.end())
		{
			cout << c;
		}
		else
		{
			cout << mapping[c];
		}

		cin.get(c);
	}

	cout << endl;
	return 0;
}