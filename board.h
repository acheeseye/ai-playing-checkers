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
#include<list>

//List of piece types
enum {
	_RED_KING_ = -2,
	_RED_MAN_ = -1,
	_BLACK_MAN_ = 1,
	_BLACK_KING_,
	_BOARDER_,
	_PLAYABLE_
};

//Directions on board
enum {
	_LEFTUP_,
	_RIGHTUP_,
	_LEFTDOWN_,
	_RIGHTDOWN_
};



class Board {
public:
	Board(int width = 8, int height = 8, int starting_player = _BLACK_); //Constructor for board

	void print_board(); //Prints board
	void print_moves_made(); //prints past moves
	void print_all_current_possible_moves();//prints all possible non jumping moves
	void print_all_current_possible_jumps();//prints all possible jumping moves

	void init_board();//initiallizes pieces
	void init_king_spots(int width);//sets places on board where piece can become king
	void clear_board();//clears board
	void update_board();
	void pass_turn();

	int get_piece_id(int position);
	int get_diag_direction(int position, int destination);

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
		int board_status_move,
		int board_status_jump,
		std::pair<int, int> position_destination,
		std::pair<int, int> position_jump_destination,
		bool can_jump,
		int diag_direction);
	bool jump_available(int board_status_jump, int board_status_move);
	//NEW GENERATE TEST//

	void generate_valid_moves(int & m_jumped_over_piece_id);
	void store_if_valid(int current_position,
		int & destination,
		int diag_move,
		int sign_of_direction,
		int & m_jumped_over_piece_id);

	void move_piece(int piece_id, int destination);

	std::vector<Piece> m_pieces; // this is public for the purpose of allowing main to print
	std::vector<std::pair<int, int>> m_moves_made; // see above

private:
	int m_current_player;
	int m_player_to_move;
	int m_width; //width of board
	int m_height; //height of board
	int m_number_of_turns;
	bool m_game_end;
	std::vector<int> m_board;
	std::vector<int> m_red_man_to_king_spots;
	std::vector<int> m_black_man_to_king_spots;
	std::vector<std::pair<int, int>> m_all_possible_moves_for_current_player;
	std::vector<std::pair<int, int>> m_all_possible_jumps_for_current_player;
	std::vector<int> m_jumped_over_piece_id;
};



//move table for temp_Board (seen below)
static const struct
{
	//-1 if not possible
	int position;
	int lmove;
	int rmove;
	int ljmp;
	int rjmp;
} move_table[32] =
{
	{ 0, 4, 5, -1, 9, },
	{ 1, 5, 6, 8, 10, },
	{ 2, 6, 7, 9, 11, },
	{ 3, 7, -1, 10, -1, },
	{ 4, -1, 8, -1, 13, },
	{ 5, 8, 9, 12, 14, },
	{ 6, 9, 10, 13, 15, },
	{ 7, 10, 11, 14, -1, },
	{ 8, 12, 13, -1, 17, },
	{ 9, 13, 14, 16, 18, },
	{ 10, 14, 15, 17, 19, },
	{ 11, 15, -1, 18, -1, },
	{ 12, -1, 16, -1, 21, },
	{ 13, 16, 17, 20, 22, },
	{ 14, 17, 18, 21, 23, },
	{ 15, 18, 19, 22, -1, },
	{ 16, 20, 21, -1, 25, },
	{ 17, 21, 22, 24, 26, },
	{ 18, 22, 23, 25, 27, },
	{ 19, 23, -1, 26, -1, },
	{ 20, -1, 24, -1, 29, },
	{ 21, 24, 25, 28, 30, },
	{ 22, 25, 26, 29, 31, },
	{ 23, 26, 27, 30, -1, },
	{ 24, 28, 29, -1, -1, },
	{ 25, 29, 30, -1, -1, },
	{ 26, 30, 31, -1, -1, },
	{ 27, 31, -1, -1, -1, },
	{ 28, -1, -1, -1, -1, },
	{ 29, -1, -1, -1, -1, },
	{ 30, -1, -1, -1, -1, },
	{ 31, -1, -1, -1, -1, }
};

//Couldn't figure out how to implement jumping using functions
//in above class so I made
class temp_Board
{
public:
	temp_Board(); //default constructor
	temp_Board(std::vector<int> board, int player);
	temp_Board(temp_Board &) = default; //copy constructor, useful for recursion
	std::vector<std::vector<int>> & generate_moves(); //generates list of moves
	bool operator==(const temp_Board &) const;
	std::vector<std::vector<int>>& get_move_list();
	void non_jump_moves();
	void jump_moves_start();
	void jump_recurse(temp_Board board_state, std::vector<int> next_move); //pass by VALUE not reference
	void move_piece(int move, bool switch_turns = true);

	bool is_over();
	int get_Player();

	void print_moves();
private:
	//Current state of the board, same as above
	std::vector<int> m_board;
	int m_current_player;
	bool m_do_jump;//member variables storing whether a jump is available

	//List of possible moves, notice that the type
	//is a list. This allows for repeated jumping to be
	//represented (i.e (24,17,8) would represent the piece
	//on 24 jumping to 17, then to 8).
	std::vector<std::vector<int>> m_possible_move_list;
public:
	void friend draw_board(const temp_Board &);
private:
	void move_from(int start, int dest);	//please do not call unless needed.
											//moves piece from start to dest
											//but may crash if not given proper values.
											//Used only because jump_recurse needed a function
											//like this to function properly.
};

#endif // !_INCLUDED_BOARD_H_