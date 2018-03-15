#include "offspringproducer.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
using std::to_string;
#include <iostream>
using std::cout;
using std::endl;
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
using std::vector;
#include <random>
#include <exception>
using std::exception;


// No-throw
OffspringProducer::OffspringProducer()
{
	m_topology.resize(GLOBAL_TOPOLOGY_SIZE);
	m_survived_parent.resize(GLOBAL_MAX_POPULATION_PER_GEN / 2);
}

// No-throw
std::vector<double> OffspringProducer::generate_random_topology()
{
	int topo_iter = 0;
	std::random_device r;
	std::default_random_engine e1(r());

	{	// setting king value
		std::uniform_real_distribution<double> uniform_dist(1, 3);
		m_topology[topo_iter] = uniform_dist(e1);
		topo_iter++;
	}

	{	// setting all weights
		std::uniform_real_distribution<double> uniform_dist(-0.2, 0.2);
		for (auto i = 0; i < GLOBAL_WC; ++i)
		{
			m_topology[topo_iter] = uniform_dist(e1);
			topo_iter++;
		}
	}
		// setting all sigma
	for (auto i = 0; i < GLOBAL_SC; ++i)
	{
		m_topology[topo_iter] = GLOBAL_SIGMA_VALUE;
		topo_iter++;
	}
	return m_topology;
}

// Basic guarantee
void OffspringProducer::record()
{
	struct stat info;
	ifstream fin;
	ofstream fout;
	int generation;
	int id;

	fin.open(GLOBAL_NAMING_FILE, ifstream::in);
	if (!fin.is_open())
	{
		//throw std::exception("OPENING \"naming_status.txt\" FAILED");
		cout << "cannot open file in OffspringProducer::record" << endl;
	}
	fin >> generation >> id;
	fin.close();

	string gen_str = to_string(generation);
	string dir_name = "ai-playing-checkers\\nn_topologies\\GEN" + gen_str;
	string id_str = to_string(id);
	string out_filename = dir_name + "\\nn" + id_str + "_brunette26_topology.txt";
	const char * dir_name_wrap = dir_name.c_str();
	stat(dir_name_wrap, &info);

	// NOTE: _mkdir returns a NON-ZERO if it is successful, thus if 0 (==false), unsuccessful
	// info.st_mode & S_IFDIR == true if directory exists
	if (_mkdir(dir_name_wrap) && !(info.st_mode & S_IFDIR)) {
		cout << "cannot create directory in OffspringProducer::record" << endl;
		return;
	}
	if (id >= GLOBAL_MAX_POPULATION_PER_GEN) {
		cout << "max population per generation reached in OffspringProducer::record" << endl;
		return;
	}

	fout.open(out_filename, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) {
		cout << "cannot open file in OffspringProducer::record (out_filename)" << endl;
		return;
	}

	fout << m_topology[0] << "\n999999\n";
	for (auto i = GLOBAL_WEIGHT_START; i < GLOBAL_SIGMA_START - 1; ++i) fout << m_topology[i] << '\n';
	fout << "888888\n";
	for (auto i = GLOBAL_SIGMA_START; i < GLOBAL_SIGMA_START + GLOBAL_SC; ++i) fout << m_topology[i] << '\n';
	fout << "777777";
	fout.close();

	fout.open(GLOBAL_NAMING_FILE, ofstream::out | ofstream::trunc);
	fout << generation << " " << id + 1;
	fout.close();
}

void OffspringProducer::produce_offspring(const std::string & parent_file)
{
	set_topology(parent_file);

	std::random_device r;
	std::default_random_engine e1(r());

	{	// king evolve
		std::uniform_real_distribution<double> uniform_dist(-0.1, 0.1);
		double uniform_king_change = uniform_dist(e1);
		m_topology[0] += uniform_king_change;
	}

	{	// sigma evolve for weight evolve
		std::normal_distribution<double> distrubution(0, 1);
		for (auto i = GLOBAL_SIGMA_START; i <= GLOBAL_SIGMA_END; ++i)
		{
			m_topology[i] *= exp(GLOBAL_TAU*distrubution(e1));
		}
	}

	{	// weight evolve
		int sigma_iter = GLOBAL_SIGMA_START;
		std::normal_distribution<double> distrubution(0, 1);
		for (auto i = GLOBAL_WEIGHT_START; i <= GLOBAL_WEIGHT_END; ++i)
		{
			m_topology[i] += m_topology[sigma_iter++] * distrubution(e1);
		}
	}
}

void OffspringProducer::reset_counter()
{
	string pathname = "ai-playing-checkers\\nn_topologies\\naming_status.txt";
	ofstream fout;
	fout.open(pathname, ofstream::out | ofstream::trunc);
	fout << "0 0";
	fout.close();
}

void OffspringProducer::advance_gen()
{
	ifstream fin;
	ofstream fout;
	int generation;
	int id;

	fin.open(GLOBAL_NAMING_FILE, ifstream::in);
	if (!fin.is_open())
	{
		cout << "naming_status.txt does not exist" << endl;
		return;
	}
	fin >> generation >> id;
	fin.close();

	id = 0;
	generation++;

	fout.open(GLOBAL_NAMING_FILE, ofstream::out | ofstream::trunc);
	fout << generation << " " << id;
	fout.close();
}

void OffspringProducer::set_topology(const std::string & parent_file)
{
	ifstream fin;
	fin.open(parent_file, ifstream::in);
	if (!fin.is_open()) 
	{
		cout << "parent file was not opened" << endl;
		return;
	}
	double input;
	int topo_iter = 0;
	while (true) {
		fin >> input;
		if (input == 999999 || input == 888888) continue;
		if (input == 777777) break;
		m_topology[topo_iter++] = input;
	}

	fin.close();
}
