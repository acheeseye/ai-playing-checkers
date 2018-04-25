#pragma once

#include <string>
#include <vector>
#include <fstream>

class FileHandler
{
public:
	FileHandler() = default;
	void set_file(const std::string & filename);

	std::vector<double> get_weights() const;
	std::vector<double> get_sigmas() const;
	double get_king() const;

private:
	std::ifstream fin_m;
	std::vector<double> weights_m;
	std::vector<double> sigmas_m;
	double king_m;
};

