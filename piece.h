// piece.h
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#ifndef _INCLUDED_PIECE_H_
#define _INCLUDED_PIECE_H_

#include <string>
//For std::string

//lower and higher in terms of the numerical value of positions,
//not positions relative to screen.
enum {
	_TOWARDS_LOWER_,
	_TOWARDS_HIGHER_,
	_BOTH_
};

class Piece {
public:
	Piece(int position, int player);
	void become_king();
	//int get_position(); //this will be reserved for if we need a clearer display of piece position
	int get_true_position();
	int get_direction();
	int get_owner();
	void set_position(int destination);
private:
	//int m_position;
	int m_owner;
	int m_true_position;
	int m_movement_direction;
	bool m_is_king;
};

#endif // !_INCLUDED_PIECE_H_
