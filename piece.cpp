// piece.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "piece.h"

//************
//************
// Two paramemter Piece object constructor
//		Constructs the Piece object.
//************
//************
Piece::Piece(int position, int owner)
{
	m_alive = true;
	m_owner = owner;
	m_true_position = position;
	m_is_king = false;
	if (owner == 1 ) m_movement_direction = _TOWARDS_LOWER_;
	else m_movement_direction = _TOWARDS_HIGHER_;
}

//************
//************
// set_king
//		Not yet tested.
//************
//************
void Piece::set_king()
{
	m_movement_direction = _BOTH_;
	m_is_king = true;
}

//************
//************
// set_dead
//		A piece is pronounced dead when it is jumped over.
//************
//************
void Piece::set_dead()
{
	m_alive = false;
	m_true_position = 0;
}

//************
//************
// get_true_position
//		Returns the position with regards to 0 being top left
//		and incrementing right.
//************
//************
int Piece::get_true_position()
{
	return m_true_position;
}

//************
//************
// get_direction
//		Returns direction of the piece; tactically declared
//		so that it may be (is) used to reduce duplicate code
//		(-1 for player 1, since moving up -> toward lower number
//		 1 for player 2, since moving down -> towards higher number
//		 2 or 0 for pieces that are kings -> not dealt with yet)
//************
//************
int Piece::get_direction()
{
	return m_movement_direction;
}

//************
//************
// get_owner
//		Returns information about who owns the piece. Used
//		for Board::ownership_check.
//************
//************
int Piece::get_owner()
{
	return m_owner;
}

//************
//************
// get_dead_status
//		Returns true if not alive (!m_alive). Used to allow
//		Board::update_board to determine when a piece no
//		longer is in play.
//************
//************
bool Piece::get_dead_status()
{
	return !m_alive;
}

//************
//************
// set_position
//		Sets position of the piece. Used for Board::move_piece.
//************
//************
void Piece::set_position(int destination)
{
	m_true_position = destination;
}
