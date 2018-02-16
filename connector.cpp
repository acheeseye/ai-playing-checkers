#include "connector.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::mt19937;
#include <functional>
using std::bind;

int count = 0;

Connector::Connector()
{
	init_weight();
}

void Connector::pass_input_and_set_output(double input)
{
	m_output = input * m_weight + m_bias;
}

void Connector::set_weight(double weight)
{
	m_weight = weight;
}

void Connector::set_bias(double bias)
{
	m_bias = bias;
}

void Connector::init_weight()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(-1, 1);
	m_weight = uniform_dist(e1);
}

double Connector::get_weight()
{
	return m_weight;
}

double Connector::get_bias()
{
	return m_bias;
}

double Connector::get_output()
{
	return m_output;
}
