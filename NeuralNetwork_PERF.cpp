#include "NeuralNetwork_PERF.h"
#include "board.h"

#include <random>
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <string>
using std::string;
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>

NeuralNetwork_PERF::NeuralNetwork_PERF(const int player)
{
	if (player == _RED_)
	{
		m_player_modifier = -1;
	}
	else if (player == _BLACK_)
	{
		m_player_modifier = 1;
	}
}

void NeuralNetwork_PERF::set_input_layer(const std::vector<int>& input)
{
	if (input.size() != GLOBAL_LAYER_0_NC) throw std::exception("INVALID INPUT SIZE");
	for (auto i = 0; i < GLOBAL_LAYER_0_NC; ++i)
	{
		if (input[i] == 2) 
		{
			m_nodes[i] = m_king_val * m_player_modifier;
		}
		else if (input[i] == -2) 
		{
			m_nodes[i] = -m_king_val * m_player_modifier;
		}
		else m_nodes[i] = input[i] * m_player_modifier;
	}
	for(auto i = GLOBAL_LAYER_0_NC; i < GLOBAL_NC; ++i)
	{
		m_nodes[i] = 0;
	}
}

void NeuralNetwork_PERF::set_topology(const std::vector<double>& topology)
{
	m_king_val = topology[0];
	for (auto i = 1; i < 1 + GLOBAL_WC; ++i)
	{
		m_weights[i - 1] = topology[i];
	}
}

double NeuralNetwork_PERF::apply_sigma(const double input_sum)
{
	return (double(2) / (double(1) + double(exp(-input_sum))) - double(1));
}

void NeuralNetwork_PERF::calculate()
{
	m_weight_iter = 0;

	for (int l_1 = 0; l_1 < GLOBAL_LAYER_1_NC; ++l_1)
	{
		for (int l_0 = 0; l_0 < GLOBAL_LAYER_0_NC; ++l_0)
		{
			m_nodes[GLOBAL_LAYER_0_NC + l_1] += m_nodes[l_0] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		m_nodes[GLOBAL_LAYER_0_NC + l_1] = apply_sigma(m_nodes[GLOBAL_LAYER_0_NC + l_1]);
	}

	for (int l_2 = 0; l_2 < GLOBAL_LAYER_2_NC; ++l_2)
	{
		for (int l_1 = 0; l_1 < GLOBAL_LAYER_1_NC; ++l_1)
		{
			m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + l_2] += m_nodes[l_1] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + l_2] = apply_sigma(m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + l_2]);
	}

	for (int l_3 = 0; l_3 < GLOBAL_LAYER_3_NC; ++l_3)
	{
		for (int l_2 = 0; l_2 < GLOBAL_LAYER_2_NC; ++l_2)
		{
			m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + GLOBAL_LAYER_2_NC + l_3] += m_nodes[l_2] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		for (int l_0 = 0; l_0 < GLOBAL_LAYER_0_NC; ++l_0)
		{
			m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + GLOBAL_LAYER_2_NC + l_3] += m_nodes[l_0] * m_player_modifier * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		m_nodes[GLOBAL_NC - 1] = apply_sigma(m_nodes[GLOBAL_NC - 1]);
	}
}

double NeuralNetwork_PERF::get_result()
{
	return m_nodes[GLOBAL_NC - 1];
}

int NeuralNetwork_PERF::get_player_modification() const
{
	return m_player_modifier;
}
