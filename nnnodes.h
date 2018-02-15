#ifndef _INCLUDED_NNNODES_H_
#define _INCLUDED_NNNODES_H_

#include <vector>
using std::vector;

class NNNodes // NN = NeuralNetwork
{
public:
	NNNodes() {};
	NNNodes(int layer_id);
	int get_layer_id();
	double get_output();
	double get_input_sum();
	double get_sigmoid_activation();
	void set_sigmoid_activation(double value);
	void calculate_and_set_output(vector<double> inputs);
private:
	//vector<double> m_all_inputs;
	double m_input_sum;
	double m_output;
	double m_sigmoid_activation;
	int m_layer_id;

	// only to be used by function get_output()
	double sigmoid();
};

#endif // !_INCLUDED_NNODES_H_
