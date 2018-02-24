#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include <vector>
#include <fstream>
#include <queue>
#include <string>

const int GLOBAL_WEIGHT_COUNT = 1690;
const int GLOBAL_SIGMA_COUNT = 51;
const int GLOBAL_LAYER_0_NODE_COUNT = 32;
const int GLOBAL_LAYER_1_NODE_COUNT = 40;
const int GLOBAL_LAYER_2_NODE_COUNT = 10;
const int GLOBAL_LAYER_3_NODE_COUNT = 1;
const int GLOBAL_MAX_LAYER_COUNT = 4;


class NeuralNetwork
{
public:

	// Constructor
	NeuralNetwork();

	// Mutator functions
	void set_player(int player);
	void set_king_value_range(double k_min, double k_max);
	void set_weight_range(double min, double max);
	void set_sigma(double sigma);
	void set_board_record_with(const std::string & file_name);
	void set_input_layer(int board_id);
	void set_generate_file(bool b);

	// Accessor functions
	double get_output();
	int get_board_count();
	int get_weight_count();

	// Initializer functions
	void init();
	void calculate_output();

	// Filename helper function
	friend std::string adjust_time(int unit);

private:

	std::string m_topology_file_destination;
	bool m_generate_file_status;

	int m_player;
	int m_layer_count;
	int m_current_layer_id;
	int m_weight_count;

	int m_weight_iter;
	int m_sigma_iter;

	double m_king_value;
	double m_king_value_min;
	double m_king_value_max;
	double m_weight_min;
	double m_weight_max;
	double m_sigma;
	double m_output;

	double m_all_weights[GLOBAL_WEIGHT_COUNT];
	double m_all_sigma[GLOBAL_SIGMA_COUNT];
	double m_layer_0[GLOBAL_LAYER_0_NODE_COUNT];
	double m_layer_1[GLOBAL_LAYER_1_NODE_COUNT];
	double m_layer_2[GLOBAL_LAYER_2_NODE_COUNT];
	double m_layer_3[GLOBAL_LAYER_3_NODE_COUNT];
	std::vector<std::vector<double>> m_board_record;

	// Private internal functions
	void apply_sigma(double & input_sum, const int node_id);
	void default_set();
	void set_next_layer_input();
	void init_weights();
	void init_king();
	void init_sigma();
	void write_topology();
};

#endif // !_INCLUDED_NEURALNETWORK_H_