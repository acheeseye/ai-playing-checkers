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
	char red_man = 'r';
	char red_king = 'R';
	char black_man = 'b';
	char black_king = 'B';
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
				cout << red_man;
				break;
			case _RED_KING_:
				cout << red_king;
				break;
			case _BLACK_MAN_:
				cout << black_man;
				break;
			case _BLACK_KING_:
				cout << black_king;
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
		cout << n.first << " " << n.second << " "; //this is format for copy pasting
		//cout << "(" << n.first << ", " << n.second << ")" << endl;
	}
	cout << endl;
}


void Board::print_all_current_possible_moves()
{
	//m_all_possible_moves_for_current_player.clear();
	//m_all_possible_jumps_for_current_player.clear();
	//generate_valid_actions();
	if (m_all_possible_moves_for_current_player.size() == 0) {
		cout << "No possible moves generated!" << endl;
		//m_game_end = true;
		return;
	}
	cout << "Possible moves:" << endl;
	for (auto n : m_all_possible_moves_for_current_player) {
		cout << "(" << n.first << "," << n.second << ") ";
	}
	//m_all_possible_moves_for_current_player.clear();
	//m_all_possible_jumps_for_current_player.clear();
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
	//m_all_possible_moves_for_current_player.clear();
	//m_all_possible_jumps_for_current_player.clear();
	//generate_valid_actions();
	if (m_all_possible_jumps_for_current_player.size() == 0) {
		cout << "No possible jumps generated!" << endl;
		//m_game_end = true;
		return;
	}
	cout << "Possible jumps:" << endl;
	for (auto n : m_all_possible_jumps_for_current_player) {
		cout << "(" << n.first << "," << n.second << ") ";
	}
	//m_all_possible_moves_for_current_player.clear();
	//m_all_possible_jumps_for_current_player.clear();
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
	for (int row = 0; row < m_height; ++row) {
		for (int col = 0; col < m_width; ++col) {
			int index = row * m_width + col;
			if ((row <= 1 || row >= m_height - 2) ||
				(col <= 1 || col >= m_width - 2)) {
				m_board[index] = _BOARDER_;
			}
			else {
				if (row % 2 == 1 && col % 2 == 0 ||
					row % 2 == 0 && col % 2 == 1) {
					m_board[index] = _PLAYABLE_;
				}
				if (row < m_height / 2 - 1 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _RED_MAN_;
					Piece p2_piece(index, _RED_, m_width);
					m_pieces.push_back(p2_piece);
				}
				else if (row > m_height / 2 && m_board[index] == _PLAYABLE_) {
					m_board[index] = _BLACK_MAN_;
					Piece p1_piece(index, _BLACK_, m_width);
					m_pieces.push_back(p1_piece);
				}
			}
		}
	}
	int invalid_id = (int)m_pieces.size();
	m_jumped_over_piece_id = { invalid_id, invalid_id, invalid_id, invalid_id };
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
		bool king_status = m_pieces[i].is_king();
		if (eliminated) {
			m_board.push_back(_PLAYABLE_);
			position = m_board.size() + 1;
		}
		else if (owner == _BLACK_) {
			cout << "piece_id: " << i << " blk" << endl;
			if (m_pieces[i].is_king()) {
				m_board[position] = _BLACK_KING_;
			}
			else if(is_king_transformer(_BLACK_, position)) {
				m_pieces[i].set_king();
				m_board[position] = _BLACK_KING_;
			}
			else {
				m_board[position] = _BLACK_MAN_;
			}
		}
		else if (owner == _RED_) {
			cout << "piece_id: " << i << " ";
			if (m_pieces[i].is_king()) {
				cout << "already red king, setting board at position as red king." << endl;
				m_board[position] = _RED_KING_;
			}
			else if (is_king_transformer(_RED_, position)) {
				cout << "red man landed on king transformer spot, transforming and setting board at position as red king." << endl;
				m_pieces[i].set_king();
				m_board[position] = _RED_KING_;
			}
			else {
				cout << "red man detected." << endl;
				m_board[position] = _RED_MAN_;
			}
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
	(m_current_player == _BLACK_) ? (m_current_player = _RED_, m_player_to_move = _RED_) :
		(m_current_player = _BLACK_, m_player_to_move = _BLACK_);
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

int Board::get_diag_direction(int position, int destination)
{
	//cout << "calculating diag direction of: " << position << " " << destination << endl;
	int piece_id = get_piece_id(position);
	int diag_direction = -1;
	//vector<int> all_diag = m_pieces[piece_id].get_all_diag();
	vector<int> all_diag_jump = m_pieces[piece_id].get_all_jump_destiations();
	auto it = find(all_diag_jump.begin(), all_diag_jump.end(), destination);
	if (it != all_diag_jump.end()) {
		diag_direction = it - all_diag_jump.begin();
	}
	return diag_direction;
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
	auto it = find(m_all_possible_moves_for_current_player.begin(),
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

void Board::generate_valid_actions()
{
	//GENERATE ALL MOVES ONE PIECE AT A TIME//	
	int starting_id, ending_id;
	(m_current_player == _BLACK_) ? (starting_id = 12) : (starting_id = 0);
	ending_id = starting_id + 12;
	for (size_t piece_id = starting_id; piece_id < ending_id; ++piece_id) {
		if (m_pieces[piece_id].get_dead_status()) {
			continue;
		}
		int piece_position = m_pieces[piece_id].get_true_position();
		int piece_direction = m_pieces[piece_id].get_direction();
		bool piece_is_king = m_pieces[piece_id].is_king();
		//cout << "piece info: " << piece_position << " dir: " << piece_direction << " king: " << piece_is_king << endl;
		//_LEFTUP_ == 0, _RIGHTDOWN_ == 3
		for (size_t advancing_destination = _LEFTUP_; advancing_destination <= _RIGHTDOWN_; ++advancing_destination) {
			int piece_destination = m_pieces[piece_id].get_diag_destination(advancing_destination);
			int piece_jump_destination = m_pieces[piece_id].get_jump_destination(advancing_destination);
			int board_status_move = m_board[piece_destination];
			int board_status_jump = m_board[piece_jump_destination];

			bool can_jump = jump_available(board_status_jump, board_status_move);

			pair<int, int> position_destination = make_pair(piece_position, piece_destination);
			pair<int, int> position_jump_destination = make_pair(piece_position, piece_jump_destination);

			if (piece_is_king) {
				store_if_possible(board_status_move, board_status_jump, position_destination, position_jump_destination, can_jump, advancing_destination);
			}
			else {
				if (piece_direction == _TOWARDS_LOWER_) {
					//cout << "	dest: " << piece_destination << " dest stat: " << board_status_move;
					//cout << " jump: " << piece_jump_destination << " jump stat: " << board_status_jump << endl;
					if (advancing_destination == _LEFTUP_ || advancing_destination == _RIGHTUP_) {
						store_if_possible(board_status_move, board_status_jump, position_destination, position_jump_destination, can_jump, advancing_destination);
					}
				}
				else if (piece_direction == _TOWARDS_HIGHER_) {
					//cout << "	dest: " << piece_destination << " dest stat: " << board_status_move;
					//cout << " jump: " << piece_jump_destination << " jump stat: " << board_status_jump << endl;
					if (advancing_destination == _LEFTDOWN_ || advancing_destination == _RIGHTDOWN_) {
						store_if_possible(board_status_move, board_status_jump, position_destination, position_jump_destination, can_jump, advancing_destination);
					}
				}
			}
		}
	}
}

void Board::store_if_possible(
	int board_status_move, 
	int board_status_jump, 
	std::pair<int, int> position_destination, 
	std::pair<int, int> position_jump_destination, 
	bool can_jump,
	int diag_direction)
{
	if (can_jump) {
		m_jumped_over_piece_id[diag_direction] = get_piece_id(position_destination.second);
		//cout << "jumped_over_id: " << m_jumped_over_piece_id[diag_direction] << endl;
		m_all_possible_jumps_for_current_player.push_back(position_jump_destination);
		//cout << "		JUMP action stored" << endl;
		return;
	}
	if (board_status_move == _PLAYABLE_) {
		m_all_possible_moves_for_current_player.push_back(position_destination);
		//cout << "		MOVE action stored" << endl;
		return;
	}
	//cout << "		move not stored" << endl;
	return;
}

bool Board::jump_available(int board_status_jump, int board_status_move)
{
	//cout << (board_status_jump == _RED_MAN_) << (board_status_jump == _RED_KING_) << (m_board[piece_jump_destination] == _PLAYABLE_) << endl;
	if (m_current_player == _BLACK_) {
		//m_jumped_over_piece_id
		return ((
			board_status_move == _RED_MAN_ ||
			board_status_move == _RED_KING_) &&
			board_status_jump == _PLAYABLE_);
	}
	else {
		return ((
			board_status_move == _BLACK_MAN_ ||
			board_status_move == _BLACK_KING_) &&
			board_status_jump == _PLAYABLE_);
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
	//m_jumped_over_piece_id = (int)m_pieces.size();

	if (!ownership_check(current_piece_id))
	{
		cout << "Selected piece does not belong to current player. Try again." << endl;
		return;
	}

	//generate_valid_moves(m_jumped_over_piece_id);
	generate_valid_actions();

	print_all_current_possible_jumps();
	print_all_current_possible_moves();

	pair<int, int> attempted_move = make_pair(current_position, destination);
	int diag_direction = get_diag_direction(current_position, destination);

	cout << "Moving piece " << attempted_move.first << " to " << attempted_move.second << "... (jump size: " << m_all_possible_jumps_for_current_player.size() << ")" << endl;
	if (m_all_possible_jumps_for_current_player.size() != 0 &&
		is_valid_jump(attempted_move)) {
		int j_piece_id = m_jumped_over_piece_id[diag_direction];
		m_pieces[j_piece_id].set_dead();
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
		return;
	}

	cout << "That is an illegal destination for the selected piece. Try another piece or destination." << endl;
}