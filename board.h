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
#include <utility>
//for std::pair

enum {
	_RED_KING_ = -2,
	_RED_MAN_ = -1,
	_BLACK_MAN_ = 1,
	_BLACK_KING_,
	_BOARDER_,
	_PLAYABLE_
};

enum {
	_LEFTUP_,
	_RIGHTUP_,
	_LEFTDOWN_,
	_RIGHTDOWN_
};

class Board {
public:
	Board(int width, int height, int starting_player);

	void print_board();
	void print_moves_made();
	void print_all_current_possible_moves();
	void print_all_current_possible_jumps();

	void init_board();
	void init_king_spots(int width);
	void clear_board();
	void update_board();
	void pass_turn();

	int get_piece_id(int position);

	bool ownership_check(int piece_id);
	bool is_boarder(int position);
	bool is_empty(int position);
	bool is_valid_move(std::pair<int, int> attempted_move);
	bool is_valid_jump(std::pair<int, int> attempted_move);
	bool is_king_transformer(int piece_owner, int position);
	bool game_ended();

	//NEW GENERATE TEST//
	void generate_valid_actions();
	void store_if_possible(
		int board_status,
		std::pair<int, int> position_destination,
		std::pair<int, int> position_jump_destination,
		bool can_jump);
	bool jump_available(int board_status, int piece_jump_destination);
	//NEW GENERATE TEST//

	void generate_valid_moves(int & jumped_over_piece_id);
	void store_if_valid(int current_position,
		int & destination,
		int diag_move,
		int sign_of_direction,
		int & jumped_over_piece_id);

	void move_piece(int piece_id, int destination);

	std::vector<Piece> m_pieces; // this is public for the purpose of allowing main to print
	std::vector<std::pair<int, int>> m_moves_made; // see above

private:
	int m_current_player;
	int m_player_to_move;
	int m_width;
	int m_height;
	int m_number_of_turns;
	bool m_game_end;
	std::vector<int> m_board;
	std::vector<int> m_red_man_to_king_spots;
	std::vector<int> m_black_man_to_king_spots;
	std::vector<std::pair<int, int>> m_all_possible_moves_for_current_player;
	std::vector<std::pair<int, int>> m_all_possible_jumps_for_current_player;
};

#endif // !_INCLUDED_BOARD_H_