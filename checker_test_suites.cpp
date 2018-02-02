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



TEST_CASE("Default Constructor","[Default Constructor]")
{
	temp_Board board;
	int number_of_moves = board.get_move_list().size();
	
	INFO("Should be 7 available moves");
	REQUIRE(number_of_moves == 7);

	board.move_piece(0);
	number_of_moves = board.get_move_list().size();
	INFO("Should be 7 available moves");
	REQUIRE(number_of_moves == 7);

	board.move_piece(2);
	number_of_moves = board.get_move_list().size();
	INFO("Should be 1 move (jump required");
	REQUIRE(number_of_moves == 1);

	temp_Board board2 = board;
	board2.move_piece(board2.get_move_list().size());
	INFO("Board 2 should remain unchanged since move is out of range");
	REQUIRE(board2 == board);

	board2.move_piece(-5);
	INFO("Board 2 should remain unchange since move is out of range");
	REQUIRE(board2 == board);

}

TEST_CASE("Jumps", "[Jumps]")
{
	std::vector<int> boardState;
	boardState.resize(32);

	//Initializes board state
	for (int i = 0; i < 32; ++i)
	{
		boardState.at(i) = _PLAYABLE_;
	}

	boardState.at(17) = _BLACK_MAN_;
	boardState.at(14) = _RED_MAN_;

	{
		INFO("Vector constructor");
		temp_Board board1(boardState, _BLACK_);

		INFO("Should only contain 1 jump move");
		std::vector<int> move;
		move.resize(2);
		move.at(0) = 17;
		move.at(1) = 10;
		draw_board(board1);
		board1.print_moves();
		REQUIRE(board1.get_move_list().size() == 1);
		REQUIRE(board1.get_move_list().at(0) == move);
	}
	for (int i = 0; i < 32; ++i)
	{
		boardState.at(i) = _PLAYABLE_;
	}

	INFO("Jump into final row");
	boardState.at(10) = _BLACK_MAN_;
	boardState.at(6) = _RED_MAN_;
	{
		temp_Board board2(boardState, _BLACK_);
		draw_board(board2);
		board2.print_moves();
		board2.move_piece(0);
		draw_board(board2);
	}

	for (int i = 0; i < 32; ++i)
	{
		boardState.at(i) = _PLAYABLE_;
	}
	INFO("Red jump into final row");
	boardState.at(21) = _RED_MAN_;
	boardState.at(25) = _BLACK_MAN_;
	boardState.at(24) = _BLACK_MAN_;
	{
		temp_Board board2(boardState, _RED_);
		draw_board(board2);
		board2.print_moves();
		board2.move_piece(0);
		draw_board(board2);
	}
	{
		temp_Board board2(boardState, _RED_);
		//draw_board(board2);
		//board2.print_moves();
		board2.move_piece(1);
		//draw_board(board2);
	}

	for (int i = 0; i < 32; ++i)
	{
		boardState.at(i) = _PLAYABLE_;
	}

	boardState.at(3) = _BLACK_KING_;
	boardState.at(5) = _RED_KING_;
	boardState.at(6) = _RED_MAN_;
	boardState.at(7) = _RED_KING_;
	boardState.at(13) = _RED_KING_;
	boardState.at(14) = _RED_KING_;
	boardState.at(15) = _RED_KING_;
	boardState.at(21) = _RED_KING_;
	boardState.at(22) = _RED_MAN_;
	boardState.at(23) = _RED_KING_;
	//boardState.at()
	{
		temp_Board board2(boardState, _BLACK_);
		INFO("Jumping nightmare, should be 9 possible moves");
		REQUIRE( board2.get_move_list().size() == 9);
		//draw_board(board2);
		//board2.print_moves();
	}


	for (int i = 0;i < 32;++i)
	{
		boardState[i] = _PLAYABLE_;
	}
	boardState.at(3) = _RED_KING_;
	boardState.at(5) = _BLACK_KING_;
	boardState.at(6) = _BLACK_MAN_;
	boardState.at(7) = _BLACK_KING_;
	boardState.at(13) = _BLACK_KING_;
	boardState.at(14) = _BLACK_KING_;
	boardState.at(15) = _BLACK_KING_;
	boardState.at(21) = _BLACK_KING_;
	boardState.at(22) = _BLACK_MAN_;
	boardState.at(23) = _BLACK_KING_;
	{
		temp_Board board2(boardState, _RED_);
		INFO("Jumping nighmare, should be 9 possible moves");
		REQUIRE(board2.get_move_list().size() == 9);
		//draw_board(board2);
		//board2.move_piece(2);
		//board2.print_moves();
		//draw_board(board2);
		//board2.print_moves();
	}

	for (int i = 0;i < 32;++i)
	{
		boardState[i] = _PLAYABLE_;
	}
	boardState.at(0) = _RED_MAN_;
	boardState.at(1) = _RED_MAN_;
	boardState.at(3) = _RED_MAN_;
	boardState.at(7) = _RED_MAN_;
	boardState.at(9) = _RED_MAN_;
	boardState.at(10) = _RED_MAN_;
	boardState.at(11) = _RED_MAN_;
	boardState.at(16) = _BLACK_MAN_;
	boardState.at(18) = _BLACK_MAN_;
	boardState.at(21) = _RED_KING_;
	boardState.at(25) = _BLACK_MAN_;
	boardState.at(26) = _BLACK_MAN_;
	boardState.at(27) = _BLACK_MAN_;
	boardState.at(31) = _BLACK_MAN_;
	{
		temp_Board board2(boardState,_RED_);
		INFO("red-up-left without recursion test, should give two answers");
		REQUIRE( (board2.get_move_list().size() == 2) );
		//draw_board(board2);
		//board2.print_moves();
	}

	for (int i = 0;i < 32;++i)
	{
		boardState[i] = _PLAYABLE_;
	}
	boardState.at(9) = _RED_MAN_;
	boardState.at(10) = _RED_MAN_;
	boardState.at(14) = _BLACK_MAN_;
	boardState.at(17) = _RED_MAN_;
	boardState.at(18) = _RED_MAN_;
	{
		temp_Board board2(boardState, _BLACK_);
		draw_board(board2);
		board2.print_moves();
	}

	boardState.at(9) = _BLACK_MAN_;
	boardState.at(10) = _BLACK_MAN_;
	boardState.at(14) = _RED_MAN_;
	boardState.at(17) = _BLACK_MAN_;
	boardState.at(18) = _BLACK_MAN_;
	{
		temp_Board board2(boardState, _RED_);
		draw_board(board2);
		board2.print_moves();
	}

	boardState.at(9) = _RED_MAN_;
	boardState.at(10) = _RED_MAN_;
	boardState.at(14) = _BLACK_KING_;
	boardState.at(17) = _RED_MAN_;
	boardState.at(18) = _RED_MAN_;
	{
		temp_Board board2(boardState, _BLACK_);
		draw_board(board2);
		board2.print_moves();
	}

	boardState.at(9) = _BLACK_MAN_;
	boardState.at(10) = _BLACK_MAN_;
	boardState.at(14) = _RED_KING_;
	boardState.at(17) = _BLACK_MAN_;
	boardState.at(18) = _BLACK_MAN_;
	{
		temp_Board board2(boardState, _RED_);
		draw_board(board2);
		board2.print_moves();
	}

	for (int i = 0;i < 32;i++)
	{
		boardState.at(i) = _PLAYABLE_;
	}
	boardState.at(1) = _RED_MAN_;
	boardState.at(2) = _RED_MAN_;
	boardState.at(3) = _RED_MAN_;
	boardState.at(4) = _RED_MAN_;
	boardState.at(5) = _RED_MAN_;
	boardState.at(7) = _RED_MAN_;
	boardState.at(9) = _RED_MAN_;
	boardState.at(10) = _RED_MAN_;
	boardState.at(11) = _RED_MAN_;
	boardState.at(12) = _BLACK_MAN_;
	boardState.at(13) = _RED_MAN_;
	boardState.at(16) = _BLACK_MAN_;
	boardState.at(23) = _BLACK_MAN_;
	boardState.at(24) = _BLACK_MAN_;
	boardState.at(25) = _BLACK_MAN_;
	boardState.at(26) = _BLACK_MAN_;
	boardState.at(27) = _BLACK_MAN_;
	boardState.at(28) = _BLACK_MAN_;
	boardState.at(30) = _BLACK_MAN_;
	boardState.at(31) = _BLACK_MAN_;
	{
		temp_Board board2(boardState, _RED_);
		draw_board(board2);
		board2.print_moves();
	}
}