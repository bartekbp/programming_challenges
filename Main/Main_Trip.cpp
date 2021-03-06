#include <iostream>
#include <cmath>

using namespace std;

double maintain_precision(double value)
{
	return floor(value * 100) / 100;
}

int main_Trip() {
	int n;

	cout.precision(2);
	cout << showpoint << fixed;

	while (cin >> n && n != 0) 
	{
		double* data = new double[n];
		double sum = 0;

		for(int i = 0; i < n; i++)
		{
			cin >> data[i];
			sum += data[i];
		}

		double average = sum / n;

		double need_to_exchange_up = 0;
		double need_to_exchange_down = 0;

		for(int i = 0; i < n; i++)
		{
			if(data[i] > average)
			{
				need_to_exchange_up += maintain_precision(data[i] - average);
			}
			else
			{
				need_to_exchange_down += maintain_precision(average - data[i]);
			}
		}

		double need_to_exchange = need_to_exchange_up > need_to_exchange_down ? need_to_exchange_up : need_to_exchange_down;
		cout << '$' << need_to_exchange << endl;

		delete[] data;
	}

	return 0;
}