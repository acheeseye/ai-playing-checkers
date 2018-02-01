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



TEST_CASE("Temp board tests","[temp board]")
{
	temp_Board board;
	draw_board(board);


	int move;

	//std::cin >> move;

	board.generate_moves();
	board.print_moves();
	INFO("Doing move 1");
	move = 3;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();
	move = 1;
	board.move_piece(move);
	draw_board(board);


	board.generate_moves();
	board.print_moves();
	move = 0;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();
	move = 0;
	board.move_piece(move);
	draw_board(board);
	
	board.generate_moves();
	board.print_moves();

	move = 4;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 4;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 0;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 1;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 2;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 1;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();

	move = 0;
	board.move_piece(move);
	draw_board(board);

	board.generate_moves();
	board.print_moves();


	//system("pause");
}