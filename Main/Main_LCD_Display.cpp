#include <iostream>
#include <string>

using namespace std;


const char upper_row = 0;
const char upper_column = 1;
const char medium_row = 2;
const char lower_column = 3;
const char lower_row = 4;
const char letter_width = 3;

template<typename T>
T*** allocate_array(int x, int y, int z)
{
	T*** data = new T**[x];

	for(int i = 0; i < x; i++)
	{
		data[i] = new T*[y];

		for(int j = 0; j < y; j++)
		{
			data[i][j] = new T[z];
		}
	}

	return data;
}

void fill_in_letters(char*** text)
{
	text[0][upper_row][0] = ' ';
	text[0][upper_row][1] = '-';
	text[0][upper_row][2] = ' ';

	text[0][upper_column][0] = '|';
	text[0][upper_column][1] = ' ';
	text[0][upper_column][2] = '|';

	text[0][medium_row][0] = ' ';
	text[0][medium_row][1] = ' ';
	text[0][medium_row][2] = ' ';

	text[0][lower_column][0] = '|';
	text[0][lower_column][1] = ' ';
	text[0][lower_column][2] = '|';

	text[0][lower_row][0] = ' ';
	text[0][lower_row][1] = '-';
	text[0][lower_row][2] = ' ';


	text[1][upper_row][0] = ' ';
	text[1][upper_row][1] = ' ';
	text[1][upper_row][2] = ' ';

	text[1][upper_column][0] = ' ';
	text[1][upper_column][1] = ' ';
	text[1][upper_column][2] = '|';

	text[1][medium_row][0] = ' ';
	text[1][medium_row][1] = ' ';
	text[1][medium_row][2] = ' ';

	text[1][lower_column][0] = ' ';
	text[1][lower_column][1] = ' ';
	text[1][lower_column][2] = '|';

	text[1][lower_row][0] = ' ';
	text[1][lower_row][1] = ' ';
	text[1][lower_row][2] = ' ';


	text[2][upper_row][0] = ' ';
	text[2][upper_row][1] = '-';
	text[2][upper_row][2] = ' ';

	text[2][upper_column][0] = ' ';
	text[2][upper_column][1] = ' ';
	text[2][upper_column][2] = '|';

	text[2][medium_row][0] = ' ';
	text[2][medium_row][1] = '-';
	text[2][medium_row][2] = ' ';

	text[2][lower_column][0] = '|';
	text[2][lower_column][1] = ' ';
	text[2][lower_column][2] = ' ';

	text[2][lower_row][0] = ' ';
	text[2][lower_row][1] = '-';
	text[2][lower_row][2] = ' ';


	text[3][upper_row][0] = ' ';
	text[3][upper_row][1] = '-';
	text[3][upper_row][2] = ' ';

	text[3][upper_column][0] = ' ';
	text[3][upper_column][1] = ' ';
	text[3][upper_column][2] = '|';

	text[3][medium_row][0] = ' ';
	text[3][medium_row][1] = '-';
	text[3][medium_row][2] = ' ';

	text[3][lower_column][0] = ' ';
	text[3][lower_column][1] = ' ';
	text[3][lower_column][2] = '|';

	text[3][lower_row][0] = ' ';
	text[3][lower_row][1] = '-';
	text[3][lower_row][2] = ' ';


	text[4][upper_row][0] = ' ';
	text[4][upper_row][1] = ' ';
	text[4][upper_row][2] = ' ';

	text[4][upper_column][0] = '|';
	text[4][upper_column][1] = ' ';
	text[4][upper_column][2] = '|';

	text[4][medium_row][0] = ' ';
	text[4][medium_row][1] = '-';
	text[4][medium_row][2] = ' ';

	text[4][lower_column][0] = ' ';
	text[4][lower_column][1] = ' ';
	text[4][lower_column][2] = '|';

	text[4][lower_row][0] = ' ';
	text[4][lower_row][1] = ' ';
	text[4][lower_row][2] = ' ';


	text[5][upper_row][0] = ' ';
	text[5][upper_row][1] = '-';
	text[5][upper_row][2] = ' ';

	text[5][upper_column][0] = '|';
	text[5][upper_column][1] = ' ';
	text[5][upper_column][2] = ' ';

	text[5][medium_row][0] = ' ';
	text[5][medium_row][1] = '-';
	text[5][medium_row][2] = ' ';

	text[5][lower_column][0] = ' ';
	text[5][lower_column][1] = ' ';
	text[5][lower_column][2] = '|';

	text[5][lower_row][0] = ' ';
	text[5][lower_row][1] = '-';
	text[5][lower_row][2] = ' ';


	text[6][upper_row][0] = ' ';
	text[6][upper_row][1] = '-';
	text[6][upper_row][2] = ' ';

	text[6][upper_column][0] = '|';
	text[6][upper_column][1] = ' ';
	text[6][upper_column][2] = ' ';

	text[6][medium_row][0] = ' ';
	text[6][medium_row][1] = '-';
	text[6][medium_row][2] = ' ';

	text[6][lower_column][0] = '|';
	text[6][lower_column][1] = ' ';
	text[6][lower_column][2] = '|';

	text[6][lower_row][0] = ' ';
	text[6][lower_row][1] = '-';
	text[6][lower_row][2] = ' ';


	text[7][upper_row][0] = ' ';
	text[7][upper_row][1] = '-';
	text[7][upper_row][2] = ' ';

	text[7][upper_column][0] = ' ';
	text[7][upper_column][1] = ' ';
	text[7][upper_column][2] = '|';

	text[7][medium_row][0] = ' ';
	text[7][medium_row][1] = ' ';
	text[7][medium_row][2] = ' ';

	text[7][lower_column][0] = ' ';
	text[7][lower_column][1] = ' ';
	text[7][lower_column][2] = '|';

	text[7][lower_row][0] = ' ';
	text[7][lower_row][1] = ' ';
	text[7][lower_row][2] = ' ';


	text[8][upper_row][0] = ' ';
	text[8][upper_row][1] = '-';
	text[8][upper_row][2] = ' ';

	text[8][upper_column][0] = '|';
	text[8][upper_column][1] = ' ';
	text[8][upper_column][2] = '|';

	text[8][medium_row][0] = ' ';
	text[8][medium_row][1] = '-';
	text[8][medium_row][2] = ' ';

	text[8][lower_column][0] = '|';
	text[8][lower_column][1] = ' ';
	text[8][lower_column][2] = '|';

	text[8][lower_row][0] = ' ';
	text[8][lower_row][1] = '-';
	text[8][lower_row][2] = ' ';


	text[9][upper_row][0] = ' ';
	text[9][upper_row][1] = '-';
	text[9][upper_row][2] = ' ';

	text[9][upper_column][0] = '|';
	text[9][upper_column][1] = ' ';
	text[9][upper_column][2] = '|';

	text[9][medium_row][0] = ' ';
	text[9][medium_row][1] = '-';
	text[9][medium_row][2] = ' ';

	text[9][lower_column][0] = ' ';
	text[9][lower_column][1] = ' ';
	text[9][lower_column][2] = '|';

	text[9][lower_row][0] = ' ';
	text[9][lower_row][1] = '-';
	text[9][lower_row][2] = ' ';
}

template<typename T>
void delete_array(T* data, int x, int y)
{
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			delete[] data[i][j];
		}

		delete[] data[i];
	}

	delete[] data;
}

void print_row(char*** text, char number, int row, int size_of_digit)
{
	char** text_of_number = text[number];
	char* text_row = text_of_number[row];
	
	char c = text_row[0];
	cout << c;

	c = text_row[1];
	for(int i = 0; i < size_of_digit; i++)
	{
		cout << c;
	}


	c = text_row[2];
	cout << c;
}

void print_column(char*** text, char number, int row, int size_of_digit)
{
	char** text_of_number = text[number];
	char* text_row = text_of_number[row];

	char c = text_row[0];
	cout << c;

	for(int i = 0; i < size_of_digit - 1; i++)
	{
		cout << ' ';
	}

	c = text_row[1];
	cout << c;


	c = text_row[2];
	cout << c;
}

void print_number_row(char*** text, string number, int row, int size_of_digit)
{
	bool first = true;
	for(int i = 0; i < number.length(); i++)
	{
		if(!first)
		{
			cout << " ";
		}

		first = false;

		print_row(text, number.at(i) - '0', row, size_of_digit);
	}

	cout << endl;
}

void print_number_column(char*** text, string number, int row, int size_of_digit)
{
	for(int i = 0; i < size_of_digit; i++)
	{
		bool first = true;
		for(int j = 0; j < number.length(); j++)
		{
			if(!first)
			{
				cout << " ";
			}

			first = false;

			print_column(text, number.at(j) - '0', row, size_of_digit);
		}

		cout << endl;
	}

}

bool number_and_size_equal_zero(string number, int size_of_digit)
{
	return size_of_digit == 0 && number.length() == 1 && number.at(0) == '0';
}

int main_LCD_Display() {
	int size_of_digit;
	string number;

	char*** text =  allocate_array<char>(10, 5, 3);
	fill_in_letters(text);

	while (cin >> size_of_digit && cin >> number && !number_and_size_equal_zero(number, size_of_digit)) 
	{
		print_number_row(text, number, 0, size_of_digit);
		print_number_column(text, number, 1, size_of_digit);
		print_number_row(text, number, 2, size_of_digit);
		print_number_column(text, number, 3, size_of_digit);
		print_number_row(text, number, 4, size_of_digit);

		cout << endl;
	}

	delete_array(text, 10, 5);
	return 0;
}