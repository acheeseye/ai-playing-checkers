#include "NeuralNetwork.h"
#include "board.h"

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
#include <random>
using std::mt19937;


NeuralNetwork::NeuralNetwork(const std::vector<int> & layer_and_node_count, int player, double king_val):
	m_player(player),
	m_layer_count(layer_and_node_count.size()),
	m_king_value(king_val)
{
	for (auto i = 0; i < m_layer_count; ++i)
	{
		m_all_layers_node_count.push_back(layer_and_node_count[i]);
	}
	init_weights_and_sigmoid();
}

void NeuralNetwork::init_weights_and_sigmoid()
{
	double sigmoid = 0.05;
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(-1, 1);
	int weight_count = 0;
	for (auto i = 0; i < m_layer_count - 1; ++i)
	{
		int weights_between_layers = m_all_layers_node_count[i] * m_all_layers_node_count[i + 1];
		weight_count += weights_between_layers;
	}
	for (auto i = 0; i < weight_count; ++i)
	{
		m_all_weights.push_back(uniform_dist(e1));
		m_all_sigmoid.push_back(sigmoid);
	}
}

void NeuralNetwork::read_board_input_from(const std::string & file_name)
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
		//return 0;
	}
	cout << "file open success" << endl << endl;

	vector<string> board_input;
	vector<vector<double>> board_record;

	while (getline(in_file, str))
	{
		board_input.push_back(str);
	}

	for (auto i = 0; i < board_input.size(); ++i)
	{
		stringstream ss(board_input[i]);
		vector<double> move_record;
		char token;

		while (ss >> token)
		{
			if (token == ' ')
			{
				ss.ignore();
			}
			else if (token == '-')
			{
				if (ss.peek() == '1') move_record.push_back(-1.0 * multiplier);
				else if (ss.peek() == 'k') move_record.push_back(m_king_value * multiplier * -1.0);
				ss.ignore();
			}
			else if (token == '0')
			{
				move_record.push_back(0);
			}
			else if (token == '1')
			{
				move_record.push_back(1 * multiplier);
			}
			else if (token == 'k')
			{
				move_record.push_back(m_king_value * multiplier);
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
	}

	in_file.close();
}

void NeuralNetwork::set_first_layer_input(const std::vector<double>& input)
{

}
