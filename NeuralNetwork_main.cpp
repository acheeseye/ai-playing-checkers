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
	NeuralNetwork nn0(nn_info, _BLACK_, 2.2);
	nn0.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");
	nn0.set_input_layer(board_id);
	nn0.calculate_output();

	//cout << endl << endl << "press ENTER to exit";
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "'Enter' to quit . . ." << endl;
	while (cin.get() != '\n');

	return 0;
}