#ifndef _INCLUDED_NNNODES_H_
#define _INCLUDED_NNNODES_H_

#include <vector>
using std::vector;

class NNNodes // NN = NeuralNetwork
{
public:
	NNNodes();
private:
	vector<float> m_all_inputs;
	float m_output;
};

#endif // !_INCLUDED_NNODES_H_
