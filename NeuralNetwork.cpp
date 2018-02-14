#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int layers):
	m_max_layers(layers)
{
	m_all_layers.resize(m_max_layers);
}

void NeuralNetwork::set_node_count(int layer_id, int node_count)
{
	if (layer_id >= m_max_layers) return;
	m_all_layers[layer_id].resize(node_count);
}
