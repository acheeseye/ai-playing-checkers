// piece.h
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

// See piece.cpp for documentation.

#ifndef _INCLUDED_PIECE_H_
#define _INCLUDED_PIECE_H_

#include <string>
//for std::string
#include <utility>
//for std::pair
#include <vector>
//for std::vector

//lower and higher in terms of the numerical value of positions,
//not positions relative to screen.
//enum {
//	_MAN_,
//	_KING_
//};

enum {
	_TOWARDS_LOWER_ = -1,
	_TOWARDS_HIGHER_ = 1,
	_BOTH_
};

enum {
	_BLACK_ = 1,
	_RED_
};

class Piece {
public:
	Piece(int position, int player, int size_of_board);

	//setters
	void set_king();
	void set_dead();
	void set_position(int destination);

	//getters
	int get_true_position();
	int get_diag_destination(int advancing_id);
	int get_jump_destination(int advancing_id);
	int get_direction();
	int get_owner();
	bool is_king();
	bool get_dead_status();

private:
	//internal private functions
	void update_diag();

	//data members
	const int m_size_of_board;
	const int m_owner;
	int m_true_position;

	std::vector<int> m_all_diag;
	std::vector<int> m_all_jump_destinations;

	bool m_alive;
	bool m_is_king;
};

#endif // !_INCLUDED_PIECE_H_
