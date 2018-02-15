#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int layers, int player) :
	m_max_layer_count(layers),
	m_player(player),
	m_own_man_value(1.0),
	m_enemy_man_value(-1.0)
{
	m_all_layers.resize(m_max_layer_count);
}

int NeuralNetwork::get_max_layer_count()
{
	return m_max_layer_count;
}

int NeuralNetwork::get_node_count(int layer_id)
{
	return m_all_layers[layer_id].size();
}

void NeuralNetwork::set_node_count(int layer_id, int node_count)
{
	if (layer_id >= m_max_layer_count) return;
	for (auto i = 0; i < node_count; ++i)
	{
		NNNodes node(layer_id);
		m_all_layers[layer_id].push_back(node);
	}
}

void NeuralNetwork::set_king_value(float king_value)
{
	m_own_king_value = king_value;
	m_enemy_king_value = -king_value;
}
