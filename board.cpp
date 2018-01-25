// board.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"

#include <vector>
using std::vector;
#include <cmath>
using std::signbit;
#include <algorithm>
using std::find;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

//************
//************
// Two-parameter constructor for Board object
//		Initiate data members and calls init_board.
//************
//************
Board::Board(int width, int height)
{
	m_number_of_turns = 0;
	m_current_player = _P1_;
	m_player_to_move = _P1_;
	m_width = width + 4;
	m_height = height + 4;
	m_board.resize(m_width * m_height);
	init_board();
}

//************
//************
// print_board
//		Print board in the current state according to
//		enumerated values listed in board.h.
//		This print does not print inaccessable spaces.
//************
//************
void Board::print_board()
{
	char en_man = 'b';
	char man = 'r';
	char boarder = ':';
	char playable = 'x';
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			//switch may be commented out to print raw enumerated values
			//(just print m_board[...])
			switch (m_board[index]) {
			case _BOARDER_:
				cout << boarder;
				break;
			case _P2_MAN_:
				cout << en_man;
				break;
			case _P1_MAN_:
				cout << man;
				break;
			case _PLAYABLE_:
				cout << playable;
				break;
			default:
				cout << ' ';
				break;
			}
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

//************
//************
// init_board
//		Fills m_board with initial board values.
//************
//************
void Board::init_board()
{
	cout << "Initiating board..." << endl;
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			if (	(row <= 1 || row >= m_height - 2)	|| 
					(col <= 1 || col >= m_width - 2)	) {
				m_board[index] = _BOARDER_;
			}
			else {
				if (row % 2 == 1 && col % 2 == 0 ||
					row % 2 == 0 && col % 2 == 1) {
					m_board[index] = _PLAYABLE_;
				}
				if (row < m_height / 2 - 1 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _P2_MAN_;
					Piece p2_piece(index, _P2_);
					m_pieces.push_back(p2_piece);
				}
				else if (row > m_height / 2 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _P1_MAN_;
					Piece p1_piece(index, _P1_);
					m_pieces.push_back(p1_piece);
				}
			}
		}
	}
}

//************
//************
// clear_board
//		Wipes all pieces off the board and replaces with _PLAYABLE_.
//		This was done to assist in update_board because it held onto
//		previous positions of moved pieces.
//************
//************
void Board::clear_board()
{
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			if (!is_boarder(index) &&
				(row % 2 == 1 && col % 2 == 0 ||
					row % 2 == 0 && col % 2 == 1)
				) {
				m_board[index] = _PLAYABLE_;
			}
		}
	}
}

//************
//************
// update_board
//		Iterates through all existing pieces and assigns m_board
//		values accordingly.
//************
//************
void Board::update_board()
{
	clear_board();
	for (int i = 0; i < m_pieces.size(); ++i) {

		int position = m_pieces[i].get_true_position();
		int owner = m_pieces[i].get_owner();
		bool eliminated = m_pieces[i].get_dead_status();

		if (eliminated) {
			m_board[position] = _PLAYABLE_;
		}
		else if (owner == _P1_) {
			m_board[position] = _P1_MAN_;
		}
		else if (owner == _P2_) {
			m_board[position] = _P2_MAN_;
		}
	}
}

//************
//************
// pass_turn
//		Passes the turn.
//************
//************
void Board::pass_turn()
{
	m_number_of_turns++;
	(m_current_player == _P1_) ?	(m_current_player = _P2_, m_player_to_move = _P2_) : 
									(m_current_player = _P1_, m_player_to_move = _P1_) ;
	cout << "Turn has been passed to: player " << m_current_player << endl;
	cout << "Turns elapsed: " << m_number_of_turns << endl;
}

//************
//************
// get_piece_id
//		Gets the piece_id of a Piece object located at position
//		if a piece exists there.
//************
//************
int Board::get_piece_id(int position)
{
	if (is_empty(position)) {
		return 0;
	}
	int piece_id = 0;
	vector<int> storage;
	vector<int>::iterator it;
	for (auto n : m_pieces) {
		storage.push_back(n.get_true_position());
	}
	it = find(storage.begin(), storage.end(), position);
	piece_id = it - storage.begin();
	return piece_id;
}

//************
//************
// valid_man_move
//		Returns true if the position being moved ONTO will either be a
//		simple move or jump.
//		For a piece to jump, it must move ONTO the enemy piece, instead
//		of where it actually would go. The destination is automatically
//		updated (subject to change if needed).
//************
//************
bool Board::valid_man_move(int piece_id, int player, int & destination)
{
	if (m_pieces[piece_id].get_true_position() == destination) {
		return false;
	}
	//variable declaration for cleaner if statements
	//left and right is relative to player one
	int sign_of_direction = m_pieces[piece_id].get_direction();
	int diag_left = (sign_of_direction * m_width) - 1;
	int diag_right = (sign_of_direction * m_width) + 1;
	int left_advance = m_pieces[piece_id].get_true_position() + diag_left;
	int right_advance = m_pieces[piece_id].get_true_position() + diag_right;

	//check for jumps first
	if(abs(m_board[destination]) <= 2) //playable pieces are -2, -1, 1, and 2
	{
		//this is wonky, sorry.
		//the condition returns true if the piece considered to move on contains an enemy piece
		//logically the comparing operator should be !=, but some how == gives the correct result
		if (signbit((float)m_board[destination]) == signbit((float)sign_of_direction)) {

			//TODO: code duplication ish, maybe fix later
			if (left_advance == destination && is_empty(destination + diag_left)) {
				int eliminated_piece_id = get_piece_id(destination);
				m_pieces[eliminated_piece_id].set_dead();
				destination += diag_left;
				return true;
			}
			if (right_advance == destination && is_empty(destination + diag_right)) {
				int eliminated_piece_id = get_piece_id(destination);
				m_pieces[eliminated_piece_id].set_dead();
				destination += diag_right;
				return true;
			}
		}
	}
	//TODO: needs to include king movement (might be a new function valid_king_move)
	if (m_board[destination] == _PLAYABLE_) {
		return (left_advance == destination || right_advance == destination);
	}

	return false;
}

//************
//************
// ownership_check
//		This function allows players to have ownership over
//		their pieces; player cannot move pieces that do not
//		belong to them.
//************
//************
bool Board::ownership_check(int piece_id, int player)
{
	return ((piece_id < 12 && player == _P2_) || (piece_id >= 12 && player == _P1_));
}

//************
//************
// is_boarder
//		Returnes true if position asked for contains boarder.
//************
//************
bool Board::is_boarder(int position)
{
	return m_board[position] == _BOARDER_;
}

//************
//************
// is_empty
//		Returns true if position asked for is empty.
//************
//************
bool Board::is_empty(int position)
{
	return m_board[position] == _PLAYABLE_;
}

//************
//************
// move_piece
//		TODO: might only need to have return type of void
//		This function combines other functions to move pieces
//		validly.
//************
//************
bool Board::move_piece(int piece_id, int destination)
{
	cout << "Moving piece " << piece_id << " to " << destination << "... ";
	cout << "(" << m_pieces[piece_id].get_true_position() << " " << destination << ")" << endl;

	if (!ownership_check(piece_id, m_current_player))
	{
		cout << "Selected piece does not belong to current player. Try again." << endl;
		//print_board();
		return false;
	}

	if (valid_man_move(piece_id, m_current_player, destination)) {
		cout << "Valid destination chosen for the selected piece. Piece moved." << endl;
		m_pieces[piece_id].set_position(destination);
		update_board();
		print_board();
		pass_turn();
		return true;
	}

	cout << "That is an illegal destination for the selected piece. Try another piece or destination." << endl;
	//print_board();
	return false;
}
