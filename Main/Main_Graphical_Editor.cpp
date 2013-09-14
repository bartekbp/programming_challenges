#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;


class stopIterationException : exception
{

};

class image
{
	int x;
	int y;
	char** data;
public:
	image(int x, int y) { };
	void clear();
	bool isInBounds(int x, int y) { };
	void setColor(int x, int y, char color) { };
	~image() { };
};

class command 
{
public:
	virtual bool isInvokeable(string& line, image** img) const =0;
	virtual void invoke(string& line, image** img) =0;
};


class exitCommand : public command
{
public:
	bool isInvokeable(string& line, image** img) const { return line == "X"; }
	void invoke(string& line, image** img) { throw stopIterationException(); }
};


// TODO -- finish
int main_Graphical_Editor() {
	string line;
	vector<command*> commands;

	commands.push_back(new exitCommand);
	
	getline(cin, line);
	image* img = NULL;
	
	try 
	{
		while (!cin.eof()) 
		{
			for(vector<command*>::iterator it = commands.begin(); it < commands.end(); it++)
			{
				if((*it)->isInvokeable(line, &img))
				{
					(*it)->invoke(line, &img);
					break;
				}
			}

			line.clear();
		}
	}
	catch(stopIterationException)
	{
		// pass
	}

	while(!commands.empty())
	{
		delete commands.back();
		commands.pop_back();
	}

	if(img != NULL)
	{
		delete img;
		img = NULL;
	}

	return 0;
}