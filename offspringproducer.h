#ifndef _INCLUDED_OFFSPRINGPRODUCER_H_
#define _INCLUDED_OFFSPRINGPRODUCER_H_


#include "NeuralNetwork_PERF.h" // For declared global values

#include <string>
#include <vector>

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
// even if no operations are done on it.
// for this reason OffspringProducer will generate the topologies instead

class OffspringProducer {
public:
	OffspringProducer();
	std::vector<double> generate_topology();
	void record();
	void produce();
	void reset_counter();
private:
	std::vector<double> m_parent_topology;
};

#endif // !_INCLUDED_OFFSPRINGPRODUCER_H_
