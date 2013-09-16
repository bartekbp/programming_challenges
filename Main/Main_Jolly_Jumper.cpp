#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


int main_Jolly_Jumper() {
	const string jolly("Jolly");
	const string not_jolly("Not jolly");

	int n;
	while (cin >> n && n != 0) 
	{
		bool* data = new bool[n - 1];

		for(int i = 0; i < n - 1; i++)
		{
			data[i] = false;
		}

		bool is_jolly = true;

		int tmp;
		int prev;
		cin >> prev;
		for(int i = 1; i < n; i++)
		{
			cin >> tmp;
			int diff = abs(tmp - prev);

			if(diff < n && diff > 0)
			{
				if(data[diff - 1])
				{
					is_jolly = false;
				}
			
				data[diff - 1] = true;
			}
			else
			{
				is_jolly = false;
			}

			prev = tmp;
		}

		cout << (is_jolly ? jolly : not_jolly) << endl;
		delete[] data;
	}

	return 0;
}