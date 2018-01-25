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
		if (board0.m_pieces[i].get_owner() == 5) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 1 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == 5) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == 6) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == 6) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "INSTRUCTION FINISHED***************************************" << endl << endl;
}

int main() {
	//setup
	Board board0(8, 8);
	board0.init_board();
	int p1_piece0 = 12;

	//print initial board & info
	board0.print_board();
	print_info(board0);

	//move 1 -- player 2 tries to play before player 1

	//move 1 -- player 1 makes illegal move
	board0.move_piece(p1_piece0, 64);
	print_info(board0);

	//move 1 -- player 2 tries to play after player 1 makes illegal move

	//move 1 -- player 1 makes legal move
	board0.move_piece(p1_piece0, 75);
	print_info(board0);

	//move 2 -- player 1 tries ti play during player 2's turn
	board0.move_piece(p1_piece0, 64);
	print_info(board0);

	cout << endl;
}