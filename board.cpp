// board.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan, 23, 2018

#include "board.h"

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

Board::Board(int width, int height)
{
	int p1 = 0;
	int p2 = 1;
	m_width = width + 4;
	m_height = height + 4;
	m_board.resize(m_width * m_height);
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			//setting boarder
			if (row <= 1 || row >= m_height - 2) m_board[index] = _BOARDER_;
			else if (col <= 1 || col >= m_width - 2) m_board[index] = _BOARDER_;
			//setting rest of board
			else {
				if (row % 2 == 1 && col % 2 == 0 ||
					row % 2 == 0 && col % 2 == 1) {
					m_board[index] = _PLAYABLE_;
				}
				if (row < m_height / 2 - 1 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _P2_MAN_;
					Piece p2_piece(index, p2);
					m_p2_pieces.push_back(p2_piece);
				}
				else if (row > m_height / 2 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _P1_MAN_;
					Piece p1_piece(index, p1);
					m_p1_pieces.push_back(p1_piece);
				}
			}
		}
	}
}

void Board::print_board()
{
	char en_man = 'b';
	char man = 'r';
	char boarder = ':';
	char playable = 'x';
	cout << "Printing Game Board..." << endl << endl;
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			//switch may be commented out to print raw enumerated values
			//(just print m_board[...])
			switch (m_board[index]) {
			case _BOARDER_:
				cout << boarder;
				break;
			case _P2_MAN_:
				cout << en_man;
				break;
			case _P1_MAN_:
				cout << man;
				break;
			case _PLAYABLE_:
				cout << playable;
				break;
			default:
				cout << ' ';
				break;
			}
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
