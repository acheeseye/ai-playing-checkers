#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include <vector>
#include <fstream>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<int> & layer_and_node_count, int player, double king_val);
	void init_weights_and_sigmoid();
	void read_board_input_from(const std::string & file_name);
	void set_first_layer_input(const std::vector<double> & input);
private:
	int m_player;
	int m_layer_count;
	double m_king_value;
	std::vector<int> m_all_layers_node_count;
	std::vector<double> m_all_weights;
	std::vector<double> m_all_sigmoid;
	//std::vector<std::vector<double>> m_
};

#endif // !_INCLUDED_NEURALNETWORK_H_