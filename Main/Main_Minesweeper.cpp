#include <iostream>
using namespace std;

int max(int a, int b) {
	if(a > b) {
		return a;
	}

	return b;
}

char calculate_surrounding(char** data, int i, int j, int n, int m) {
	char count = 0;

	for(int k = max(i - 1, 0); k < i + 2 && k < n; k++) {
		for(int l = max(j - 1, 0); l < j + 2 && l < m; l++) {
			if(data[k][l] == '*') {
				count++;
			}
		}
	}

	return count;
}

int main_Minesweeper() {
	int n, m;
	int fields = 1;
	char tmp;
	while (cin >> n >> m && ((n != 0) || (m != 0))) {
		if(fields != 1)
			cout << endl;
		char** data = new char*[n];

		for (int i = 0; i < n; i++) {
			data[i] = new char[m];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> tmp;
				data[i][j] = tmp;
			}
		}

		cout << "Field #" << fields << ":" << endl;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if(data[i][j] == '*') {
					cout << "*";
				} else {
					cout << (int) calculate_surrounding(data, i, j, n, m);
				}
			}
			cout << endl;
		}


		for (int i = 0; i < n; i++) {
			delete [] data[i];
		}

		delete [] data;
		fields++;
	}
}