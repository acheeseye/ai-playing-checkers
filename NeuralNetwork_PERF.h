#ifndef _INCLUDED_NEURALNETWORK_PERF_H_
#define _INCLUDED_NEURALNETWORK_PERF_H_

#include <vector>

//NC for node count
//WC for weight count
//SC for sigma count
const int GLOBAL_LAYER_0_NC = 32;
const int GLOBAL_LAYER_1_NC = 40;
const int GLOBAL_LAYER_2_NC = 10;
const int GLOBAL_LAYER_3_NC = 1;
const int GLOBAL_NC = GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + GLOBAL_LAYER_2_NC + GLOBAL_LAYER_3_NC;
const int GLOBAL_WC = 
GLOBAL_LAYER_0_NC * GLOBAL_LAYER_1_NC +
GLOBAL_LAYER_1_NC * GLOBAL_LAYER_2_NC +
GLOBAL_LAYER_2_NC * GLOBAL_LAYER_3_NC +
GLOBAL_LAYER_0_NC;
const int GLOBAL_SC = GLOBAL_WC;
const int GLOBAL_TOPOLOGY_SIZE = 1 + GLOBAL_WC + GLOBAL_SC;

class NeuralNetwork_PERF {
public:
	NeuralNetwork_PERF(int player);
	void set_input_layer(const std::vector<int> & input);
	void set_topology(const std::vector<double> & topology);
	void calculate();
	double apply_sigma(double input_sum);
	double get_result();
	int get_player_modification() const;
private:
	double m_nodes[GLOBAL_NC];
	double m_weights[GLOBAL_WC];
	double m_king_val;
	int m_weight_iter;
};

#endif