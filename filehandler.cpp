#include "filehandler.h"
#include "ai-playing-checkers/NeuralNetwork_PERF.h"

#include <fstream>
#include <iostream>

void FileHandler::set_file(const std::string& filename)
{
	fin_m.open(filename, std::ifstream::in);
	if (!fin_m.is_open()) throw std::runtime_error("Topology " + filename + " not opened with FileHandler");

	weights_m.clear();
	sigmas_m.clear();
	weights_m.reserve(GLOBAL_TOPOLOGY_SIZE);
	sigmas_m.reserve(GLOBAL_TOPOLOGY_SIZE);

	double dbuf;

	fin_m >> dbuf;
	king_m = dbuf;

	while(true)
	{
		fin_m >> dbuf;
		if (dbuf == 999999) continue;
		if (dbuf == 888888) break;
		weights_m.push_back(dbuf);
	}

	while(true)
	{
		fin_m >> dbuf;
		if (dbuf == 777777) break;
		sigmas_m.push_back(dbuf);
	}

	fin_m.close();
}

std::vector<double> FileHandler::get_weights() const
{
	return weights_m;
}

std::vector<double> FileHandler::get_sigmas() const 
{
	return sigmas_m;
}

double FileHandler::get_king() const
{
	return king_m;
}
