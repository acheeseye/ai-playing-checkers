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

//lower and higher in terms of the numerical value of positions,
//not positions relative to screen.
enum {
	_TOWARDS_LOWER_ = -1,
	_TOWARDS_HIGHER_ = 1,
	_BOTH_
};

class Piece {
public:
	Piece(int position, int player);
	void set_king();
	void set_dead();
	//int get_position(); //this will be reserved for if we need a clearer display of piece position
	int get_true_position();
	int get_direction();
	int get_owner();
	bool get_dead_status();
	void set_position(int destination);

	//bool operator==(const Piece & rhs);
private:
	//int m_position;
	int m_owner;
	int m_true_position;
	int m_movement_direction;
	bool m_alive;
	bool m_is_king;
};

#endif // !_INCLUDED_PIECE_H_
