// board.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;


Board::Board(int width, int height)
{
	m_number_of_turns = 0;
	m_current_player = _P1_;
	m_player_to_move = _P1_;
	m_width = width + 4;
	m_height = height + 4;
	m_board.resize(m_width * m_height);
}

void Board::print_board()
{
	char en_man = 'b';
	char man = 'r';
	char boarder = ':';
	char playable = 'x';
	cout << "Printing Game Board..." << endl << endl;
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

void Board::init_board()
{
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

void Board::update_board()
{
	clear_board();
	for (int i = 0; i < m_pieces.size(); ++i) { // we obtain the piece infor
		int position = m_pieces[i].get_true_position();
		int owner = m_pieces[i].get_owner();
		if (owner == _P1_) {
			m_board[position] = _P1_MAN_;
		}
		else if (owner == _P2_) {
			m_board[position] = _P2_MAN_;
		}
	}
}

void Board::pass_turn()
{
	cout << "TURN HAS BEEN PASSED TO: " << m_current_player << endl;
	m_number_of_turns++;
	(m_current_player == _P1_) ?	(m_current_player = _P2_, m_player_to_move = _P2_) : 
									(m_current_player = _P1_, m_player_to_move = _P1_) ;
}

bool Board::is_boarder(int position)
{
	return m_board[position] == _BOARDER_;
}

bool Board::is_empty(int position)
{
	return false;
}

bool Board::move_piece(int piece_id, int destination)
{
	cout << "Moving piece " << piece_id << " to " << destination << "... ";
	cout << "(" << m_pieces[piece_id].get_true_position() << " " << destination << ")" << endl;
	if (m_player_to_move != m_current_player)
	{
		cout << endl << "Turn order incorrect, it is the other player's turn." << endl << endl;
		print_board();
		return false;
	}
	if (	m_board[destination] == _PLAYABLE_ &&
			(	m_pieces[piece_id].get_true_position() - m_width - 1 == destination ||
				m_pieces[piece_id].get_true_position() - m_width + 1 == destination	)
		) {
		cout << "Valid destination chosen. Piece moved." << endl << endl;
		m_pieces[piece_id].set_position(destination);
		update_board();
		print_board();
		pass_turn();
		return true;
	}
	cout << "That is an illegal destination for the selected piece. Try another piece or destination." << endl << endl;
	print_board();
	return false;
}
