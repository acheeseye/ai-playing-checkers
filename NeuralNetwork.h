#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include <vector>

class NeuralNetwork
{
	typedef std::vector<double> layer_type;
public:
	NeuralNetwork(int layers, int player);
	int get_max_layer_count();
	int get_node_count(int layer_id);

	std::vector<layer_type> get_all_layers();
	double get_node(int layer_id, int node_id);

	double board_evaluation(std::string & file_name);

	void set_node_count(int layer_id, int node_count);
	void set_king_value(double king_value);

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