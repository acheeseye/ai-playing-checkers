#include "offspringproducer.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
using std::to_string;
using std::getline;
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
#include <algorithm>
using std::sort;
#include <utility>
using std::pair;
using std::make_pair;


//--No-throw
OffspringProducer::OffspringProducer()
{
	m_topology.resize(GLOBAL_TOPOLOGY_SIZE);
	m_survived_parent.resize(GLOBAL_MAX_POPULATION_PER_GEN / 2);
}

//--No-throw
// generates random topology with given initials
// this sets current topology to random
// this returns a topology as ease to be passed to NeuralNetwork_PERF
// * this should not be used beyond generation for zeroth generation
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

//--Basic guarantee
// records current topology (may be parent or offspring)
// checks if GENX directory exists and creates it if it doesn't
// advances naming_status.txt (population_id++)
// advance_gen must be called before if recording for next generation
// newly recorded topologies will overwrite old ones
// delimited by 999999, 888888, and 777777
void OffspringProducer::record_current()
{
	struct stat info;
	ifstream fin;
	ofstream fout;
	int generation;
	int id;

	fin.open(GLOBAL_NAMING_FILE, ifstream::in);
	if (!fin.is_open())
	{
		cout << "cannot open file in OffspringProducer::record" << endl;
		return;
	}
	fin >> generation >> id;
	fin.close();

	string gen_str = to_string(generation);
	string dir_name = "ai-playing-checkers\\nn_topologies\\GEN" + gen_str;
	string id_str = to_string(id);
	string out_filename = dir_name + "\\nn" + id_str + "_brunette26_topology.txt";
	string games_played_dir = dir_name;
	games_played_dir += "\\games_played_" + gen_str;

	const char * dir_name_wrap = dir_name.c_str();
	const char * games_played_dir_wrap = games_played_dir.c_str();

	stat(dir_name_wrap, &info);

	// NOTE: _mkdir returns a NON-ZERO if it is successful, thus if 0 (==false), unsuccessful
	// info.st_mode & S_IFDIR == true if directory exists
	if (_mkdir(dir_name_wrap) && !(info.st_mode & S_IFDIR)) {
		cout << "cannot create directory \"" << dir_name_wrap << "\" in OffspringProducer::record" << endl;
		return;
	}

	stat(games_played_dir_wrap, &info);

	if (_mkdir(games_played_dir_wrap) && !(info.st_mode & S_IFDIR)) {
		cout << "cannot create directory \"" << games_played_dir_wrap << "\" in OffspringProducer::record" << endl;
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
	for (auto i = GLOBAL_WEIGHT_START; i < GLOBAL_SIGMA_START; ++i) fout << m_topology[i] << '\n';
	fout << "888888\n";
	for (auto i = GLOBAL_SIGMA_START; i < GLOBAL_SIGMA_START + GLOBAL_SC; ++i) fout << m_topology[i] << '\n';
	fout << "777777";
	fout.close();

	fout.open(GLOBAL_NAMING_FILE, ofstream::out | ofstream::trunc);
	fout << generation << " " << id + 1;
	fout.close();
}

// sets current topology to offspring
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
		for (auto i = GLOBAL_SIGMA_START; i < GLOBAL_SIGMA_END; ++i)
		{
			m_topology[i] *= exp(GLOBAL_TAU*distrubution(e1));
		}
	}

	{	// weight evolve
		int sigma_iter = GLOBAL_SIGMA_START;
		std::normal_distribution<double> distrubution(0, 1);
		for (auto i = GLOBAL_WEIGHT_START; i < GLOBAL_WEIGHT_END; ++i)
		{
			m_topology[i] += m_topology[sigma_iter++] * distrubution(e1);
		}
	}
}

// hard resets the naming_status.txt to 0, 0
// * this should not be used beyond testing for zeroth generation
void OffspringProducer::reset_counter()
{
	string pathname = "ai-playing-checkers\\nn_topologies\\naming_status.txt";
	ofstream fout;
	fout.open(pathname, ofstream::out | ofstream::trunc);
	if(!fout.is_open())
	{
		cout << "naming_status.txt was not opened" << endl;
		return;
	}
	fout << "0 0";
	fout.close();
}

// generation++ & population_id = 0
void OffspringProducer::advance_gen()
{
	ifstream fin;
	ofstream fout;
	int generation;
	int id;

	fin.open(GLOBAL_NAMING_FILE, ifstream::in);
	if (!fin.is_open())
	{
		cout << "naming_status.txt was not opened" << endl;
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

// responsive to delimiters (777777, 888888, 999999)
// internal function called by produce_offspring
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

// stores survivors in m_survived_parents as a vector of network IDs
void OffspringProducer::determine_survivors(const std::string & result_txt)
{
	ifstream fin;
	vector< pair<int, int> > all_scores;

	fin.open(result_txt, ifstream::in);
	if(!fin.is_open())
	{
		cout << "result_txt was not opened in OffspringProducer::determine_survivors" << endl;
		return;
	}

	for(auto i = 0; i < GLOBAL_MAX_POPULATION_PER_GEN; ++i)
	{
		int network_score = 0;
		int ibuf;
		for(auto to_ignore = 0; to_ignore < 1 + GLOBAL_OPPO_COUNT; ++to_ignore)
		{
			fin >> ibuf;
			fin.ignore();
		}
		for(auto match_result = 0; match_result < GLOBAL_OPPO_COUNT; ++match_result)
		{
			fin >> ibuf;
			if(ibuf == 0) network_score += 0;
			else if (ibuf == 1) network_score += 1;
			else if (ibuf == 2) network_score -= 2;
			else 
			{
				cout << "invalid score read in OffspringProducer::determine_survivors" << endl;
				return;
			}
		}
		all_scores.push_back( make_pair(network_score, i) );
	}
	fin.close();

	sort(all_scores.begin(), all_scores.end(), 
		// lambda for sorting in descending order
		[] (const pair<int, int> & i, const pair<int, int> & j)
		{ return ( i.first > j.first ); }
		);

	// for verification purposes
	cout << "score, ID" << endl;
	for (auto n : all_scores)
	{
		cout << n.first << ", " << n.second << endl;
	}

	int gen = get_current_generation_id();

	for(auto i = 0; i < GLOBAL_MAX_POPULATION_PER_GEN / 2; ++i)
	{
		string parent_topo_location = 
			"ai-playing-checkers\\nn_topologies\\GEN" + 
			to_string(gen) + 
			"\\nn" + 
			to_string(all_scores[i].second) + "_brunette26_topology.txt";
		
		m_survived_parent[i] = parent_topo_location;
	}
}

// returns -1 if naming_status.txt was not opened
int OffspringProducer::get_current_generation_id()
{
	ifstream fin;
	fin.open(GLOBAL_NAMING_FILE, ifstream::in);
	if(!fin.is_open())
	{
		cout << "naming_status.txt not opened" << endl;
		return -1;
	}
	int gen;
	fin >> gen;
	fin.close();
	return gen;
}

void OffspringProducer::produce_next_generation()
{
	advance_gen();
	int gen = get_current_generation_id();
	for(auto i = 0; i < GLOBAL_MAX_POPULATION_PER_GEN / 2; ++i)
	{
		// record parent
		set_topology(m_survived_parent[i]);
		record_current();

		// produce offspring (not recorded yet)
		produce_offspring(m_survived_parent[i]);
		record_current();
	}
}
