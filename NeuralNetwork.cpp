#include "NeuralNetwork.h"
#include "nnnodes.h";

#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
#include <vector>

typedef vector<NNNodes> layer_type;

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

vector<layer_type> NeuralNetwork::get_all_layers()
{
	return m_all_layers;
}

NNNodes NeuralNetwork::get_node(int layer_id, int node_id)
{
	return m_all_layers[layer_id][node_id];
}

double NeuralNetwork::board_evaluation(string & file_name)
{
	ifstream in_file;
	string s;
	in_file.open(file_name);
	if (!in_file) 
	{
		cout << "CANNOT OPEN FILE WITH FUNCTION NeuralNetwork::board_evaluation" << endl;
		return 0;
	}
	cout << "file open success" << endl;

	vector<string> board_input;

	while (in_file >> s)
	{
	}

	for (auto i = 0; i < board_input.size(); ++i)
	{
	}

	in_file.close();
}

void NeuralNetwork::set_node_count(int layer_id, int node_count)
{
	if (layer_id >= m_max_layer_count) return;
	m_all_layers[layer_id].resize(node_count);
}

void NeuralNetwork::set_king_value(double king_value)
{
	m_own_king_value = king_value;
	m_enemy_king_value = -king_value;
}

void NeuralNetwork::init_nodes()
{
	for (auto layer_id = 0; layer_id < m_max_layer_count; ++layer_id)
	{
		if (layer_id == m_max_layer_count - 1) return;
		int next_layer_node_count = m_all_layers[layer_id + 1].size();
		for (auto node_id = 0; node_id < m_all_layers[layer_id].size(); ++node_id)
		{
			NNNodes add_this_node(layer_id, next_layer_node_count);
			m_all_layers[layer_id][node_id] = add_this_node;
		}
	}
}
