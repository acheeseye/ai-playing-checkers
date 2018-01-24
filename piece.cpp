// piece.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan, 23, 2018

#include "piece.h"

Piece::Piece(int position, int player)
{
	if (player == 0) m_movement_direction = _TOWARDS_LOWER_;
	else m_movement_direction = _TOWARDS_HIGHER_;
	m_true_position = position;
	m_is_king = false;
}

void Piece::become_king()
{
	m_movement_direction = _BOTH_;
	m_is_king = true;
}

int Piece::get_true_position()
{
	return m_true_position;
}

int Piece::get_direction()
{
	return m_movement_direction;
}

void Piece::set_position(int destination)
{
	//we can have move validation checked here or on the Board object instead
	m_true_position = destination;
}
