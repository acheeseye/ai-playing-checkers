#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include <vector>
#include <fstream>
#include <queue>
#include <string>

class NeuralNetwork
{
public:

	// Constructor
	NeuralNetwork(const std::vector<int> & layer_and_node_count);

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

private:

	std::string m_topology_file_destination;
	bool m_generate_file_status;

	int m_player;
	int m_layer_count;
	int m_current_layer_id;
	int m_weight_count;
	int m_weight_iter;

	double m_king_value;
	double m_king_value_min;
	double m_king_value_max;
	double m_weight_min;
	double m_weight_max;
	double m_sigma;
	double m_output;

	std::vector<int> m_all_layers_node_count;
	std::vector<double> m_all_weights;
	std::vector<double> m_all_sigma;
	std::vector<double> m_current_layer;
	std::vector<std::vector<double>> m_board_record;

	// Private internal functions
	double apply_sigma(double input_sum, int node_id);
	void default_set();
	void set_next_layer_input();
	void init_weights();
	void init_king();
	void init_sigma();
	void write_topology();
};

#endif // !_INCLUDED_NEURALNETWORK_H_