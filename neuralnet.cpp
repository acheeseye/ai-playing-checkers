#include "neuralnet.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

inline static double sigmoid(double x,size_t index,const double a=1,const double b=1,const double c=0)
{
	switch(index)
	{
		case 0:
			return x;
		case 1:
			return 2.0/(1.0+std::exp(-x/b))-1.0;
		default:
			throw std::runtime_error("Invalid sigmoid index(expected value 0<=index<=2).");
	};
}

skynet::neuralnet_t::neuralnet_t(
	const std::vector<size_t>& layers,
	const std::vector<double>& weights,
	double king)
	:	layers_m(layers),
		king_m(king)
{
	if (layers_m.empty()) {
		std::cout << "bad layers" << std::endl;
		throw std::runtime_error("Invalid number of layers(expected value >= 0).");
	}

	if (layers_m.back() != 1) {
		std::cout << "invalid argument" << std::endl;
		throw std::invalid_argument("Expected last layer value of 1(got " +
									std::to_string(layers_m.back()) + ").");
	}

	create_node_layers_m();
	set_node_weights_m(weights);
}

double skynet::neuralnet_t::evaluate(const std::vector<int>& inputs,
	std::function<double(const double)> sigmoid)
{
	for (size_t ii = 0; ii < node_layers_m[0].size(); ++ii)
	{
		if (inputs[ii] == 2)
		{
			node_layers_m[0][ii].value = king_m;
		}
		else if (inputs[ii] == -2)
		{
			node_layers_m[0][ii].value = -king_m;
		}
		else if (inputs[ii] == 4)
		{
			node_layers_m[0][ii].value = 0;
		}
		{
			node_layers_m[0][ii].value = inputs[ii];
		}
	}

	for(size_t ii=1;ii<node_layers_m.size();++ii)
	{
		for(size_t jj=0;jj<node_layers_m[ii].size();++jj)
		{
			node_layers_m[ii][jj].value=0;

			for(size_t kk=0;kk<node_layers_m[ii-1].size();++kk)
				node_layers_m[ii][jj].value+=node_layers_m[ii-1][kk].value*node_layers_m[ii-1][kk].weights[jj];

			for(size_t kk=0;kk<piece_count_layer_m.size();++kk)
			{
				node_layers_m[ii][jj].value += piece_count_layer_m[kk].value*piece_count_layer_m[kk].weights[0];
			}
			
			node_layers_m[ii][jj].value=sigmoid(node_layers_m[ii][jj].value);
		}
	}

	return node_layers_m[node_layers_m.size()-1][0].value;
}

double skynet::neuralnet_t::evaluate(const std::vector<int>& inputs,
	const size_t sigmoid_index,const double a,const double b,const double c)
{
	if(b==0)
		throw std::runtime_error("Division by 0.");

	return evaluate(inputs,[&](const double value)
		{return sigmoid(value,sigmoid_index,a,b,c);});
}

void skynet::neuralnet_t::create_node_layers_m()
{
	node_layers_m.clear();
	piece_count_layer_m.clear();

	for(size_t i = 0; i < 32; ++i)
	{
		node_t node;
		node.value = 0;
		node.weights.resize(1,1);
		piece_count_layer_m.push_back(node);
	}

	for(size_t ii=0;ii<layers_m.size();++ii)	// iterate through layout (32, 40, 10, 1)
	{
		if(ii+1<layers_m.size())				// if not last layer
		{
			std::vector<node_t> node_layer;		// vector< pair < vector<double>, valueholder > >

			for(size_t jj=0;jj<layers_m[ii];++jj)	// iterate through each layer layout (32)
			{
				node_t node;
				node.value=0;
				node.weights.resize(layers_m[ii+1],1);	// weight count connecting to next layer
				node_layer.push_back(node);
			}

			node_layers_m.push_back(node_layer);
		}
		else // is last layer
		{
			node_t node;
			node.value=5;
			node.weights.clear();
			node_layers_m.push_back({node});
		}
	}
}

void skynet::neuralnet_t::set_node_weights_m(const std::vector<double>& weights)
{
	std::vector<double*> real_weights;

	for(auto& layer:node_layers_m)
		for(auto& node:layer)
			for (auto& weight : node.weights)
			{
				real_weights.push_back(&weight);
			}

	if (1690 != real_weights.size())
	{
		std::cout << "bad sizes" << std::endl;
		throw std::runtime_error("Invalid number of normal weights(expected " +
								 std::to_string(real_weights.size()) + " got " + std::to_string(weights.size()) + ").");
	}

	size_t riter = 0;
	for (size_t ii = 32; ii < real_weights.size() + 32; ++ii)
	{
		*(real_weights[riter]) = weights[ii];
		riter++;
	}

	for(size_t i = 0; i < 32; ++i)
	{
		piece_count_layer_m[i].weights[0] = weights[i];
	}
}
