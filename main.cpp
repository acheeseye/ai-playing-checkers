// main.cpp
// CS 405/605 Introduction to AI Spring 2018
// AI Playing Checkers Project
// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
// Created Jan 23, 2018

#include "board.h"
#include <random>
#include <time.h>
#include <SFML\Graphics.hpp>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::to_string;

int mouse_selected_index_converter(int mouse_selected_index, int mouse_index_x, int mouse_index_y)
{
	int return_index = 33;
	if (mouse_selected_index % 2 == 1 &&
		mouse_index_x % 2 == 1 &&
		mouse_index_y % 2 == 0 &&
		mouse_index_x < 8)
		return (mouse_selected_index - 1) / 2;
	else if (mouse_selected_index % 2 == 0 &&
		mouse_index_x % 2 == 0 &&
		mouse_index_y % 2 == 1 &&
		mouse_index_x < 8)
		return (mouse_selected_index / 2);
	else
		return return_index;
}

int main() {

	//Game of checkers using temp_Board
	temp_Board board;

	int next_move;

	int start_piece_id = 33;
	int end_piece_id = 33;
	int mouse_selected_index = 64;

	bool draw_selector = false;

	unsigned int board_size = 8;
	unsigned int board_width = 700;
	unsigned int board_height = 700;
	unsigned int side_display_width = 200;
	unsigned int board_boarder = 30;
	unsigned int slot_width = (board_width - board_boarder * 2) / board_size;
	unsigned int slot_height = (board_width - board_boarder * 2) / board_size;
	unsigned int piece_distance_from_edge = 10;

	sf::Font font;
	if (!font.loadFromFile("ai-playing-checkers/cour.ttf"))
	{
		cout << "font load failed" << endl;
	}

	sf::RenderWindow window(sf::VideoMode(board_width + side_display_width, board_height), "CHECKERS");

	sf::RectangleShape board_base(sf::Vector2f(board_width, board_height));
	sf::RectangleShape selector(sf::Vector2f(slot_width, slot_height));
	sf::RectangleShape slot(sf::Vector2f(slot_width, slot_height));
	sf::CircleShape piece(slot_width / 2 - piece_distance_from_edge);

	sf::Vector2f board_base_origin = board_base.getPosition();
	sf::Vector2f slot_origin = board_base_origin + sf::Vector2f(board_boarder, board_boarder);

	board_base.setFillColor(sf::Color(85, 35, 5));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(10);
	selector.setOutlineColor(sf::Color(55, 0, 130));

	srand(time(NULL));

	//while (false)
	while (window.isOpen())
	{
		sf::Event event;
		sf::Mouse mouse;
		int selected_board_index = 33;
		vector<int> board_status;
		board_status.resize(32);
		for (int i = 0; i < 32; ++i) {
			board_status.at(i) = board.get_board_status(i);
		}

		if (board.get_Player() == _RED_)
		{
			next_move = rand() % board.get_move_list().size();
			board.move_piece(next_move);
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					board.print_moves();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					cout << "GUI OVERRIDE. ENTER MOVE ID: ";
					cin >> next_move;
					board.move_piece(next_move);
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mouse_press_position = mouse.getPosition(window);
				int mouse_x = mouse_press_position.x;
				int mouse_y = mouse_press_position.y;
				int mouse_index_x = (mouse_x - board_boarder) / slot_width;
				int mouse_index_y = (mouse_y - board_boarder) / slot_width;

				mouse_selected_index = mouse_index_x + mouse_index_y * board_size;
				selected_board_index = mouse_selected_index_converter(
					mouse_selected_index, mouse_index_x, mouse_index_y);
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (selected_board_index != 33) { // location selected is valid
			if (selected_board_index == start_piece_id) {
				start_piece_id = 33;
				end_piece_id = 33;
				draw_selector = false;
			}
			else if (start_piece_id != 33) {
				end_piece_id = selected_board_index;
				draw_selector = false;
			}
			else {
				start_piece_id = selected_board_index;
				draw_selector = true;
			}
			cout << "start selected: " << start_piece_id << " end selected: " << end_piece_id << endl;
		}

		if (start_piece_id != 33 && end_piece_id != 33)
		{
			vector<int> attempted_move{ start_piece_id, end_piece_id };
			vector<vector<int>> moves = board.get_move_list();
			auto it = find(moves.begin(), moves.end(), attempted_move);
			if (it != moves.end())
			{
				cout << "move attempted is valid" << endl;
				int move_id = it - moves.begin();
				board.move_piece(move_id);
			}
			else cout << "move attempted is INVALID" << endl;
			start_piece_id = 33;
			end_piece_id = 33;
		}

		window.clear();

		window.draw(board_base);
		bool playable_slot = false;
		sf::Vector2f selector_draw_position;
		for (int col = 0; col < board_size; ++col)
		{
			for (int row = 0; row < board_size; ++row)
			{
				sf::Vector2f position_on_board =
					sf::Vector2f(slot_origin.x, slot_origin.y) +
					sf::Vector2f(slot_width * col, slot_height * row);
				slot.setPosition(position_on_board);

				sf::Vector2f piece_dfe_holder(piece_distance_from_edge, piece_distance_from_edge);
				piece.setPosition(position_on_board + piece_dfe_holder);

				int playable_slot_id = (row * board_size + col) / 2;
				int current_status = board_status[playable_slot_id];

				switch (current_status)
				{
				case _RED_MAN_:
					piece.setFillColor(sf::Color::Red);
					break;
				case _RED_KING_:
					piece.setFillColor(sf::Color(165, 0, 80));
					break;
				case _BLACK_MAN_:
					piece.setFillColor(sf::Color::Black);
					break;
				case _BLACK_KING_:
					piece.setFillColor(sf::Color(125, 125, 125));
					break;
				case _PLAYABLE_:
					piece.setFillColor(sf::Color::Transparent);
					break;
				}

				if (playable_slot)
				{
					string p_slot_id_str = to_string(playable_slot_id);
					sf::Text slot_id(p_slot_id_str, font, 15);
					slot_id.setPosition(position_on_board);
					slot.setFillColor(sf::Color(125, 75, 30));
					window.draw(slot);
					window.draw(slot_id);
					window.draw(piece);
					if (draw_selector)
						selector_draw_position = position_on_board;
					playable_slot = !playable_slot;
				}
				else
				{
					slot.setFillColor(sf::Color(240, 195, 150));
					window.draw(slot);
					playable_slot = !playable_slot;
				}
			}
			playable_slot = !playable_slot;
		}
		// selector drawer
		if (mouse_selected_index != 64 && start_piece_id != 33)
		{
			int col = mouse_selected_index % 8;
			int row = mouse_selected_index / 8;
			int col_translate = col * slot_width + board_boarder;
			int row_translate = row * slot_height + board_boarder;
			sf::Vector2f selector_draw_location(col_translate, row_translate);
			selector.setPosition(selector_draw_location);
			window.draw(selector);
		}

		window.display();

		if (board.is_over()) {
			cout << "GAME ENDED. PRESS ENTER TO EXIT. (or R to restart but later)" << endl;

			break;
		}
	}

	return 0;

	std::cout << "This is a game of checkers." << std::endl;
	std::cout << "Printed below the board is the list of move options" << std::endl;
	std::cout << "Choose a move to begin game, type -1 to end game" << std::endl;
	while (!board.is_over())
	{
		int next_move;
		draw_board(board);
		board.print_moves();

		if (board.get_Player() == _BLACK_)
		{
			std::cout << "Player: " << board.get_Player() << std::endl;
			std::cout << "Move choice:";
			std::cin >> next_move;
		}
		else
		{
			next_move = rand() % board.get_move_list().size();
			std::cout << "computer did move:" <<next_move<< std::endl;
			std::cout << "computer did move" << std::endl;
		}
		
		//apparently, setting next move equal to something insanely large like
		//11111111111111111111111111111111111111
		//or plugging in characters such as 'a' will cause std::cin.fail() to be
		//true causing the program to enter an infinite loop. This next if statement
		//fixes this.
		if (std::cin.bad() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.get();
		}

		if (next_move == -1)
		{
			break;
		}
		board.move_piece(next_move);
	}
	std::cout << "game over" << std::endl;

	return 0;



	/*
	Board board0(8, 8, _BLACK_);

	int p1_piece0 = 12;

	//move 0 -- print initial board & info
	board0.print_board();
	//board0.move_piece(92, 79);
	//board0.move_piece(57, 68);
	//board0.move_piece(79, 66);
	//board0.move_piece(79, 57);

	//this:
	//92 79 57 68 79 57 55 68
	//produces a disappearing r piece
	//92 79 57 68 79 57 55 68 90 79 68 90

//SERIES OF TESTS -- I'M NOT SURE HOW TO USE CATCH AT THE MOMENT

	//TODO: generate correct jumped over piece id
	while (!board0.game_ended()) {
		board0.generate_valid_actions();
		board0.print_all_current_possible_moves();
		int current;
		int destination;
		cout << "Enter the next move (0 to print board info, 1 to stop game): ";
		cin >> current >> destination;
		if (current == 0) {
			board0.print_moves_made();
			board0.print_all_current_possible_jumps();
			board0.print_all_current_possible_moves();
			print_info(board0);
		}
		else if (current == 1) {
			break;
		}
		else {
			board0.move_piece(current, destination);
			cout << "INSTRUCTION ENDED\n\n";
		}
	}

	cout << endl;
	*/
}