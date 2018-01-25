// board.h
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

// See board.cpp for documentation.

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

enum {
	_P1_ = 1,
	_P2_
};

class Board {
public:
	Board(int width, int height);

	void print_board();
	void init_board();
	void clear_board();
	void update_board();
	void pass_turn();

	int get_piece_id(int position);

	bool valid_man_move(int piece_id, int player, int & destination);
	bool ownership_check(int piece_id, int player);
	bool is_boarder(int position);
	bool is_empty(int position);
	bool move_piece(int piece_id, int destination);

	std::vector<Piece> m_pieces; // this is public for the purpose of allowing main to print

private:
	int m_current_player;
	int m_player_to_move;
	int m_width;
	int m_height;
	int m_number_of_turns;
	std::vector<int> m_board;
};

#endif // !_INCLUDED_BOARD_H_