#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


int main_Hartals() {
	int t;
	cin >> t;
	for(int testCases = 0; testCases < t; testCases++)
	{
		int n;
		cin >> n;

		int p;
		cin >> p;

		int* hartals = new int[p];
		for(int i = 0; i < p; i++)
		{
			cin >> hartals[i];
		}

		bool* freeDay = new bool[n];
		for(int i = 0; i < n; i++)
		{
			freeDay[i] = true;
		}

		for(int i = 0; i < p; i++)
		{
			for(int j = hartals[i] - 1; j < n; j += hartals[i])
			{
				freeDay[j] = false;
			}
		}

		for(int i = 5; i < n; i += 7)
		{
			freeDay[i] = true;

			if(i + 1 < n)
			{
				freeDay[i + 1] = true;
			}
		}

		int lostDays = 0;
		for(int i = 0; i < n; i++)
		{
			lostDays += freeDay[i] ? 0 : 1;
		}

		cout << lostDays << endl;

		delete freeDay;
		delete hartals;
	}

	return 0;
}