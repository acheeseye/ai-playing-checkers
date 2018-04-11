#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;
using std::getline;

#include <vector>
using std::vector;

#include <regex>
using std::regex;
using std::regex_replace;


void replace_all(vector<string> & data, const string & old_str, const string & new_str)
{
	for (auto & datum : data)
	{
		datum = regex_replace(datum, regex(old_str), new_str);
	}
}


vector<string> process_in(const string & i_file)
{
	string line;
	vector<string> raw_data;

	ifstream the_txt(i_file);

	bool success = false;

	if (the_txt.is_open())
	{
		success = true;
		while (getline(the_txt, line))
		{
			raw_data.push_back(line);
		}
	}
	else
	{ cout << "UNABLE TO OPEN FILE: " << i_file << endl; }

	if (success)
	{
		raw_data.pop_back();

		replace_all(raw_data, "-1", "r");
		replace_all(raw_data, "-2", "R");
		replace_all(raw_data, "1", "b");
		replace_all(raw_data, "2", "B");
		replace_all(raw_data, "0", "_");
		replace_all(raw_data, " ", "");

		the_txt.close();
	}

	return raw_data;
}


void process_out(const string & i_file, const vector<string> & data)
{
	ofstream the_txt(i_file, ios::out | ios::trunc);

	if (the_txt.is_open())
	{
		for (auto & datum : data)
		{
			the_txt << datum << endl;
		}
	}
	else
	{
		cout << "UNABLE TO OPEN FILE: " << i_file << endl;
	}

	the_txt.close();
}


int main()
{
	string i_file = "0_20.txt";

	vector<string> game_data = process_in(i_file);

	for (auto & str : game_data)
	{
		cout << str << endl;
	}

	process_out(i_file, game_data);

	cout << endl << endl << "PRESS ENTER TO QUIT";
	while(cin.get() != '\n');
	return 0;
}