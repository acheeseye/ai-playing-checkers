#ifndef _INCLUDED_NNNODES_H_
#define _INCLUDED_NNNODES_H_

#include "connector.h"

#include <vector>
using std::vector;

class NNNodes // NN = NeuralNetwork
{
public:
	NNNodes() {};
	NNNodes(int layer_id, int connector_count);
	int get_layer_id();
	int get_connector_count();
	double get_output();
	double get_input_sum();
	double get_sigmoid_activation();
	void set_sigmoid_activation(double value);
	void calculate_and_set_output(vector<double> & inputs);
private:
	double m_input_sum;
	double m_output;
	double m_sigmoid_activation;
	int m_layer_id;
	vector<Connector> m_output_connectors;

	// only to be used by function get_output()
	double sigmoid();
};

#endif // !_INCLUDED_NNODES_H_
