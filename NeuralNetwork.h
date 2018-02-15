#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include "nnnodes.h"

#include <vector>
using std::vector;

class NeuralNetwork
{
	typedef vector<NNNodes> layer_type;
public:
	NeuralNetwork(int layers, int player);
	int get_max_layer_count();
	int get_node_count(int layer_id);
	void set_node_count(int layer_id, int node_count);
	void set_king_value(float king_value);

protected:
	int m_max_layer_count;
	int m_player;
	double m_own_man_value;
	double m_own_king_value;
	double m_enemy_man_value;
	double m_enemy_king_value;
	vector<layer_type> m_all_layers;
};

#endif // !_INCLUDED_NEURALNETWORK_H_
