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
#include <stdexcept>

//***********************************************************
//Functions for temp_Board
//***********************************************************
temp_Board::temp_Board(int starting_player) :m_current_player(starting_player)
{
	m_board.resize(32);
	for (int i = 0; i < 32;++i)
	{
		if (i < 12)
			m_board.at(i) = _RED_MAN_;
		else if (i >= 20)
			m_board.at(i) = _BLACK_MAN_;
		else
			m_board.at(i) = _PLAYABLE_;
	}
	m_do_jump = false;

	//populates possible move list
	generate_moves();
}

temp_Board::temp_Board(std::vector<int> board, int player)
{
	if (player != _BLACK_ && player != _RED_)
	{
		m_current_player = _BLACK_;
	}
	else
	{
		m_current_player = player;
	}
	m_board.resize(32);
	if (board.size() != 32)
		board.resize(32);
	for (int i = 0;i < 32;++i)
	{
		if (board.at(i) != _BLACK_MAN_&& board.at(i) != _RED_MAN_ && board.at(i) != _BLACK_KING_ && board.at(i) != _RED_KING_)
		{
			board.at(i) = _PLAYABLE_;
		}
		m_board.at(i) = board.at(i);
	}
	generate_moves();
}

bool temp_Board::operator==(const temp_Board & board) const
{
	bool flag = true;
	for (int i = 0;i < 32;++i)
	{
		flag &= (board.m_board == this->m_board);
	}
	return flag;
}

std::vector<std::vector<int>> & temp_Board::get_move_list()
{
	return m_possible_move_list;
}

std::vector<std::vector<int>>& temp_Board::generate_moves()
{
	m_possible_move_list.resize(0);
	//check jumps first.
	jump_moves_start();

	//if a jump is found, non jump moves aren't considered.
	if (m_do_jump)
	{
		return m_possible_move_list;
	}
	//List of non-jump moves
	non_jump_moves();
	return m_possible_move_list;
}

void temp_Board::jump_moves_start()
{
	int position, uleft, uright, dleft, dright;
	int juleft, juright, jdleft, jdright;
	m_do_jump = false;

	
	for (int i = 0;i < 32;++i)
	{
		position = m_board.at(i);
		std::vector<int> move;
		if (m_current_player == _BLACK_)
		{
			if (position != _BLACK_MAN_ && position != _BLACK_KING_)
				continue;
		}
		else
		{
			if (position != _RED_MAN_ && position != _RED_KING_)
				continue;
		}
		
		if (position == _RED_MAN_)
		{
			if (move_table[i].ljmp != -1)
			{
				jdleft = m_board.at(move_table[i].ljmp);
				dleft = m_board.at(move_table[i].lmove);
				if (jdleft == _PLAYABLE_ && (dleft == _BLACK_MAN_ || dleft == _BLACK_KING_))
				{
					m_do_jump = true;

					//
					move.push_back(i);
					move.push_back(move_table[i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[i].rjmp != -1)
			{
				jdright = m_board.at(move_table[i].rjmp);
				dright = m_board.at(move_table[i].rmove);
				if (jdright == _PLAYABLE_ && (dright == _BLACK_MAN_ || dright == _BLACK_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(move_table[i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
		}
		else if (position == _RED_KING_)
		{
			if (move_table[i].ljmp != -1)
			{
				jdleft = m_board.at(move_table[i].ljmp);
				dleft = m_board.at(move_table[i].lmove);
				if (jdleft == _PLAYABLE_ && (dleft == _BLACK_MAN_ || dleft == _BLACK_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(move_table[i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[i].rjmp != -1)
			{
				jdright = m_board.at(move_table[i].rjmp);
				dright = m_board.at(move_table[i].rmove);
				if (jdright == _PLAYABLE_ && (dright == _BLACK_MAN_ || dright == _BLACK_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(move_table[i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[31 - i].rjmp != -1)
			{
				juleft = m_board.at(31 - move_table[31 - i].rjmp);
				uleft = m_board.at(31 - move_table[31 - i].rmove);
				if (juleft == _PLAYABLE_ && (uleft == _BLACK_MAN_ || uleft == _BLACK_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[31 - i].ljmp != -1)
			{
				juright = m_board.at(31 - move_table[31 - i].ljmp);
				uright = m_board.at(31 - move_table[31 - i].lmove);
				if (juright == _PLAYABLE_ && (uright == _BLACK_MAN_ || uright == _BLACK_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
		}
		else if (position == _BLACK_MAN_)
		{
			
			if (move_table[31 - i].rjmp != -1)
			{
				juleft = m_board.at(31 - move_table[31 - i].rjmp);
				uleft = m_board.at(31 - move_table[31 - i].rmove);
				if (juleft == _PLAYABLE_ && (uleft == _RED_MAN_ || uleft == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[31 - i].ljmp != -1)
			{
				juright = m_board.at(31 - move_table[31 - i].ljmp);
				uright = m_board.at(31 - move_table[31 - i].lmove);
				if (juright == _PLAYABLE_ && (uright == _RED_MAN_ || uright == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
		}
		else
		{
			if (move_table[i].ljmp != -1)
			{
				jdleft = m_board.at(move_table[i].ljmp);
				dleft = m_board.at(move_table[i].lmove);
				if (jdleft == _PLAYABLE_ && (dleft == _RED_MAN_ || dleft == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(move_table[i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[i].rjmp != -1)
			{
				jdright = m_board.at(move_table[i].rjmp);
				dright = m_board.at(move_table[i].rmove);
				if (jdright == _PLAYABLE_ && (dright == _RED_MAN_ || dright == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(move_table[i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[31 - i].rjmp != -1)
			{
				juleft = m_board.at(31 - move_table[31 - i].rjmp);
				uleft = m_board.at(31 - move_table[31 - i].rmove);
				if (juleft == _PLAYABLE_ && (uleft == _RED_MAN_ || uleft == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].rjmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
			if (move_table[31 - i].ljmp != -1)
			{
				juright = m_board.at(31 - move_table[31 - i].ljmp);
				uright = m_board.at(31 - move_table[31 - i].lmove);
				if (juright == _PLAYABLE_ && (uright == _RED_MAN_ || uright == _RED_KING_))
				{
					m_do_jump = true;
					
					//
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].ljmp);
					jump_recurse(*this, move);
					move.pop_back();
					move.pop_back();
					//do jumping stuff
				}
			}
		}
	}
}

void temp_Board::non_jump_moves()
{
	int position, uleft, uright, dleft, dright;
	int juleft, juright, jdleft, jdright;
	for (int i = 0;i < 32; ++i)
	{
		position = m_board.at(i);
		if (m_current_player == _BLACK_)
		{
			if (position != _BLACK_MAN_ && position != _BLACK_KING_)
				continue;
		}
		else
		{
			if (position != _RED_MAN_ && position != _RED_KING_)
				continue;
		}

		if (move_table[i].lmove != -1)
		{
			dleft = m_board.at(move_table[i].lmove);
			if (position == _RED_MAN_ || position == _RED_KING_ || position == _BLACK_KING_)
			{
				if (dleft == _PLAYABLE_)
				{
					std::vector<int> move;
					move.push_back(i);
					move.push_back(move_table[i].lmove);
					m_possible_move_list.push_back(move);
				}
			}
		}
		if (move_table[i].rmove != -1)
		{
			dright = m_board.at(move_table[i].rmove);
			if (position == _RED_MAN_ || position == _RED_KING_ || position == _BLACK_KING_)
			{
				if (dright == _PLAYABLE_)
				{
					std::vector<int> move;
					move.push_back(i);
					move.push_back(move_table[i].rmove);
					m_possible_move_list.push_back(move);
				}
			}
		}
		if (move_table[31 - i].rmove != -1)
		{
			uleft = m_board.at(31 - move_table[31 - i].rmove);
			if (position == _BLACK_MAN_ || position == _RED_KING_ || position == _BLACK_KING_)
			{
				if (uleft == _PLAYABLE_)
				{
					std::vector<int> move;
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].rmove);
					m_possible_move_list.push_back(move);
				}
			}
		}
		if (move_table[31 - i].lmove != -1)
		{
			uright = m_board.at(31 - move_table[31 - i].lmove);
			if (position == _BLACK_MAN_ || position == _RED_KING_ || position == _BLACK_KING_)
			{
				if (uright == _PLAYABLE_)
				{
					std::vector<int> move;
					move.push_back(i);
					move.push_back(31 - move_table[31 - i].lmove);
					m_possible_move_list.push_back(move);
				}
			}
		}



	}
}

void temp_Board::jump_recurse(temp_Board board, std::vector<int> next_move)
{
	int position, uleft, uright, dleft, dright;
	int juleft, juright, jdleft, jdright;
	board.move_from(next_move.at(next_move.size()-2), next_move.at(next_move.size() - 1));

	int  i = next_move.at(next_move.size()-1);
	position = board.m_board.at(i);
	std::vector<int> move;
	
	bool is_leaf = true;
	if (position == _RED_MAN_)
	{
		if (move_table[i].ljmp != -1)
		{
			jdleft = board.m_board.at(move_table[i].ljmp);
			dleft = board.m_board.at(move_table[i].lmove);
			if (jdleft == _PLAYABLE_ && (dleft == _BLACK_MAN_ || dleft == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[i].rjmp != -1)
		{
			jdright = board.m_board.at(move_table[i].rjmp);
			dright = board.m_board.at(move_table[i].rmove);
			if (jdright == _PLAYABLE_ && (dright == _BLACK_MAN_ || dright == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
	}
	else if (position == _RED_KING_)
	{
		if (move_table[i].ljmp != -1)
		{
			jdleft = board.m_board.at(move_table[i].ljmp);
			dleft = board.m_board.at(move_table[i].lmove);
			if (jdleft == _PLAYABLE_ && (dleft == _BLACK_MAN_ || dleft == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[i].rjmp != -1)
		{
			jdright = board.m_board.at(move_table[i].rjmp);
			dright = board.m_board.at(move_table[i].rmove);
			if (jdright == _PLAYABLE_ && (dright == _BLACK_MAN_ || dright == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[31 - i].rjmp != -1)
		{
			juleft = board.m_board.at(31 - move_table[31 - i].rjmp);
			uleft = board.m_board.at(31 - move_table[31 - i].rmove);
			if (juleft == _PLAYABLE_ && (uleft == _BLACK_MAN_ || uleft == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[31 - i].ljmp != -1)
		{
			juright = board.m_board.at(31 - move_table[31 - i].ljmp);
			uright = board.m_board.at(31 - move_table[31 - i].lmove);
			if (juright == _PLAYABLE_ && (uright == _BLACK_MAN_ || uright == _BLACK_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
	}
	else if (position == _BLACK_MAN_)
	{

		if (move_table[31 - i].rjmp != -1)
		{
			juleft = board.m_board.at(31 - move_table[31 - i].rjmp);
			uleft = board.m_board.at(31 - move_table[31 - i].rmove);
			if (juleft == _PLAYABLE_ && (uleft == _RED_MAN_ || uleft == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[31 - i].ljmp != -1)
		{
			juright = board.m_board.at(31 - move_table[31 - i].ljmp);
			uright = board.m_board.at(31 - move_table[31 - i].lmove);
			if (juright == _PLAYABLE_ && (uright == _RED_MAN_ || uright == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
	}
	else
	{
		if (move_table[i].ljmp != -1)
		{
			jdleft = board.m_board.at(move_table[i].ljmp);
			dleft = board.m_board.at(move_table[i].lmove);
			if (jdleft == _PLAYABLE_ && (dleft == _RED_MAN_ || dleft == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[i].rjmp != -1)
		{
			jdright =board.m_board.at(move_table[i].rjmp);
			dright = board.m_board.at(move_table[i].rmove);
			if (jdright == _PLAYABLE_ && (dright == _RED_MAN_ || dright == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(move_table[i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[31 - i].rjmp != -1)
		{
			juleft = board.m_board.at(31 - move_table[31 - i].rjmp);
			uleft = board.m_board.at(31 - move_table[31 - i].rmove);
			if (juleft == _PLAYABLE_ && (uleft == _RED_MAN_ || uleft == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].rjmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
		if (move_table[31 - i].ljmp != -1)
		{
			juright = board.m_board.at(31 - move_table[31 - i].ljmp);
			uright = board.m_board.at(31 - move_table[31 - i].lmove);
			if (juright == _PLAYABLE_ && (uright == _RED_MAN_ || uright == _RED_KING_))
			{
				is_leaf = false;
				//
				next_move.push_back(31 - move_table[31 - i].ljmp);
				jump_recurse(board, next_move);
				next_move.pop_back();
				//do jumping stuff
			}
		}
	}
	if (is_leaf)
	{
		m_possible_move_list.push_back(next_move);
	}

}

void temp_Board::print_moves()
{
	for (int i = 0; i < m_possible_move_list.size();++i)
	{
		std::cout << i << ":";
		std::cout << "(";
		for (int j = 0; j < m_possible_move_list.at(i).size();++j)
		{
			if (j != 0)
				std::cout << ",";
			std::cout << m_possible_move_list.at(i).at(j);
		}
		std::cout << ")  ";
	}
	std::cout << std::endl;
}

void temp_Board::move_piece(int move_number, bool switch_turns)
{
	if (move_number<0 || move_number>= m_possible_move_list.size())
		return;
	std::vector<int> moves = m_possible_move_list.at(move_number);
	int start;
	int des;
	for (int i = 0;i < moves.size()-1; ++i)
	{
		start = moves.at(i);
		des = moves.at(i + 1);
		if (!m_do_jump)
		{
			int piece = m_board.at(start);
			m_board.at(start) = _PLAYABLE_;
			m_board.at(des) = piece;
		}
		else
		{
			int piece = m_board.at(start);
			m_board.at(start) = _PLAYABLE_;
			m_board.at(des) = piece;

			if (des < start)
			{
				std::swap(start, des);
			}

			if (move_table[start].ljmp == des)
			{
				m_board.at(move_table[start].lmove) = _PLAYABLE_;
			}
			else
			{
				m_board.at(move_table[start].rmove) = _PLAYABLE_;
			}

		}
		

	}
		
	if (m_current_player == _BLACK_)
	{
		for (int i = 0; i < 4;++i)
		{
			if (m_board.at(i) == _BLACK_MAN_)
			{
				m_board.at(i) = _BLACK_KING_;
			}
		}
		if(switch_turns)
			m_current_player = _RED_;
	}
	else
	{
		for (int i = 28; i < 32;++i)
		{
			if (m_board.at(i) == _RED_MAN_)
			{
				m_board.at(i) = _RED_KING_;
			}
		}
		if (switch_turns)
			m_current_player = _BLACK_;
	}
	// repopulates move list
	generate_moves();
}

void temp_Board::store_move(std::vector<int> move_made)
{
	m_moves_made.push_back(move_made);
}

void temp_Board::move_from(int start, int dest)
{
		if (!m_do_jump)
		{
			int piece = m_board.at(start);
			m_board.at(start) = _PLAYABLE_;
			m_board.at(dest) = piece;
		}
		else
		{
			int piece = m_board.at(start);
			m_board.at(start) = _PLAYABLE_;
			m_board.at(dest) = piece;

			if (dest < start)
			{
				std::swap(start, dest);
			}

			if (move_table[start].ljmp == dest)
			{
				m_board.at(move_table[start].lmove) = _PLAYABLE_;
			}
			else
			{
				m_board.at(move_table[start].rmove) = _PLAYABLE_;
			}

		}


	//if (m_current_player == _BLACK_)
	//{
	//	for (int i = 0; i < 4;++i)
	//	{
	//		if (m_board.at(i) == _BLACK_MAN_)
	//		{
	//			m_board.at(i) = _BLACK_KING_;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int i = 28; i < 32;++i)
	//	{
	//		if (m_board.at(i) == _RED_MAN_)
	//		{
	//			m_board.at(i) = _RED_KING_;
	//		}
	//	}
	//}
}

int temp_Board::get_Player() { return m_current_player; }

int temp_Board::get_board_status(int board_id)
{
	return m_board.at(board_id);
}

bool temp_Board::is_over() { return (m_possible_move_list.size() == 0); }

void draw_board(const temp_Board & board)
{
	for (int row = -2; row < 10; ++row) {
		for (int col = -1; col < 5; ++col) {
			if (row < 0 || row >= 8||col<0||col>=4)
			{
				std::cout << ": : ";
				continue;
			}else if (board.m_board[row * 4 + col] == _BLACK_MAN_)
			{
				if (row % 2 == 0)
					std::cout << "  " << "b ";
				else
					std::cout << "b " << "  ";
			}
			else if (board.m_board[row * 4 + col] == _BLACK_KING_)
			{
				if (row % 2 == 0)
					std::cout << "  " << "B ";
				else
					std::cout << "B " << "  ";
			}
			else if (board.m_board[row * 4 + col] == _RED_MAN_)
			{
				if (row % 2 == 0)
					std::cout << "  " << "r ";
				else
					std::cout << "r " << "  ";
			}
			else if (board.m_board[row * 4 + col] == _RED_KING_)
			{
				if (row % 2 == 0)
					std::cout << "  " << "R ";
				else
					std::cout << "R " << "  ";
			}
			else
			{
				if (row % 2 == 0)
					std::cout << "  " << "x ";
				else
					std::cout << "x " << "  ";
			}
		}
		cout << endl;
	}
}