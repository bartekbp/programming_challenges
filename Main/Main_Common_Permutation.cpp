#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string> 


using namespace std;



int main_Common_Permutation() 
{
	string tmp;
	string firstLine;
	string secondLine;
	
	getline(cin, tmp);

	while(cin.good())
	{
		firstLine = tmp;
		getline(cin, secondLine);

		sort(firstLine.begin(), firstLine.end());
		sort(secondLine.begin(), secondLine.end());

		string result;
		set_intersection(firstLine.begin(), firstLine.end(), secondLine.begin(), secondLine.end(), inserter(result, result.end()));
		cout << result << endl;

		getline(cin, tmp);
	}
	
	return 0;
}