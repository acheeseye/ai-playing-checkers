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