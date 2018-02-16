#include "NeuralNetwork.h"
#include "board.h"
// For enumerated values

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <vector>
using std::vector;

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

double NeuralNetwork::get_final_output()
{
	return m_all_layers[m_max_layer_count-1][0].get_output();
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
	// Board values are stored with _RED_ as enemy (they are negative values)
	double multiplier = 1.0;
	if (m_player == _RED_)
	{
		multiplier = -1.0;
	}
	ifstream in_file;
	string str;
	in_file.open(file_name);

	if (!in_file) 
	{
		cout << "CANNOT OPEN FILE WITH FUNCTION NeuralNetwork::board_evaluation" << endl;
		return 0;
	}
	cout << "file open success" << endl << endl;

	vector<double> NN_first_layer_input;

<<<<<<< HEAD
	while (!in_file.eof())
||||||| merged common ancestors
	while (in_file >> s)
	{
	}

	for (auto i = 0; i < board_input.size(); ++i)
=======
	vector<vector<int>> board_record;

	while (getline(in_file, str))
	{
		board_input.push_back(str);
	}

	for (auto i = 0; i < board_input.size(); ++i)
>>>>>>> 93f4875fdea0911e1cc9502e2c8475388d7e89f6
	{
<<<<<<< HEAD
		char c_iter;
		std::getline(in_file, s);
		if (s == "") break;
		for (auto i = 0; i < s.size(); ++i)
		{
			c_iter = s[i];
			if (c_iter == '0') NN_first_layer_input.push_back(0);
			else if (c_iter == '1') NN_first_layer_input.push_back(1 * multiplier);
			else if (c_iter == 'k') NN_first_layer_input.push_back(m_own_king_value * multiplier);
			else if (c_iter == '-')
			{
				if (s[i + 1] == '1') NN_first_layer_input.push_back(-1 * multiplier);
				else if (s[i + i] == 'k') NN_first_layer_input.push_back(m_enemy_king_value * multiplier);
				++i;
			}
		}
		propagate_NN(NN_first_layer_input);
		cout << "BOARDEVAL: " << get_final_output() << endl;
		NN_first_layer_input.clear();
||||||| merged common ancestors
=======
		stringstream ss(board_input[i]);
		vector<int> move_record;
		int token;

		while (ss >> token)
		{
			move_record.push_back(token);

			if (ss.peek() == ',')
			{
				ss.ignore();
			}
		}
		board_record.push_back(move_record);
	}

	for (int j = 0; j < board_record.size(); ++j) // this loop just here to show file was parsed correctly
	{
		for (int k = 0; k < 32; ++k)
		{
			cout << board_record[j][k] << " ";
		}
		cout << endl;
>>>>>>> 93f4875fdea0911e1cc9502e2c8475388d7e89f6
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

void NeuralNetwork::set_first_layer_inputs(const vector<double> & first_layer_inputs)
{
	int layer_id = 0;
	if (first_layer_inputs.size() != m_all_layers[layer_id].size()) throw std::exception("Attempting to input incorrect count of values to layer 0 in NeuralNetwork::set_first_layer_inputs");
	for (auto i = 0; i < m_all_layers[layer_id].size(); ++i)
	{
		m_all_layers[layer_id][i].set_input(first_layer_inputs[i]);
	}
}

void NeuralNetwork::print_node_input(int layer_id)
{
	cout << m_all_layers[layer_id][0].get_input_sum() << " ";
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
			add_this_node.set_sigmoid_activation(1);
			m_all_layers[layer_id][node_id] = add_this_node;
		}
	}
}

void NeuralNetwork::propagate_NN(const vector<double> & first_layer_input)
{
	for (auto layer_id = 0; layer_id < m_max_layer_count; ++layer_id)
	{
		print_node_input(layer_id);
		for (auto node_id = 0; node_id < m_all_layers[layer_id].size(); ++node_id)
		{
			vector<double> previous_layer_input;
			if (layer_id == 0)
			{
				//connector outputs are set
				m_all_layers[layer_id][node_id].calculate_and_set_output(first_layer_input);
			}
			else
			{
				//connector outputs are set
				m_all_layers[layer_id][node_id].calculate_and_set_output(previous_layer_input);
			}
			//prepping for next node
			previous_layer_input = m_all_layers[layer_id][node_id].get_all_connector_output();

			for (auto n : previous_layer_input)
			{
				//cout << n << " ";
			}
		}
	}
}
