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
#include <time.h>

clock_t t;

int main()
{
	vector<int> nn_info{ 32, 40, 10, 1 }; //blondie24
	vector<int> nn_info1{ 32, 100, 50, 30, 10, 1 }; //6 layers & >10,000 weights
	NeuralNetwork nn0(nn_info);
	NeuralNetwork nn1(nn_info1);
	nn0.init();
	nn1.init();
	nn0.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");
	nn1.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");

	cout.precision(6);
	cout << "nn0 weights: " << nn0.get_weight_count() << endl;
	for (volatile int i = 0; i < 10; ++i) { //not sure about volatile int usage, but no optimization?
		double t_sum = 0;
		for (auto board_id = 0; board_id < nn0.get_board_count(); ++board_id) 
		{
			nn0.set_input_layer(board_id);
			t = clock();
			nn0.calculate_output();
			t = clock() - t;
			t_sum += ((double)t) / CLOCKS_PER_SEC;
			//cout << nn0.get_output() << endl;
		}
		double avg = t_sum / (double)nn0.get_board_count();
		cout << "nn0: Average calculation_output elapsed time: " << avg << " sec (";
		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
	}

	cout << endl;
	cout << "nn1 weights: " << nn1.get_weight_count() << endl;
	for (volatile int i = 0; i < 10; ++i) { //not sure about volatile int usage, but no optimization?
		double t_sum = 0;
		for (auto board_id = 0; board_id < nn1.get_board_count(); ++board_id) 
		{
			nn1.set_input_layer(board_id);
			t = clock();
			nn1.calculate_output();
			t = clock() - t;
			t_sum += ((double)t) / CLOCKS_PER_SEC;
			//cout << nn1.get_output() << endl;
		}
		double avg = t_sum / (double)nn1.get_board_count();
		cout << "nn1: Average calculation_output elapsed time: " << avg << " sec (";
		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
	}

	cout << "'Enter' to quit . . .";
	while (cin.get() != '\n');

	return 0;
}