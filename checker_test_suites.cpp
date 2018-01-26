//Tests for checkers program
//Uses catch framework.
//
//In order to add/ modify tests,
//simply write
//		TEST_CASE(" description ", "[ Test Category ]")
//		{
//			//code to be tested
//		}
//
//Inside of test case, use
//			INFO("description");
//to give user description of current subtest. Use
//			REQUIRE( some boolean );
//fo actual condition being tested.


#include "board.h"
#include "piece.h"
#include <iostream>
using std::cout;
using std::endl;


#define CATCH_CONFIG_FAST_COMPILE
// Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

//************************* Test Cases *****************************

void print_info(Board board0) {
	cout << "Player 1 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _P1_) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 1 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _P1_) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _P2_) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _P2_) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "INSTRUCTION FINISHED***************************************" << endl << endl;
}


TEST_CASE("Random Tests","[Random Tests]")
{
	Board board0(8, 8);
	int p1_piece0 = 12;


	bool flag = board0.move_piece(11, 64);
	INFO("Should Return False, Player 2 cannot move before player 1");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 64);
	INFO("Should Return False, Illegal Move");
	REQUIRE(!flag);
	print_info(board0);


	flag = board0.move_piece(11, 64);
	INFO("Player 1 has yet to make legal move");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 75);
	INFO("Player 1 makes legal move");
	REQUIRE(flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 64);
	INFO("Player 1 attempts to move before player 2");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 64);
	INFO("Player 1 attempts to move before player 2 again");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(11, 70);
	INFO("Player 2 makes Illegal move");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(11, 68);
	INFO("Legal move");
	REQUIRE(flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 75);
	INFO("Player 1 attempts to move to occupied squre");
	REQUIRE(!flag);
	print_info(board0);

	flag = board0.move_piece(p1_piece0, 62);
	INFO("Legal move");
	REQUIRE(flag);
	print_info(board0);



	//move 4 -- player 2 makes illegal move (moving backwards)
	flag = board0.move_piece(11, 57);
	INFO("move 4, player 2 makes illegal move, (moving backwards");
	REQUIRE(!flag);
	print_info(board0);

	//move 4 -- player 2 makes illegal move (moving backwards)
	flag = board0.move_piece(11, 55);
	INFO("move 4 -- player 2 makes illegal move (moving backwards");
	REQUIRE(!flag);
	print_info(board0);

	//move 4 -- player 2 makes legal move
	flag = board0.move_piece(11, 79);
	INFO("move 4 -- player 2 makes legal move");
	REQUIRE(flag);
	print_info(board0);

	//move 5 -- player 1 makes illegal move (tries to jump over a piece but next piece in line is not empty)
	flag = board0.move_piece(12, 51);
	INFO("move 5 -- player 1 tries to jump over piece when next in line is not empty.");
	REQUIRE(!flag);
	print_info(board0);

	//move 5 -- player 1 makes legal move (tries to move onto player 2 piece, which
	//										results in a jump)
	flag = board0.move_piece(14, 79);
	INFO("Player 1 makes legal move");
	REQUIRE(flag);
	print_info(board0);

	//move 6 -- player 2 makes legal move (jump it must take)
	flag = board0.move_piece(10, 68);
	INFO("move 6 -- player 2 makes legal move");
	REQUIRE(flag);
	print_info(board0);
}