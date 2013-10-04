#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <climits>


using namespace std;


const string ERDOS = "Erdos, P.";
const string INFINITY = "infinity";
const string SCENARIO = "Scenario ";
const char COMMA = ',';
const char COLON = ':';



struct Book
{
	set<string> authors;
};


struct Author
{
	string name;
	unsigned int distance;
	set<Author*> coAuthors;
	Author(string name): distance(UINT_MAX), name(name) { }
};


pair<size_t, string> readAuthor(size_t firstName, string authorsLine)
{
	size_t nextComma = authorsLine.find(COMMA, firstName + 1);
	size_t commaAfterLastName = authorsLine.find(COMMA, nextComma + 1);
	if(commaAfterLastName == string::npos)
	{
		commaAfterLastName = authorsLine.size();
	}

	return pair<size_t, string>(commaAfterLastName + 2, authorsLine.substr(firstName, commaAfterLastName - firstName));
}


set<string> readAuthors()
{
	string tmp;
	getline(cin, tmp);

	size_t colon = tmp.find(COLON);
	string authorsLine = tmp.substr(0, colon);
	size_t firstName = 0;
	set<string> authors;
	while(firstName < authorsLine.size())
	{
		pair<size_t, string> nextFirstNameAndAuthor = readAuthor(firstName, authorsLine);
		string author = nextFirstNameAndAuthor.second;
		authors.insert(author);

		firstName = nextFirstNameAndAuthor.first;
	}

	return authors;
}


bool greaterThanPredicate(Author* lhs, Author* rhs)
{
	return lhs->distance > rhs->distance;
}


vector<Book> readBooks(int p)
{
	vector<Book> books;
	for(unsigned int j = 0; j < p; j++)
	{
		set<string> authors = readAuthors();

		Book book;
		book.authors = authors;

		books.push_back(book);
	}

	return books;
}


vector<string> readAuthors(int n)
{
	vector<string> authors;
	for(unsigned int j = 0; j < n; j++)
	{
		string author;
		getline(cin, author);

		authors.push_back(author);
	}

	return authors;
}


void generateAuthorGraph(map<string, Author*>& nameToAuthor, vector<Book> books)
{
	for(unsigned int j = 0; j < books.size(); j++)
	{
		set<string> currentAuthors = books[j].authors;
		set<Author*> coAuthors;
		for(set<string>::iterator it = currentAuthors.begin(); it != currentAuthors.end(); it++)
		{
			Author* author;
			if(nameToAuthor.find(*it) != nameToAuthor.end())
			{
				author = nameToAuthor[*it];
			}
			else
			{
				author = new Author(*it);
				nameToAuthor[*it] = author;
			}
				
			coAuthors.insert(author);
		}

		for(set<Author*>::iterator it = coAuthors.begin(); it != coAuthors.end(); it++)
		{
			set<Author*> unionOfCoAuthors;
			set_union((*it)->coAuthors.begin(), (*it)->coAuthors.end(), coAuthors.begin(), coAuthors.end(), inserter(unionOfCoAuthors, unionOfCoAuthors.end()));
			unionOfCoAuthors.erase(unionOfCoAuthors.find(*it));
			(*it)->coAuthors = unionOfCoAuthors;
		}
	}
}


string erdosNumber(unsigned int number)
{
	if(number == UINT_MAX)
	{
		return INFINITY;
	}
	
	ostringstream stream;
	stream << number;
	return stream.str();
}


int main_Erdos_Numbers() 
{
	string tmp;
	getline(cin, tmp); 
	unsigned int numberOfScenarios = atoi(tmp.c_str());

	for(unsigned int i = 0; i < numberOfScenarios; i++)
	{
		unsigned int p;
		cin >> p;
		unsigned int n;
		cin >> n;
		getline(cin, tmp);

		vector<Book> books = readBooks(p);
		vector<string> authors = readAuthors(n);

		map<string, Author*> nameToAuthor;
		generateAuthorGraph(nameToAuthor, books);

		if(nameToAuthor.find(ERDOS) != nameToAuthor.end())
		{
			Author* erdos = nameToAuthor[ERDOS];
			erdos->distance = 0;
		}
		
		vector<Author*> sortedAuthors;

		for(map<string, Author*>::iterator it = nameToAuthor.begin(); it != nameToAuthor.end(); it++)
		{
			sortedAuthors.push_back(it->second);
		}	

		sort(sortedAuthors.begin(), sortedAuthors.end(), greaterThanPredicate);
		while(sortedAuthors.empty() == false)
		{
			Author* author = sortedAuthors.back();
			sortedAuthors.pop_back();

			for(set<Author*>::iterator it = author->coAuthors.begin(); it != author->coAuthors.end(); it++)
			{
				if((*it)->distance - 1 > author->distance)
				{
					(*it)->distance = author->distance + 1;
				}
			}

			sort(sortedAuthors.begin(), sortedAuthors.end(), greaterThanPredicate);
		}

		cout << SCENARIO;
		cout << i + 1 << endl;

		for(unsigned int j = 0; j < authors.size(); j++)
		{
			cout << authors[j] + " ";
			if(nameToAuthor.find(authors[j]) != nameToAuthor.end())
			{
				cout << erdosNumber(nameToAuthor[authors[j]]->distance) << endl;
			}
			else
			{
				cout << erdosNumber(UINT_MAX) << endl;
			}
		}

	}

	return 0;
}