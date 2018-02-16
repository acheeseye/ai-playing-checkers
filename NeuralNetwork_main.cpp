<<<<<<< HEAD
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
||||||| merged common ancestors
//#include "NeuralNetwork.h"
//
//#include <string>
//using std::string;
//
//int main()
//{
//	NeuralNetwork brunette26(4, 0);
//	brunette26.set_node_count(0, 32);
//	brunette26.set_node_count(1, 40);
//	brunette26.set_node_count(2, 10);
//	brunette26.set_node_count(3, 1);
//	brunette26.init_nodes();
//
//	string file_to_read = "ai-playing-checkers\\compressed_game_data\\cmprss_game_20180215_044817.txt";
//	brunette26.board_evaluation(file_to_read);
//}
=======
/*#include "NeuralNetwork.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
#include <string>
using std::string;
#include <limits>
using std::numeric_limits;

int main()
{
	NeuralNetwork brunette26(4, 0);
	brunette26.set_node_count(0, 32);
	brunette26.set_node_count(1, 40);
	brunette26.set_node_count(2, 10);
	brunette26.set_node_count(3, 1);
	brunette26.init_nodes();

	string file_to_read = "ai-playing-checkers\\games_played\\game_20180215_132515.txt";
	brunette26.board_evaluation(file_to_read);

	cout << endl << endl << "press ENTER to exit";
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (cin.get() != '\n');

	return 0;
}*/
>>>>>>> 93f4875fdea0911e1cc9502e2c8475388d7e89f6
