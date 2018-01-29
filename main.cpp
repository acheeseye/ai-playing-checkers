// main.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void print_info(Board board0) {
	cout << "Player 1 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _BLACK_) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 1 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _BLACK_) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _RED_) {
			int a = board0.m_pieces[i].get_true_position();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "Player 2 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_pieces.size(); ++i) {
		if (board0.m_pieces[i].get_owner() == _RED_) {
			int a = board0.m_pieces[i].get_direction();
			cout << a << " ";
		}
	}
	cout << endl;
	cout << "INSTRUCTION FINISHED***************************************" << endl << endl;
}

int main() {
	Board board0(8, 8, _BLACK_);

	int p1_piece0 = 12;

	//move 0 -- print initial board & info
	board0.print_board();
	//board0.move_piece(92, 79);
	//board0.move_piece(57, 68);
	//board0.move_piece(79, 66);
	//board0.move_piece(79, 57);

	//this:
	//92 79 57 68 79 57 55 68
	//produces a disappearing r piece
	//92 79 57 68 79 57 55 68 90 79 68 90

//SERIES OF TESTS -- I'M NOT SURE HOW TO USE CATCH AT THE MOMENT

	while (!board0.game_ended()) {
		int current;
		int destination;
		cout << "Enter the next move: ";
		cin >> current >> destination;
		if (current == 0) {
			board0.print_moves_made();
			board0.print_all_current_possible_jumps();
			board0.print_all_current_possible_moves();
			print_info(board0);
		}
		else if (current == 1) {
			break;
		}
		else {
			board0.move_piece(current, destination);
		}
	}

	cout << endl;
}