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


// No-throw
OffspringProducer::OffspringProducer()
{
	m_parent_topology.resize(GLOBAL_TOPOLOGY_SIZE);
}

std::vector<double> OffspringProducer::generate_topology()
{
	int topo_iter = 0;
	std::random_device r;
	std::default_random_engine e1(r());
	{
		std::uniform_real_distribution<double> uniform_dist(1, 3);
		m_parent_topology[topo_iter] = uniform_dist(e1);
		topo_iter++;
	}
	{
		std::uniform_real_distribution<double> uniform_dist(-0.2, 0.2);
		for (auto i = 0; i < GLOBAL_WC; ++i)
		{
			m_parent_topology[topo_iter] = uniform_dist(e1);
			topo_iter++;
		}
	}

	for (auto i = 0; i < GLOBAL_SC; ++i)
	{
		m_parent_topology[topo_iter] = 5;
		topo_iter++;
	}
	return m_parent_topology;
}

// Basic guarantee
void OffspringProducer::record()
{
	struct stat info;
	ifstream fin;
	ofstream fout;
	string naming_file = "ai-playing-checkers\\nn_topologies\\naming_status.txt";
	int generation;
	int id;

	fin.open(naming_file, ifstream::in);
	if (!fin.is_open())
	{
		throw std::exception("OPEING \"naming_status.txt\" FAILED");
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
	if (_mkdir(dir_name_wrap) && !(info.st_mode & S_IFDIR)) throw std::exception("DIRECTORY CREATION FAILED");
	if (id >= 30) throw std::exception("MAXIMUM NERUAL NETWORK COUNT REACHED FOR CURRENT GENERATION");

	fout.open(out_filename, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) throw std::exception("OPENING TOPOLOGY FILE TO WRITE FAILED");
	fout << m_parent_topology[0] << " 9999 ";
	for (auto i = 1; i < 1 + GLOBAL_WC; ++i) fout << m_parent_topology[i] << ' ';
	fout << "8888 ";
	for (auto i = 1 + GLOBAL_WC; i < 1 + GLOBAL_WC + GLOBAL_SC; ++i) fout << m_parent_topology[i] << ' ';
	fout.close();

	// if naming_file is not openable, function will have exited by this point 
	// (don't need to check if fout can open naming_file)
	fout.open(naming_file, ofstream::out | ofstream::trunc);
	fout << generation << " " << id + 1;
	fout.close();
}

void OffspringProducer::produce()
{
}

void OffspringProducer::reset_counter()
{
	string pathname = "ai-playing-checkers\\nn_topologies\\naming_status.txt";
	ofstream fout;
	fout.open(pathname, ofstream::out | ofstream::trunc);
	fout << "0 0";
	fout.close();
}
