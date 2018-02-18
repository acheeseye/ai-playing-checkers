#ifndef _INCLUDED_NEURALNETWORK_H_
#define _INCLUDED_NEURALNETWORK_H_

#include <vector>
#include <fstream>
#include <queue>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<int> & layer_and_node_count);
	void set_player(int player);
	void set_king_value(double king_value);
	void set_weight_range(double min, double max);
	void set_sigmoid(double sigmoid);
	void init_weights_and_sigmoid();
	void set_board_record_with(const std::string & file_name);
	void set_input_layer(int board_id);
	void calculate_output();
	double get_output();
private:
	int m_player;
	int m_layer_count;
	int m_current_layer_id;
	double m_king_value;
	double m_weight_min;
	double m_weight_max;
	double m_sigmoid;
	double m_output;
	std::vector<int> m_all_layers_node_count;
	std::queue<double> m_all_weights;
	std::vector<double> m_all_sigmoid;
	std::vector<double> m_input_layer;
	std::vector<std::vector<double>> m_board_record;

	void set_next_layer_input();
};

#endif // !_INCLUDED_NEURALNETWORK_H_