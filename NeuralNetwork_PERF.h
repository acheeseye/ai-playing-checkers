#ifndef _INCLUDED_NEURALNETWORK_PERF_H_
#define _INCLUDED_NEURALNETWORK_PERF_H_

#include <vector>
#include <tuple>

//NC for node count
//WC for weight count
//SC for sigma count
const int GLOBAL_LAYER_0_NC = 32;
const int GLOBAL_LAYER_1_NC = 40;
const int GLOBAL_LAYER_2_NC = 10;
const int GLOBAL_LAYER_3_NC = 1;
const int GLOBAL_NC = GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + GLOBAL_LAYER_2_NC + GLOBAL_LAYER_3_NC;
const int GLOBAL_SC = GLOBAL_NC - GLOBAL_LAYER_0_NC;
const int GLOBAL_WC = 
GLOBAL_LAYER_0_NC * GLOBAL_LAYER_1_NC +
GLOBAL_LAYER_1_NC * GLOBAL_LAYER_2_NC +
GLOBAL_LAYER_2_NC * GLOBAL_LAYER_3_NC;
const int GLOBAL_TOPOLOGY_SIZE = 1 + GLOBAL_WC + GLOBAL_SC;

class NeuralNetwork_PERF {
public:
	NeuralNetwork_PERF(const std::vector<double> & input, const std::vector<double> & topology);
	void calculate();
	void apply_sigma(double & input_sum);
private:
	double m_nodes[GLOBAL_NC];
	double m_sigma[GLOBAL_SC];
	double m_weights[GLOBAL_WC];
	double m_king_val;
	int m_sigma_iter;
	int m_weight_iter;
};

#endif