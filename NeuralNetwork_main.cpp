#include "NeuralNetwork.h"
#include "board.h"
// For player playing

#include <stdlib.h>
#include <time.h>

#include <string>
using std::string;
#include <random>
using std::mt19937;


int main()
{

	NeuralNetwork brunette26(4, _BLACK_);
	brunette26.set_node_count(0, 32);
	brunette26.set_node_count(1, 40);
	brunette26.set_node_count(2, 10);
	brunette26.set_node_count(3, 1);
	brunette26.init_nodes();

	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(1, 3);
	brunette26.set_king_value(uniform_dist(e1));

	string file_to_read = "ai-playing-checkers\\readable_game_data\\readable_game_20180215_130538.txt";
	brunette26.board_evaluation(file_to_read);
}