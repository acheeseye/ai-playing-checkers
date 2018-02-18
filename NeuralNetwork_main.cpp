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
	int board_id = 0;
	vector<int> nn_info{ 32, 40, 10, 1 };
	NeuralNetwork nn0(nn_info);

	nn0.set_king_value(2.2);
	nn0.set_player(_BLACK_);
	nn0.set_sigmoid(0.05);
	nn0.set_weight_range(-0.2, 0.2);
	nn0.init_weights_and_sigmoid();

	nn0.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");
	nn0.set_input_layer(board_id);
	nn0.calculate_output();
	cout << nn0.get_output() << endl;

	//cout << endl << endl << "press ENTER to exit";
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "'Enter' to quit . . ." << endl;
	while (cin.get() != '\n');

	return 0;
}