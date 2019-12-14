#include "FolderHandler.h"

void Combine(ifstream& input, string input_name, ofstream& output)
{
	output << "\v" << input_name << "\n";

	char c;

	while (input.get(c))
	{
		output << c;
	}
}

void Separate(ifstream& input)
{
	string name;

	char c;

	ofstream output;

	while (input.get(c))
	{
		if (c == '\v')
		{
			output.close();
			getline(input, name);
			output.open(name);
		}
		else output << c;
	}
	
}
