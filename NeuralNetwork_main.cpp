#include "NeuralNetwork.h"
#include "board.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
#include <string>
using std::string;
#include <limits>
using std::numeric_limits;
#include <vector>
using std::vector;

int main()
{
	//double input_sum = 1.3;
	//double sigma = 0.05;
	//cout << (2 / (1 + exp(-input_sum * sigma)) - 1) << endl;

	//return 0;

	vector<int> nn_info{ 32, 40, 10, 1 };
	NeuralNetwork nn0(nn_info);
	nn0.set_player(_RED_);
	nn0.init();
	nn0.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");

	for (auto board_id = 0; board_id < nn0.get_board_count(); ++board_id) {
		nn0.set_input_layer(board_id);
		nn0.calculate_output();
		cout << nn0.get_output() << endl;
	}

	cout << "'Enter' to quit . . .";
	while (cin.get() != '\n');

	return 0;
}