// board.h
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

// See board.cpp for documentation.

#ifndef _INCLUDED_BOARD_H_
#define _INCLUDED_BOARD_H_

#include <SFML\Graphics.hpp>
#include <vector>
//for std::vector
#include <string>
//for std::string
#include <utility>
//for std::pair
#include <list>
#include <fstream>
// for std::ofstream
// for std::ifstream

//List of piece types
enum {
	_RED_KING_ = -2,
	_RED_MAN_ = -1,
	_BLACK_MAN_ = 1,
	_BLACK_KING_,
	_BOARDER_,
	_PLAYABLE_
};

enum {
	_RED_,
	_BLACK_
};

//Directions on board
enum {
	_LEFTUP_,
	_RIGHTUP_,
	_LEFTDOWN_,
	_RIGHTDOWN_
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
	{ 0	, 4	, 5	,-1	, 9	, },
	{ 1	, 5	, 6	, 8	, 10, },
	{ 2	, 6	, 7	, 9	, 11, },
	{ 3	, 7	, -1, 10, -1, },
	{ 4	, -1, 8	, -1, 13, },
	{ 5	, 8	, 9	, 12, 14, },
	{ 6	, 9	, 10, 13, 15, },
	{ 7	, 10, 11, 14, -1, },
	{ 8	, 12, 13, -1, 17, },
	{ 9	, 13, 14, 16, 18, },
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
	temp_Board(int starting_player); //default constructor
	temp_Board(std::vector<int> board, int player);
	temp_Board(temp_Board &) = default; //copy constructor, useful for recursion

	std::vector<std::vector<int>> & generate_moves(); //generates list of moves
	bool operator==(const temp_Board &) const;
	std::vector<std::vector<int>>& get_move_list();

	int piece_count_eval();
	std::pair<int, int> count_pieces();
	void handle_count(std::string & pieces, sf::Text & pieces_text);


	void non_jump_moves();
	void jump_moves_start();
	void jump_recurse(temp_Board board_state, std::vector<int> next_move); //pass by VALUE not reference
	void move_piece(int move, bool switch_turns = true);
	void store_move(std::vector<int> move_made);

	bool is_over();
	int get_Player();
	int get_board_status(int board_id);

	void print_moves();

	//void denote_endgame(std::string player, std::ofstream & to_file); // necessary? winner can be inferred by rewritten process_output
	void write_board_to_file(std::ofstream & to_file);

private:
	//Current state of the board, same as above
	std::vector<int> m_board;
	int m_current_player;
	bool m_do_jump;//member variables storing whether a jump is available
	std::vector<std::vector<int>> m_moves_made;

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

class Board_tree
{
public:
	Board_tree(temp_Board next_board):m_number_of_children(next_board.generate_moves().size()){}
	friend std::vector<int> min_max_search(temp_Board & current_board, int depth); //ist entry is move, 2nd is value
private:
	int m_number_of_children;
};

#endif // !_INCLUDED_BOARD_H_