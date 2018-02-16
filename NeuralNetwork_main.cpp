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
	vector<int> nn_info{ 32, 40, 10, 1 };
	NeuralNetwork nn0(nn_info, _BLACK_, 2.2);
	nn0.read_board_input_from("ai-playing-checkers\\readable_game_data\\readable_game_20180215_184621.txt");

	//cout << endl << endl << "press ENTER to exit";
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "enter to quit" << endl;
	while (cin.get() != '\n');

	return 0;
}