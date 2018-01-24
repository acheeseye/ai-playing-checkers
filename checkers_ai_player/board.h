// board.h
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan, 23, 2018

#ifndef _INCLUDED_BOARD_H_
#define _INCLUDED_BOARD_H_

#include "piece.h"

#include <vector>
//for std::vector
#include <string>
//for std::string

enum {
	_P2_KING_ = -2,
	_P2_MAN_ = -1,
	_P1_MAN_ = 1,
	_P1_KING_,
	_BOARDER_,
	_PLAYABLE_
};

class Board {
public:
	Board(int width, int height);
	void print_board();

private:
	int m_width;
	int m_height;
	std::vector<int> m_board;

public:
	//these should be protected? (Piece class is not currently inherited)
	//or we can make a function in Piece to return the pieces and then store it
	//(access @ main)
	std::vector<Piece> m_p1_pieces;
	std::vector<Piece> m_p2_pieces;

};

#endif // !_INCLUDED_BOARD_H_