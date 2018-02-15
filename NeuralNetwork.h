#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include "nnnodes.h"

#include <vector>
using std::vector;

class NeuralNetwork
{
	typedef vector<NNNodes> layer_type;
public:
	NeuralNetwork(int layers);
	int get_max_layer_count();
	int get_node_count(int layer_id);
	void set_node_count(int layer_id, int node_count);

protected:
	int m_max_layer_count;
	vector<layer_type> m_all_layers;
};

#endif // !_INCLUDED_NEURALNETWORK_H_
