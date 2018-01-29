// piece.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "piece.h"

#include <iostream>
using std::cout;
using std::endl;

//************
//************
// Two paramemter Piece object constructor
//		Constructs the Piece object.
//************
//************
Piece::Piece(int position, int owner, int size_of_board) :
	m_size_of_board(size_of_board),
	m_owner(owner),
	m_true_position(position),
	m_alive(true),
	m_is_king(false)
{
	m_all_diag.resize(4);
	m_all_jump_destinations.resize(4);
	update_diag();
}

//************
//************
// set_king
//		Not yet tested.
//************
//************
void Piece::set_king()
{
	cout << "Piece::set_king triggered." << endl;
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

int Piece::get_diag_destination(int advancing_id)
{
	return m_all_diag[advancing_id];
}

int Piece::get_jump_destination(int advancing_id)
{
	return m_all_jump_destinations[advancing_id];
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
	if (m_is_king) return _BOTH_;
	else if (m_owner == _BLACK_) return _TOWARDS_LOWER_;
	else return _TOWARDS_HIGHER_;
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

bool Piece::is_king()
{
	return m_is_king;
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
	update_diag();
}

void Piece::update_diag()
{
	int left_up = m_true_position - m_size_of_board - 1;
	int right_up = m_true_position - m_size_of_board + 1;
	int left_down = m_true_position + m_size_of_board - 1;
	int right_down = m_true_position + m_size_of_board + 1;

	int left_up_jump = left_up - m_size_of_board - 1;
	int right_up_jump = right_up - m_size_of_board + 1;
	int left_down_jump = left_down + m_size_of_board - 1;
	int right_down_jump = right_down + m_size_of_board + 1;


	m_all_diag[0] = left_up;
	m_all_diag[1] = right_up;
	m_all_diag[2] = left_down;
	m_all_diag[3] = right_down;

	m_all_jump_destinations[0] = left_up_jump;
	m_all_jump_destinations[1] = right_up_jump;
	m_all_jump_destinations[2] = left_down_jump;
	m_all_jump_destinations[3] = right_down_jump;
}
