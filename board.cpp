// board.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"

#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
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
Board::Board(int width, int height, int starting_player)
{
	int boarder_size = 2;
	m_game_end = false;
	m_number_of_turns = 0;
	m_current_player = starting_player;
	m_player_to_move = starting_player;
	m_width = width + boarder_size * 2;
	m_height = height + boarder_size * 2;
	m_board.resize(m_width * m_height);
	init_board();
	init_king_spots(width);
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
	char en_man = 'r';
	char man = 'b';
	char boarder = ':';
	char playable = 'x';
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			switch (m_board[index]) {
			case _BOARDER_:
				cout << boarder;
				break;
			case _RED_MAN_:
				cout << en_man;
				break;
			case _BLACK_MAN_:
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
}

//************
//************
// print_moves_made
//		Prints corresponding data member.
//************
//************
void Board::print_moves_made()
{
	if (m_moves_made.size() == 0) {
		cout << "No moves made yet!" << endl;
	}
	for (auto n : m_moves_made) {
		//cout << n.first << " " << n.second << " "; //this is format for copy pasting
		cout << "(" << n.first << ", " << n.second << ")" << endl;
	}
	cout << endl;
}


void Board::print_all_current_possible_moves()
{
	if (m_all_possible_moves_for_current_player.size() == 0) {
		cout << "No possible moves generated!" << endl;
		m_game_end = true;
	}
	cout << "Possible moves:" << endl;
	for (auto n : m_all_possible_moves_for_current_player) {
		cout << "(" << n.first << "," << n.second << ") ";
	}
	cout << endl;
}

//************
//************
// print_all_current_possible_jumps()
//		Prints corresponding data member.
//************
//************
void Board::print_all_current_possible_jumps()
{
	if (m_all_possible_moves_for_current_player.size() == 0) {
		cout << "No possible jumps generated!" << endl;
		m_game_end = true;
	}
	cout << "Possible jumps:" << endl;
	for (auto n : m_all_possible_jumps_for_current_player) {
		cout << "(" << n.first << "," << n.second << ") ";
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
					m_board[index] = _RED_MAN_;
					Piece p2_piece(index, _RED_);
					m_pieces.push_back(p2_piece);
				}
				else if (row > m_height / 2 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _BLACK_MAN_;
					Piece p1_piece(index, _BLACK_);
					m_pieces.push_back(p1_piece);
				}
			}
		}
	}
}

//************
//************
// init_king_spots
//		Used to store end of board spots (king transformation spots) in
//		data members.
//************
//************
void Board::init_king_spots(int width)
{
	int pieces_per_row = width / 2;
	for (int i = 0; i < pieces_per_row; ++i) {
		m_black_man_to_king_spots.push_back(m_pieces[i].get_true_position());
	}
	for (int i = (int)m_pieces.size() - pieces_per_row; i < (int)m_pieces.size(); ++i) {
		m_red_man_to_king_spots.push_back(m_pieces[i].get_true_position());
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
			m_board.push_back(_PLAYABLE_);
			position = m_board.size() + 1;
		}
		else if (owner == _BLACK_) {
			if (is_king_transformer(_BLACK_, position)) {
				m_pieces[i].set_king();
			}
			m_board[position] = _BLACK_MAN_;
		}
		else if (owner == _RED_) {
			if (is_king_transformer(_RED_, position)) {
				m_pieces[i].set_king();
			}
			m_board[position] = _RED_MAN_;
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
	(m_current_player == _BLACK_) ?	(m_current_player = _RED_, m_player_to_move = _RED_) : 
									(m_current_player = _BLACK_, m_player_to_move = _BLACK_) ;
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
		cout << "FATAL ERROR: TRIED TO RETRIEVE A NON EXISTANT PIECE DURING A JUMP (Board::get_piece_id)" << endl;
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
// ownership_check
//		This function checks if the selected piece
//		belongs to the current player.
//************
//************
bool Board::ownership_check(int piece_id)
{
	return ((piece_id < 12 && m_current_player == _RED_) || (piece_id >= 12 && m_current_player == _BLACK_));
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
// is_valid_move
//		Finds if the attempted move is stored in data member.
//************
//************
bool Board::is_valid_move(std::pair<int, int> attempted_move)
{
	auto it = find(	m_all_possible_moves_for_current_player.begin(),
					m_all_possible_moves_for_current_player.end(),
					attempted_move);
	return it != m_all_possible_moves_for_current_player.end();
}

//************
//************
// is_valid_jump
//		Finds if the attempted jump is stored in data member.
//************
//************
bool Board::is_valid_jump(std::pair<int, int> attempted_move)
{
	auto it = find(m_all_possible_jumps_for_current_player.begin(),
		m_all_possible_jumps_for_current_player.end(),
		attempted_move);
	return it != m_all_possible_jumps_for_current_player.end();
}

//************
//************
// is_king_transformer
//		Checks if the piece is on the other end to be transformed.
//************
//************
bool Board::is_king_transformer(int piece_owner, int position)
{
	if (piece_owner == _RED_) {
		auto it = find(m_red_man_to_king_spots.begin(),
			m_red_man_to_king_spots.end(),
			position);
		return it != m_red_man_to_king_spots.end();
	}
	else {
		auto it = find(m_black_man_to_king_spots.begin(),
			m_black_man_to_king_spots.end(),
			position);
		return it != m_black_man_to_king_spots.end();
	}
	return false;
}

//************
//************
// game_ended
//		Returns true if game ended. Used for console input.
//************
//************
bool Board::game_ended()
{
	return m_game_end;
}

//************
//************
// generate_valid_moves
//		Generates all possible moves for all possible pieces.
//		Result is stored in m_all_possible_xxxxx_for_current_player.
//		The passed in jumped_over_piece_id returns < m_board.size() if
//		a jump is made.
//************
//************
void Board::generate_valid_moves(int & jumped_over_piece_id)
{
	int starting_id;
	(m_current_player == _BLACK_) ? (starting_id = 12) : (starting_id = 0);
	int ending_id = starting_id + m_pieces.size() / 2;
	for (int i = starting_id; i < ending_id; ++i) {
		if (m_pieces[i].get_dead_status()) {
			continue;
		}
		int sign_of_direction = m_pieces[i].get_direction();
		int current_piece_position = m_pieces[i].get_true_position();
		//left and right is relative to player one
		int diag_left = (sign_of_direction * m_width) - 1;
		int diag_right = (sign_of_direction * m_width) + 1;
		int left_advance = current_piece_position + diag_left;
		int right_advance = current_piece_position + diag_right;
		//these only work for men at the moment
		store_if_valid(current_piece_position, left_advance, diag_left, sign_of_direction, jumped_over_piece_id);
		store_if_valid(current_piece_position, right_advance, diag_right, sign_of_direction, jumped_over_piece_id);
	}
}

//************
//************
// store_if_valid
//		Helper function to determine if move to be stored is a move or jump.
//************
//************
void Board::store_if_valid(	int current_piece_position, 
							int & destination, 
							int diag_move, 
							int sign_of_direction,
							int & jumped_over_piece_id)
{
	pair<int, int> tmp_move_holder;
	if (abs(m_board[destination]) <= 2 &&
		signbit((float)m_board[destination]) == signbit((float)sign_of_direction) &&
		m_board[destination + diag_move] == _PLAYABLE_) {
		jumped_over_piece_id = get_piece_id(destination);
		destination += diag_move;
		pair<int, int> tmp_move_holder = make_pair(current_piece_position, destination);
		m_all_possible_jumps_for_current_player.push_back(tmp_move_holder);
	}
	if (m_board[destination] == _PLAYABLE_) {
		tmp_move_holder = make_pair(current_piece_position, destination);
		m_all_possible_moves_for_current_player.push_back(tmp_move_holder);
	}
}

//************
//************
// move_piece
//		TODO: might only need to have return type of void
//		This function combines other functions to move pieces
//		validly.
//************
//************
void Board::move_piece(int current_position, int destination)
{
	m_all_possible_moves_for_current_player.clear();
	m_all_possible_jumps_for_current_player.clear();
	int current_piece_id = get_piece_id(current_position);
	int jumped_over_piece_id = (int)m_pieces.size();

	if (!ownership_check(current_piece_id))
	{
		cout << "Selected piece does not belong to current player. Try again." << endl;
		return;
	}

	generate_valid_moves(jumped_over_piece_id);
	pair<int, int> attempted_move = make_pair(current_position, destination);
	cout << "Moving piece " << attempted_move.first << " to " << attempted_move.second << "... ";

	if (m_all_possible_jumps_for_current_player.size() != 0 && 
		is_valid_jump(attempted_move)) {
		cout << "valid jump attempted" << endl;
		m_pieces[jumped_over_piece_id].set_dead();
		m_moves_made.push_back(attempted_move);
		m_pieces[current_piece_id].set_position(destination);
		update_board();
		print_board();
		pass_turn();
		return;
	}

	if (m_all_possible_jumps_for_current_player.size() == 0 &&
		is_valid_move(attempted_move)) {
		cout << "Valid destination chosen for the selected piece. Piece moved to ";
		cout << attempted_move.second << endl;
		m_moves_made.push_back(attempted_move);
		m_pieces[current_piece_id].set_position(destination);
		update_board();
		print_board();
		pass_turn();
		//int dummy = 0;
		//generate_valid_moves(dummy);
		//print_all_current_possible_moves();
		return;
	}

	cout << "That is an illegal destination for the selected piece. Try another piece or destination." << endl;
	//return false;
}
