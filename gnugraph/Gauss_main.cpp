#include "GnuGraph.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <random>
using std::normal_distribution;
using std::random_device;
using std::mt19937;


int main()
{
	GnuGraph graph("C:/Program Files/gnuplot/bin/gnuplot.exe"); // provide path to executable

	vector<double> g_vals, width;
	map<double, double> vals;

	random_device rnd;
	mt19937 e2(rnd());

	normal_distribution<> gauss(0, 1);

	for (int i = 0; i < 1000; ++i)
	{
		++vals[round(gauss(e2))];
	}

	for (auto & p : vals)
	{
		cout << p.first << ' ' << string(p.second / 200, '*') << '\n';
	
		g_vals.push_back(p.second);
		width.push_back(p.first);
	}

	const string output = graph.plot(width, g_vals, "gauss check");
	cout << output << '\n'; // print any errors to console


	cout << "press ENTER to quit" << endl;
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (cin.get() != '\n');

	return 0;
}