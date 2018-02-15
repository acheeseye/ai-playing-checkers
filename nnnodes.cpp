#include "nnnodes.h"

#include <iostream>
using std::cout;
using std::endl;

NNNodes::NNNodes(int layer_id)
{
	m_layer_id = layer_id;
}

int NNNodes::get_layer_id()
{
	return m_layer_id;
}

double NNNodes::get_output()
{
	return m_output;
}

double NNNodes::get_input_sum()
{
	return m_input_sum;
}

double NNNodes::get_sigmoid_activation()
{
	return m_sigmoid_activation;
}

void NNNodes::set_sigmoid_activation(double value)
{
	m_sigmoid_activation = value;
}

void NNNodes::calculate_and_set_output(vector<double> inputs)
{
	m_input_sum = 0.0; // doubles need to be initialized first
	for (auto i = 0; i < inputs.size(); ++i) {
		m_input_sum += inputs.at(i);
	}
	sigmoid();
}

double NNNodes::sigmoid()
{
	//m_output = 0.5 * (m_input_sum * m_sigmoid_activation / (1 + abs(m_input_sum*m_sigmoid_activation))) + 0.5;
	
	//this function allows the sigmoid to reach (approach) -1.0 ~ 1.0 rather than 0.0 ~ 1.0
	m_output = 2 / (1 + exp(-m_input_sum*m_sigmoid_activation)) - 1;
	return m_output;
}
