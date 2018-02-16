////Tests for checkers program
////Uses catch framework.
////
////In order to add/ modify tests,
////simply write
////		TEST_CASE(" description ", "[ Test Category ]")
////		{
////			//code to be tested
////		}
////
////Inside of test case, use
////			INFO("description");
////to give user description of current subtest. Use
////			REQUIRE( some boolean );
////fo actual condition being tested.
//
//
//#include "board.h"
//#include "NeuralNetwork.h"
//#include "double.h"
//#include <iostream>
//using std::cout;
//using std::endl;
//#include <vector>
//using std::vector;
//#include <math.h>
//using std::exp;
//
//
//#define CATCH_CONFIG_FAST_COMPILE
//// Disable some features for faster compile
//#include "catch.hpp"       // For the "Catch" unit-testing framework
//
////************************* Test Cases *****************************
//
//
//
//TEST_CASE("Default Constructor","[Default Constructor]")
//{
//	temp_Board board(_RED_);
//	int number_of_moves = board.get_move_list().size();
//
//	{
//		INFO("Player should be red");
//		REQUIRE(board.get_Player() == _RED_);
//	}
//
//	{
//		INFO("Should be 7 available moves");
//		REQUIRE(number_of_moves == 7);
//	}
//
//	{
//		board.move_piece(0);
//		number_of_moves = board.get_move_list().size();
//		INFO("Should be 7 available moves");
//		REQUIRE(number_of_moves == 7);
//	}
//
//	{
//		INFO("Player should be black");
//		REQUIRE(board.get_Player() == _BLACK_);
//	}
//
//	{
//		board.move_piece(2);
//		number_of_moves = board.get_move_list().size();
//		INFO("Should be 8 moves");
//		REQUIRE(number_of_moves == 8);
//	}
//
//	{
//		temp_Board board2 = board;
//		board2.move_piece(board2.get_move_list().size());
//		INFO("Board 2 should remain unchanged since move is out of range");
//		REQUIRE(board2 == board);
//		board2.move_piece(-5);
//		INFO("Board 2 should remain unchange since move is out of range");
//		REQUIRE(board2 == board);
//	}
//
//}
//
//TEST_CASE("Jumps", "[Jumps]")
//{
//	std::vector<int> boardState;
//	boardState.resize(32);
//
//	//Initializes board state
//	for (int i = 0; i < 32; ++i)
//	{
//		boardState.at(i) = _PLAYABLE_;
//	}
//
//	boardState.at(17) = _BLACK_MAN_;
//	boardState.at(14) = _RED_MAN_;
//
//	{
//		INFO("Vector constructor");
//		temp_Board board1(boardState, _BLACK_);
//
//		INFO("Should only contain 1 jump move");
//		std::vector<int> move;
//		move.resize(2);
//		move.at(0) = 17;
//		move.at(1) = 10;
//		REQUIRE(board1.get_move_list().size() == 1);
//		REQUIRE(board1.get_move_list().at(0) == move);
//	}
//	for (int i = 0; i < 32; ++i)
//	{
//		boardState.at(i) = _PLAYABLE_;
//	}
//
//	INFO("Jump into final row");
//	boardState.at(10) = _BLACK_MAN_;
//	boardState.at(6) = _RED_MAN_;
//	{
//		temp_Board board2(boardState, _BLACK_);
//		board2.move_piece(0);
//	}
//
//	for (int i = 0; i < 32; ++i)
//	{
//		boardState.at(i) = _PLAYABLE_;
//	}
//	INFO("Red jump into final row");
//	boardState.at(21) = _RED_MAN_;
//	boardState.at(25) = _BLACK_MAN_;
//	boardState.at(24) = _BLACK_MAN_;
//	{
//		temp_Board board2(boardState, _RED_);
//		board2.move_piece(0);
//	}
//	{
//		temp_Board board2(boardState, _RED_);
//		board2.move_piece(1);
//	}
//
//	for (int i = 0; i < 32; ++i)
//	{
//		boardState.at(i) = _PLAYABLE_;
//	}
//
//	boardState.at(3) = _BLACK_KING_;
//	boardState.at(5) = _RED_KING_;
//	boardState.at(6) = _RED_MAN_;
//	boardState.at(7) = _RED_KING_;
//	boardState.at(13) = _RED_KING_;
//	boardState.at(14) = _RED_KING_;
//	boardState.at(15) = _RED_KING_;
//	boardState.at(21) = _RED_KING_;
//	boardState.at(22) = _RED_MAN_;
//	boardState.at(23) = _RED_KING_;
//	{
//		temp_Board board2(boardState, _BLACK_);
//		INFO("Jumping nightmare, should be 9 possible moves");
//		REQUIRE( board2.get_move_list().size() == 9);
//		//draw_board(board2);
//		//board2.print_moves();
//	}
//
//
//	for (int i = 0;i < 32;++i)
//	{
//		boardState[i] = _PLAYABLE_;
//	}
//	boardState.at(3) = _RED_KING_;
//	boardState.at(5) = _BLACK_KING_;
//	boardState.at(6) = _BLACK_MAN_;
//	boardState.at(7) = _BLACK_KING_;
//	boardState.at(13) = _BLACK_KING_;
//	boardState.at(14) = _BLACK_KING_;
//	boardState.at(15) = _BLACK_KING_;
//	boardState.at(21) = _BLACK_KING_;
//	boardState.at(22) = _BLACK_MAN_;
//	boardState.at(23) = _BLACK_KING_;
//	{
//		temp_Board board2(boardState, _RED_);
//		INFO("Jumping nighmare, should be 9 possible moves");
//		REQUIRE(board2.get_move_list().size() == 9);
//	}
//
//	for (int i = 0;i < 32;++i)
//	{
//		boardState[i] = _PLAYABLE_;
//	}
//	boardState.at(0) = _RED_MAN_;
//	boardState.at(1) = _RED_MAN_;
//	boardState.at(3) = _RED_MAN_;
//	boardState.at(7) = _RED_MAN_;
//	boardState.at(9) = _RED_MAN_;
//	boardState.at(10) = _RED_MAN_;
//	boardState.at(11) = _RED_MAN_;
//	boardState.at(16) = _BLACK_MAN_;
//	boardState.at(18) = _BLACK_MAN_;
//	boardState.at(21) = _RED_KING_;
//	boardState.at(25) = _BLACK_MAN_;
//	boardState.at(26) = _BLACK_MAN_;
//	boardState.at(27) = _BLACK_MAN_;
//	boardState.at(31) = _BLACK_MAN_;
//	{
//		temp_Board board2(boardState,_RED_);
//		INFO("red-up-left without recursion test, should give two answers");
//		REQUIRE( (board2.get_move_list().size() == 2) );
//		//draw_board(board2);
//		//board2.print_moves();
//	}
//
//	for (int i = 0;i < 32;++i)
//	{
//		boardState[i] = _PLAYABLE_;
//	}
//	boardState.at(9) = _RED_MAN_;
//	boardState.at(10) = _RED_MAN_;
//	boardState.at(14) = _BLACK_MAN_;
//	boardState.at(17) = _RED_MAN_;
//	boardState.at(18) = _RED_MAN_;
//	{
//		temp_Board board2(boardState, _BLACK_);
//	}
//
//	boardState.at(9) = _BLACK_MAN_;
//	boardState.at(10) = _BLACK_MAN_;
//	boardState.at(14) = _RED_MAN_;
//	boardState.at(17) = _BLACK_MAN_;
//	boardState.at(18) = _BLACK_MAN_;
//	{
//		temp_Board board2(boardState, _RED_);
//	}
//
//	boardState.at(9) = _RED_MAN_;
//	boardState.at(10) = _RED_MAN_;
//	boardState.at(14) = _BLACK_KING_;
//	boardState.at(17) = _RED_MAN_;
//	boardState.at(18) = _RED_MAN_;
//	{
//		temp_Board board2(boardState, _BLACK_);
//	}
//
//	boardState.at(9) = _BLACK_MAN_;
//	boardState.at(10) = _BLACK_MAN_;
//	boardState.at(14) = _RED_KING_;
//	boardState.at(17) = _BLACK_MAN_;
//	boardState.at(18) = _BLACK_MAN_;
//	{
//		temp_Board board2(boardState, _RED_);
//	}
//
//	for (int i = 0;i < 32;i++)
//	{
//		boardState.at(i) = _PLAYABLE_;
//	}
//	boardState.at(1) = _RED_MAN_;
//	boardState.at(2) = _RED_MAN_;
//	boardState.at(3) = _RED_MAN_;
//	boardState.at(4) = _RED_MAN_;
//	boardState.at(5) = _RED_MAN_;
//	boardState.at(7) = _RED_MAN_;
//	boardState.at(9) = _RED_MAN_;
//	boardState.at(10) = _RED_MAN_;
//	boardState.at(11) = _RED_MAN_;
//	boardState.at(12) = _BLACK_MAN_;
//	boardState.at(13) = _RED_MAN_;
//	boardState.at(16) = _BLACK_MAN_;
//	boardState.at(23) = _BLACK_MAN_;
//	boardState.at(24) = _BLACK_MAN_;
//	boardState.at(25) = _BLACK_MAN_;
//	boardState.at(26) = _BLACK_MAN_;
//	boardState.at(27) = _BLACK_MAN_;
//	boardState.at(28) = _BLACK_MAN_;
//	boardState.at(30) = _BLACK_MAN_;
//	boardState.at(31) = _BLACK_MAN_;
//	{
//		temp_Board board2(boardState, _RED_);
//	}
//}
//
////Optimizing will come later. Ignore this series of tests.
//
////TEST_CASE("Proof of faster Sigmoid calculation")
////{
////	vector<double> dummy_input{ 0.1, 0.1156, 0, 0.923 };
////	double sum = 0.0;
////	double sigmoid_activation = 0.5;
////	for (auto i = 0; i < dummy_input.size(); ++i) sum += dummy_input[i];
////
////	//calculation one:
////	double result = 1 / (1 + exp((-sum) * sigmoid_activation));
////	int rounder = 10000;
////	int tmp_result = result * rounder;
////	result = (double)tmp_result / (double)rounder;
////
////	{
////		INFO("Normal calculation of Sigmoid output");
////		REQUIRE(result == 0.6386);
////	}
////
////	//calculation two:
////	/*sigmoid_activation = 0.1;
////	result = 1 / (1 + exp((-sum) * sigmoid_activation));
////	double result_two = 0.5 * (sum * sigmoid_activation / (1 + abs(sum*sigmoid_activation))) + 0.5;
////	tmp_result = result_two * rounder;
////	result_two = (double)tmp_result / (double)rounder;
////	{
////		INFO("New function's output for Sigmoid activation variable as 0.1");
////		REQUIRE(result_two == result);
////	}*/
////
////	sum = 1;
////	sigmoid_activation = 0.3;
////	result = 1 / (1 + exp((-sum) * sigmoid_activation));
////	double result_two = 0.5 * (sum * sigmoid_activation / (1 + abs(sum*sigmoid_activation))) + 0.5;
////	//tmp_result = result_two * rounder;
////	//result_two = (double)tmp_result / (double)rounder;
////	{
////		INFO("New function's output for Sigmoid activation variable as 0.3");
////		REQUIRE(result_two == result);
////	}
////}
//
//TEST_CASE("Testing for class double construction", "[One parameter]")
//{
//	int layer_id = 0;
//	int dummy_next_layer_node_count = 10;
//	bool ctor_flag;
//	try {
//		double node0(layer_id, dummy_next_layer_node_count);
//		ctor_flag = false;
//	}
//	catch (...)
//	{
//		ctor_flag = true;
//	}
//
//	{
//		INFO("Construction try catch");
//		REQUIRE(ctor_flag == false);
//	}
//
//	double node0(layer_id, dummy_next_layer_node_count);
//
//	{
//		INFO("Constructing NNNode with layer_id = 0");
//		REQUIRE(node0.get_layer_id() == 0);
//	}
//
//	double node1(layer_id, dummy_next_layer_node_count);
//	{
//		INFO("Construction another double with layer_id = 0");
//		REQUIRE(node1.get_layer_id() == 0);
//	}
//
//	double sigmoid_activation = 0.5;
//	node0.set_sigmoid_activation(sigmoid_activation);
//
//	{
//		INFO("Check for correct sigmoid activation set");
//		REQUIRE(node0.get_sigmoid_activation() == 0.5);
//	}
//
//	vector<double> dummy_input{ 
//		-1, -1, -1, -1,
//		-1, -1, -1, -1,
//		-1, -1, -1, -1,
//		0, 0, 0, 0,
//		0, 0, 0, 0,
//		1, 1, 1, 1,
//		1, 1, 1, 1,
//		1, 1, 1, 1,
//	};
//	node0.calculate_and_set_output(dummy_input);
//	{
//		INFO("Calculate input sum with input of initial board");
//		REQUIRE(node0.get_input_sum() == 0);
//	}
//
//	{
//		INFO("The output node with initial board status");
//		REQUIRE(node0.get_output() == 0);
//	}
//}
//
//TEST_CASE("Testing for class NeuralNetwork", "[Construction two parameter]")
//{
//	int layer_count = 5;
//	NeuralNetwork brunette26(5, _RED_);
//	{
//		INFO("NN construction size layer count as 5");
//		REQUIRE(brunette26.get_max_layer_count() == 5);
//	}
//
//	brunette26.set_node_count(0, 4);
//	brunette26.set_node_count(1, 32);
//	brunette26.set_node_count(2, 40);
//	brunette26.set_node_count(3, 10);
//	brunette26.set_node_count(4, 1);
//
//	{
//		INFO("NN node counts: 4, 32, 40, 10, 1");
//		REQUIRE(brunette26.get_node_count(0) == 4);
//		REQUIRE(brunette26.get_node_count(1) == 32);
//		REQUIRE(brunette26.get_node_count(2) == 40);
//		REQUIRE(brunette26.get_node_count(3) == 10);
//		REQUIRE(brunette26.get_node_count(4) == 1);
//	}
//
//	brunette26.init_nodes();
//
//	{
//		INFO("NNNode connector count must be correct");
//		REQUIRE(brunette26.get_node(0, 0).get_connector_count() == 32);
//		REQUIRE(brunette26.get_node(1, 0).get_connector_count() == 40);
//		REQUIRE(brunette26.get_node(2, 0).get_connector_count() == 10);
//		REQUIRE(brunette26.get_node(3, 0).get_connector_count() == 1);
//		REQUIRE(brunette26.get_node(4, 0).get_connector_count() == 0);
//	}
//}