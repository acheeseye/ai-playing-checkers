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
	void set_node_count(int layer_id, int node_count);
private:
	int m_max_layers;
	vector<layer_type> m_all_layers;
};

#endif // !_INCLUDED_NEURALNETWORK_H_
