// main.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"

#include <iostream>
using std::cout;
using std::endl;

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

int main() {
	cout << "START OF PROGRAM" << endl;

	//setup
	Board board0(8, 8);
	int p1_piece0 = 12;

	//move 0 -- print initial board & info
	board0.print_board();
	print_info(board0);

//SERIES OF TESTS -- I'M NOT SURE HOW TO USE CATCH AT THE MOMENT

	//move 1 -- player 2 tries to play before player 1
	board0.move_piece(11, 64);
	print_info(board0);

	//move 1 -- player 1 makes illegal move
	board0.move_piece(p1_piece0, 64);
	print_info(board0);

	//move 1 -- player 2 tries to play after player 1 makes illegal move
	board0.move_piece(11, 64);
	print_info(board0);

	//move 1 -- player 1 makes legal move
	board0.move_piece(p1_piece0, 75);
	print_info(board0);

	//move 2 -- player 1 tries to play during player 2's turn
	board0.move_piece(p1_piece0, 64);
	print_info(board0);

	//move 2 -- player 1 tries to play during player 2's turn again
	board0.move_piece(p1_piece0, 64);
	print_info(board0);

	//move 2 -- player 2 makes illegal move (collision with boarder)
	board0.move_piece(11, 70);
	print_info(board0);

	//move 2 -- player 2 makes legal move
	board0.move_piece(11, 68);
	print_info(board0);

	//move 3 -- player 1 makes illegal move (moving to same spot)
	board0.move_piece(p1_piece0, 75);
	print_info(board0);

	//move 3 -- player 1 makes legal move
	board0.move_piece(p1_piece0, 62);
	print_info(board0);

	//move 4 -- player 2 makes illegal move (moving backwards)
	board0.move_piece(11, 57);
	print_info(board0);

	//move 4 -- player 2 makes illegal move (moving backwards)
	board0.move_piece(11, 55);
	print_info(board0);

	//move 4 -- player 2 makes legal move
	board0.move_piece(11, 79);
	print_info(board0);

	//move 5 -- player 1 makes illegal move (tries to jump over a piece but next piece in line is not empty)
	board0.move_piece(12, 51);
	print_info(board0);

	//move 5 -- player 1 makes legal move (tries to move onto player 2 piece, which
	//										results in a jump)
	board0.move_piece(14, 79);
	print_info(board0);

	//move 6 -- player 2 makes legal move (jump it must take)
	board0.move_piece(10, 68);
	print_info(board0);

	cout << endl;
}