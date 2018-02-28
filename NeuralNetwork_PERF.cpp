#include "NeuralNetwork_PERF.h"

#include <random>
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <string>
using std::string;
using std::to_string;
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>

NeuralNetwork_PERF::NeuralNetwork_PERF(const std::vector<double>& input, const std::vector<double>& topology)
{
	if (input.size() != GLOBAL_LAYER_0_NC) throw std::exception("INVALID INPUT SIZE");
	for (auto i = 0; i < GLOBAL_LAYER_0_NC; ++i)
	{
		m_nodes[i] = input[i];
	}
	for (auto i = GLOBAL_LAYER_0_NC; i < GLOBAL_NC; ++i)
	{
		m_nodes[i] = 0;
	}
	m_king_val = topology[0];
	for (auto i = 1; i < 1 + GLOBAL_WC; ++i)
	{
		m_weights[i - 1] = topology[i];
	}
	for (auto i = 1 + GLOBAL_WC; i < 1 + GLOBAL_WC + GLOBAL_SC; ++i)
	{
		m_sigma[i - 1 - GLOBAL_WC] = topology[i];
	}
}

void NeuralNetwork_PERF::apply_sigma(double & input_sum)
{
	input_sum = (2 / (1 + exp(-input_sum * m_sigma[m_sigma_iter])) - 1);
}

void NeuralNetwork_PERF::calculate()
{
	m_weight_iter = 0;
	m_sigma_iter = 0;

	for (int l_1 = 0; l_1 < GLOBAL_LAYER_1_NC; ++l_1)
	{
		for (int l_0 = 0; l_0 < GLOBAL_LAYER_0_NC; ++l_0)
		{
			m_nodes[GLOBAL_LAYER_0_NC + l_1] += m_nodes[l_0] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(m_nodes[GLOBAL_LAYER_0_NC + l_1]);
		m_sigma_iter++;
	}

	for (int l_2 = 0; l_2 < GLOBAL_LAYER_2_NC; ++l_2)
	{
		for (int l_1 = 0; l_1 < GLOBAL_LAYER_1_NC; ++l_1)
		{
			m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + l_2] += m_nodes[l_1] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(m_nodes[GLOBAL_LAYER_1_NC + l_2]);
		m_sigma_iter++;
	}

	for (int l_3 = 0; l_3 < GLOBAL_LAYER_3_NC; ++l_3)
	{
		for (int l_2 = 0; l_2 < GLOBAL_LAYER_2_NC; ++l_2)
		{
			m_nodes[GLOBAL_LAYER_0_NC + GLOBAL_LAYER_1_NC + GLOBAL_LAYER_2_NC + l_3] += m_nodes[l_2] * m_weights[m_weight_iter];
			m_weight_iter++;
		}
		apply_sigma(m_nodes[GLOBAL_LAYER_2_NC + l_3]);
		m_sigma_iter++;
	}
}
