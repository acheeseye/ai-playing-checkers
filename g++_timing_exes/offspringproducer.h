#ifndef _INCLUDED_OFFSPRINGPRODUCER_H_
#define _INCLUDED_OFFSPRINGPRODUCER_H_

#include "NeuralNetwork_PERF.h" // For declared global values

#include <string>
#include <vector>
#include <cmath>

const int GLOBAL_KING_START = 0;
const int GLOBAL_WEIGHT_START = 1;
const int GLOBAL_WEIGHT_END = 1691 + 32; // one past so it uses < rather than <=
const int GLOBAL_SIGMA_START = 1691 + 32;
const int GLOBAL_SIGMA_END = 3381 + 32 + 32; // one past so it uses < rather than <=

const double GLOBAL_SIGMA_VALUE = 0.05;
const int GLOBAL_MAX_POPULATION_PER_GEN = 30;
const double GLOBAL_TAU = (1 / std::sqrt(2 * std::sqrt(GLOBAL_WC)));
const std::string GLOBAL_NAMING_FILE = "ai-playing-checkers\\nn_topologies\\naming_status.txt";
const std::string GLOBAL_OFFSPRING_PROOF = "ai-playing-checkers\\nn_topologies\\offsp_proof.txt";

const int GLOBAL_OPPO_COUNT = 5;


// CLASS OffspringProducer
// PURPOSE:
// Records the parent topology and produces an offspring
// Declutters NeuralNetwork_PERF to maximize performance
// For some absolutely wicked reason, array [] operation
// on the same index returns DIFFERENT values at various
// times (see below)

//NeuralNetwork_PERF brunette26(dummy_input);
//double * top_holder;
//vector<double> safe_container;
//top_holder = brunette26.get_topology();
//cout << "in main: " << top_holder[1741] << endl;
//for (auto i = 0; i < GLOBAL_TOPOLOGY_SIZE; ++i){	
//	if (i == 1741) {
//		cout << "in for loop: " << top_holder[1741] << endl;
//	}
//}

// this code prints top_holder[1741] as DIFFERENT VALUES
// even if no operations are done on it
// for this reason OffspringProducer will generate the topologies instead

class OffspringProducer {
public:
	OffspringProducer();
	std::vector<double> generate_random_topology();
	void set_topology(const std::string & parent_file);
	void produce_offspring(const std::string & parent_file);
	void record_current();

	void reset_counter();
	void advance_gen();
	void determine_survivors(const std::string & result_txt);
	int get_current_generation_id();
	std::vector<double> get_topology();

	void produce_next_generation();
private:
	std::vector<double> m_topology;
	std::vector<std::string> m_survived_parent;
	std::vector<std::string> m_offspring;
};

#endif // !_INCLUDED_OFFSPRINGPRODUCER_H_
