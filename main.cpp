// main.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell

#include "board.h"

#include <iostream>
using std::cout;
using std::endl;

int main() {
	Board board0(8, 8);
	board0.print_board();

	cout << "Player 1 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_p1_pieces.size(); ++i) {
		int a = board0.m_p1_pieces[i].get_true_position();
		cout << a << " ";
	}
	cout << endl;
	cout << "Player 1 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_p1_pieces.size(); ++i) {
		int a = board0.m_p1_pieces[i].get_direction();
		cout << a << " ";
	}
	cout << endl;
	cout << "Player 2 Piece Positions: ";
	for (int i = 0; i < (int)board0.m_p1_pieces.size(); ++i) {
		int a = board0.m_p2_pieces[i].get_true_position();
		cout << a << " ";
	}
	cout << endl;
	cout << "Player 2 Piece Direction: ";
	for (int i = 0; i < (int)board0.m_p1_pieces.size(); ++i) {
		int a = board0.m_p2_pieces[i].get_direction();
		cout << a << " ";
	}
	cout << endl;
	
	cout << endl;
}