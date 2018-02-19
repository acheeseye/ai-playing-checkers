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
	//double input_sum = 1.3;
	//double sigma = 0.05;
	//cout << (2 / (1 + exp(-input_sum * sigma)) - 1) << endl;

	//return 0;
	vector<int> nn_info{ 32, 40, 10, 1 };
	NeuralNetwork nn0(nn_info);
	nn0.set_player(_RED_);
	nn0.init();
	nn0.set_board_record_with("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");

	cout.precision(10);

	for (volatile int i = 0; i < 10; ++i) { //not sure about volatile int usage, but no optimization?
		double t_sum = 0;
		for (auto board_id = 0; board_id < nn0.get_board_count(); ++board_id) {

			nn0.set_input_layer(board_id);
			t = clock();
			nn0.calculate_output();
			t = clock() - t;
			t_sum += ((double)t) / CLOCKS_PER_SEC;
			//cout << nn0.get_output() << endl;
		}
		double avg = t_sum / (double)nn0.get_board_count();
		cout << "Average calculation_output elapsed time: " << avg << " sec (";
		cout << 1.0 / avg << " BEF/sec)" << endl;
		cout << "Boards potentially evaluated per 15 seconds: " << 1.0 / avg * 15 << endl;
		cout << endl;
	}

	cout << "'Enter' to quit . . .";
	while (cin.get() != '\n');

	return 0;
}