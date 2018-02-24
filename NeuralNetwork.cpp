#include "NeuralNetwork.h"
#include "board.h"

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
using std::getline;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <sstream>
using std::stringstream;
#include <vector>
using std::vector;
using std::max_element;
#include <random>
using std::mt19937;
#include <queue>
using std::queue;
#include <time.h>
#include <chrono>

//NTR (non timing-related)
NeuralNetwork::NeuralNetwork() :
	m_layer_count(GLOBAL_LAYER_0_NODE_COUNT),
	m_current_layer_id(0),
	m_weight_count(GLOBAL_WEIGHT_COUNT)
{
	default_set();
}

//NTR
void NeuralNetwork::set_player(int player)
{
	m_player = player;
}

//NTR (maybe needs error checking for min > max, perhaps later)
void NeuralNetwork::set_king_value_range(double k_min, double k_max)
{
	m_king_value_min = k_min;
	m_king_value_max = k_max;
}

//NTR
void NeuralNetwork::set_weight_range(double min, double max)
{
	if (min > max)
	{
		double tmp = min;
		min = max;
		max = tmp;
	}
	m_weight_min = min;
	m_weight_max = max;
}

//NTR
void NeuralNetwork::set_sigma(double sigma)
{
	m_sigma = sigma;
}

//NTR
void NeuralNetwork::default_set()
{
	struct tm timeinfo;
	time_t now = time(0);
	localtime_s(&timeinfo, &now);

	string year = to_string(1900 + timeinfo.tm_year);
	string month = adjust_time(1 + timeinfo.tm_mon);
	string day = adjust_time(timeinfo.tm_mday);

	string hour = adjust_time(timeinfo.tm_hour);
	string minute = adjust_time(timeinfo.tm_min);
	string second = adjust_time(timeinfo.tm_sec);

	m_player = _RED_;
	m_king_value_min = 1.0;
	m_king_value_max = 3.0;
	m_weight_min = -0.2;
	m_weight_max = 0.2;
	m_sigma = GLOBAL_SIGMA_VALUE;
	m_generate_file_status = false;
	m_topology_file_destination = "ai-playing-checkers\\nn_topologies\\brunette26_topology_"
		+ year + month + day + '_' + hour + minute + second + ".txt";
}

//NTR
void NeuralNetwork::init()
{
	init_king();
	init_weights();
	init_sigma();
	if (m_generate_file_status == true) write_topology();
}

void NeuralNetwork::init_TESTING(const vector<double> & weights_TESTING)
{
	for (auto i = 0; i < 6; ++i)
	{
		m_all_sigma_TESTING[i] = GLOBAL_SIGMA_VALUE;
	}
	for (auto i = 0; i < T___GLOBAL_WEIGHT_COUNT; ++i)
	{
		m_all_weights_TESTING[i] = weights_TESTING[i];
	}
	m_layer_0_TESTING[0] = -1;
	m_layer_0_TESTING[1] = 0;
	m_layer_0_TESTING[2] = 0;
	m_layer_0_TESTING[3] = 1;
}

//NTR
void NeuralNetwork::init_weights()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(m_weight_min, m_weight_max);

	for (auto i = 0; i < m_weight_count; ++i)
	{
		m_all_weights[i] = uniform_dist(e1);
	}
}

//NTR
void NeuralNetwork::set_board_record_with(const std::string & file_name)
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
		//throw std::exception("File not opened in NeuralNetwork::set_board_record_with"); // causes a crash if file name is wrong
		cout << "*********************************************************" << endl;
		cout << "ERROR OPENING FILE: PROBABLY NOT READING GAME DATA" << endl;
		cout << "PLEASE CHECK IF THE FILE NAME IS CORRECT FOR YOUR VERSION" << endl;
		cout << "*********************************************************" << endl;
	}
	else
	{
		vector<string> board_tokens;

		while (getline(in_file, str))
		{
			board_tokens.push_back(str);
		}

		for (auto i = 0; i < board_tokens.size(); ++i)
		{
			stringstream ss(board_tokens[i]);
			vector<double> move_record;
			char token;

			while (ss >> token)
			{
				if (token == ' ') ss.ignore();
				else if (token == '-')
				{
					if (ss.peek() == '1') move_record.push_back(-1.0 * multiplier);
					else if (ss.peek() == 'k') move_record.push_back(m_king_value * multiplier * -1.0);
					ss.ignore();
				}
				else if (token == '0') move_record.push_back(0);
				else if (token == '1') move_record.push_back(1 * multiplier);
				else if (token == 'k') move_record.push_back(m_king_value * multiplier);
			}
			m_board_record.push_back(move_record);
		}

		for (int j = 0; j < m_board_record.size(); ++j) // this loop just here to show file was parsed correctly
		{
			for (int k = 0; k < 32; ++k)
			{
				//cout << board_record[j][k] << " ";
			}
			//cout << endl;
		}

		in_file.close();
	}
}

//TIMING low
void NeuralNetwork::set_input_layer(int board_id)
{
	for (auto i = 0; i < 32; ++i)
	{
		m_layer_0[i] = m_board_record[board_id][i];
	}
}

//NTR
void NeuralNetwork::set_generate_file(bool b)
{
	m_generate_file_status = b;
}

//TIMING medium - decreases speed by ~33%
void NeuralNetwork::apply_sigma(double & input_sum, const int node_id)
{
	input_sum = (2 / (1 + exp(-input_sum * m_all_sigma_TESTING[node_id])) - 1);

}

//TIMING high
//void NeuralNetwork::set_next_layer_input()
//{
//	auto begin = std::chrono::high_resolution_clock::now();
//
//	double input_sum = 0.0;
//	int current_layer_node_count = m_all_layers_node_count[m_current_layer_id];
//	int next_layer_node_count = m_all_layers_node_count[m_current_layer_id + 1];
//	vector<double> next_layer_input_buffer;
//	
//	if (m_current_layer_id >= m_layer_count) 
//		throw std::exception("Out of range index received for NeuralNetwork::set_next_layer_input");
//	for (auto next_layer_node_id = 0; next_layer_node_id < next_layer_node_count; ++next_layer_node_id)
//	{
//		for (auto node_id = 0; node_id < current_layer_node_count; ++node_id)
//		{
//			double next_layer_single_node_input = m_current_layer[node_id] * m_all_weights[m_weight_iter];
//			m_weight_iter++;
//			input_sum += next_layer_single_node_input;
//		}
//		
//		//double current_node_output = input_sum;
//		double current_node_output = apply_sigma(input_sum, next_layer_node_id);
//		//if (node_output > 1.0 || node_output < -1.0) throw std::exception("Input sum exceeds expected sigmoid output");
//		next_layer_input_buffer.push_back(current_node_output);
//	}
//
//	m_current_layer_id++;
//	m_current_layer.resize(next_layer_node_count);
//	m_current_layer = next_layer_input_buffer;
//
//	auto end = std::chrono::high_resolution_clock::now();
//	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / (double)1000000000 << " sec"<< endl;
//
//}

//NTR
void NeuralNetwork::init_king()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(m_king_value_min, m_king_value_max);
	m_king_value = uniform_dist(e1);
}

//NTR
void NeuralNetwork::init_sigma()
{
	for (auto i = 0; i < GLOBAL_SIGMA_COUNT; ++i) 
	{
		m_all_sigma[i] = m_sigma;
	}
}

//NTR
void NeuralNetwork::write_topology()
{
	ofstream output_file;
	output_file.open(m_topology_file_destination, ofstream::out | ofstream::app);
	if (!output_file.is_open()) throw std::exception("NeuralNetwork::write_topology cannot open output file");
	output_file << m_king_value << '\n';
	for (auto weight_id = 0; weight_id < m_weight_count; ++weight_id)
	{
		if (weight_id < m_weight_count - 1)
		{
			output_file << m_all_weights[weight_id] << " " << m_all_sigma[weight_id] << "\n";
		}
		else
		{
			output_file << m_all_weights[weight_id] << " " << m_all_sigma[weight_id]; // no trailing newline
		}
	}
	output_file.close();
}

//TIMING HIGH
void NeuralNetwork::calculate_output()
{
	m_weight_iter = 0; //restart at 0th weight when calling set_next_layer_input
	m_sigma_iter = 0;

	for (auto layer_1_node_id = 0; layer_1_node_id < GLOBAL_LAYER_1_NODE_COUNT; ++layer_1_node_id)
	{
		double layer_1_node_sum = 0.0;
		for (auto layer_0_node_id = 0; layer_0_node_id < GLOBAL_LAYER_0_NODE_COUNT; ++layer_0_node_id)
		{
			layer_1_node_sum += m_layer_0[layer_0_node_id] * m_all_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_1_node_sum, m_sigma_iter);
		m_layer_1[layer_1_node_id] = layer_1_node_sum;
		m_sigma_iter++;
	}

	for (auto layer_2_node_id = 0; layer_2_node_id < GLOBAL_LAYER_2_NODE_COUNT; ++layer_2_node_id)
	{
		double layer_2_node_sum = 0.0;
		for (auto layer_1_node_id = 0; layer_1_node_id < GLOBAL_LAYER_1_NODE_COUNT; ++layer_1_node_id)
		{
			layer_2_node_sum += m_layer_1[layer_1_node_id] * m_all_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_2_node_sum, m_sigma_iter);
		m_layer_2[layer_2_node_id] = layer_2_node_sum;
		m_sigma_iter++;
	}

	for (auto layer_3_node_id = 0; layer_3_node_id < GLOBAL_LAYER_3_NODE_COUNT; ++layer_3_node_id)
	{
		double layer_3_node_sum = 0.0;
		for (auto layer_2_node_id = 0; layer_2_node_id < GLOBAL_LAYER_2_NODE_COUNT; ++layer_2_node_id)
		{
			layer_3_node_sum += m_layer_2[layer_2_node_id] * m_all_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_3_node_sum, m_sigma_iter);
		m_layer_3[layer_3_node_id] = layer_3_node_sum;
		m_sigma_iter++;
	}

	m_output = m_layer_3[0];
}

void NeuralNetwork::calculate_output_TESTING()
{
	m_weight_iter = 0; //restart at 0th weight when calling set_next_layer_input
	m_sigma_iter = 0;
	m_layer_0[0] = -1.0;
	m_layer_0[1] = 0.0;
	m_layer_0[2] = 0.0;
	m_layer_0[3] = 1.0;

	for (auto layer_1_node_id = 0; layer_1_node_id < T___GLOBAL_LAYER_1_NODE_COUNT; ++layer_1_node_id)
	{
		double layer_1_node_sum = 0.0;
		for (auto layer_0_node_id = 0; layer_0_node_id < T___GLOBAL_LAYER_0_NODE_COUNT; ++layer_0_node_id)
		{
			layer_1_node_sum += m_layer_0[layer_0_node_id] * m_all_weights_TESTING[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_1_node_sum, m_sigma_iter);
		m_layer_1[layer_1_node_id] = layer_1_node_sum;
		m_sigma_iter++;
	}

	for (auto layer_2_node_id = 0; layer_2_node_id < T___GLOBAL_LAYER_2_NODE_COUNT; ++layer_2_node_id)
	{
		double layer_2_node_sum = 0.0;
		for (auto layer_1_node_id = 0; layer_1_node_id < T___GLOBAL_LAYER_1_NODE_COUNT; ++layer_1_node_id)
		{
			layer_2_node_sum += m_layer_1[layer_1_node_id] * m_all_weights_TESTING[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_2_node_sum, m_sigma_iter);
		m_layer_2[layer_2_node_id] = layer_2_node_sum;
		m_sigma_iter++;
	}

	for (auto layer_3_node_id = 0; layer_3_node_id < T___GLOBAL_LAYER_3_NODE_COUNT; ++layer_3_node_id)
	{
		double layer_3_node_sum = 0.0;
		for (auto layer_2_node_id = 0; layer_2_node_id < T___GLOBAL_LAYER_2_NODE_COUNT; ++layer_2_node_id)
		{
			layer_3_node_sum += m_layer_2[layer_2_node_id] * m_all_weights_TESTING[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(layer_3_node_sum, m_sigma_iter);
		m_layer_3[layer_3_node_id] = layer_3_node_sum;
		m_sigma_iter++;
	}

	m_output = m_layer_3[0];
}

//NTR
double NeuralNetwork::get_output()
{
	return m_output;
}

//NTR
int NeuralNetwork::get_board_count()
{
	return m_board_record.size();
}

//NTR
int NeuralNetwork::get_weight_count()
{
	return GLOBAL_WEIGHT_COUNT;
}
