#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include "nnnodes.h"

#include <vector>

class NeuralNetwork
{
	typedef std::vector<NNNodes> layer_type;
public:
	NeuralNetwork(int layers, int player);

	// Getters
	int get_max_layer_count();
	int get_node_count(int layer_id);
	double get_final_output();
	std::vector<layer_type> get_all_layers();
	NNNodes get_node(int layer_id, int node_id);

	double board_evaluation(std::string & file_name);

	// Setters
	void set_node_count(int layer_id, int node_count);
	void set_king_value(double king_value);
	void set_first_layer_inputs(const std::vector<double> & first_layer_inputs);
	void print_node_input(int layer_id); //samples 0th node

	// Initializers
	void init_nodes();
	void propagate_NN(const std::vector<double> & first_layer_input); // this is likely the most time consuming part of the NN

private:
	int m_max_layer_count;
	int m_player;
	double m_own_man_value;
	double m_own_king_value;
	double m_enemy_man_value;
	double m_enemy_king_value;
	std::vector<layer_type> m_all_layers;
};

#endif // !_INCLUDED_NEURALNETWORK_H_
