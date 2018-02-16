//// main.cpp
//// CS 405/605 Introduction to AI Spring 2018
//// AI Playing Checkers Project
//// Members: Jason Hsi, Jesse Keller, and Addeline Mitchell
//// Created Jan 23, 2018
//
//#include "board.h"
//#include "NeuralNetwork.h"
//#include <random>
//#include <time.h>
//#include <SFML\Graphics.hpp>
//
//#include <iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//#include <vector>
//using std::vector;
//#include <string>
//using std::string;
//using std::to_string;
//#include <fstream>
//using std::ofstream;
////using std::ifstream;
//
//int mouse_selected_index_converter(int mouse_selected_index, int mouse_index_x, int mouse_index_y)
//{
//	int return_index = 33;
//	if (mouse_selected_index % 2 == 1 &&
//		mouse_index_x % 2 == 1 &&
//		mouse_index_y % 2 == 0 &&
//		mouse_index_x < 8)
//		return (mouse_selected_index - 1) / 2;
//	else if (mouse_selected_index % 2 == 0 &&
//		mouse_index_x % 2 == 0 &&
//		mouse_index_y % 2 == 1 &&
//		mouse_index_x < 8)
//		return (mouse_selected_index / 2);
//	else
//		return return_index;
//}
//
//string adjust_time(int unit);
//string adjust_time(int unit)
//{
//	string str;
//	if (unit < 10)
//	{
//		str = "0" + to_string(unit);
//	}
//	else
//	{
//		str = to_string(unit);
//	}
//	return str;
//}
//
//int main() {
//
//	//int NN_layers = 5;
//	//int layer_0_nc = 4;
//	//int layer_1_nc = 32;
//	//int layer_2_nc = 40;
//	//int layer_3_nc = 10;
//	//int layer_4_nc = 1;
//
//	//NeuralNetwork brunette26(NN_layers);
//	//brunette26.set_node_count(0, layer_0_nc);
//	//brunette26.set_node_count(1, layer_1_nc);
//	//brunette26.set_node_count(2, layer_2_nc);
//	//brunette26.set_node_count(3, layer_3_nc);
//	//brunette26.set_node_count(4, layer_4_nc);
//
//	//Game of checkers using temp_Board
//
//	struct tm timeinfo;
//	time_t now = time(0);
//	localtime_s(&timeinfo, &now);
//
//	string year = to_string(1900 + timeinfo.tm_year);
//	string month = adjust_time(1 + timeinfo.tm_mon);
//	string day = adjust_time(timeinfo.tm_mday);
//
//	string hour = adjust_time(timeinfo.tm_hour);
//	string minute = adjust_time(timeinfo.tm_min);
//	string second = adjust_time(timeinfo.tm_sec);
//
//	//sorry, for my version I have to enter the "ai-playing-checkers" direcotry to open the files
//	//just remove the "ai-playing-checkers" part of the string for it to work for you (probably)
//	string file_name = "ai-playing-checkers\\games_played\\game_" + year + month + day + '_' + hour + minute + second + ".txt";
//	string compressed_board_status_file_name = 
//		"ai-playing-checkers\\compressed_game_data\\cmprss_game_" + year + month + day + '_' + hour + minute + second + ".txt";
//	string readable_board_status_file_name =
//		"ai-playing-checkers\\readable_game_data\\readable_game_" + year + month + day + '_' + hour + minute + second + ".txt";
//
//	std::ofstream to_file;
//	to_file.open(file_name, std::ofstream::out | std::ofstream::app);
//	std::ofstream to_file_for_cmprss;
//	to_file_for_cmprss.open(compressed_board_status_file_name, std::ofstream::out | std::ofstream::binary);
//	std::ofstream to_file_readable;
//	to_file_readable.open(readable_board_status_file_name, std::ofstream::out | std::ofstream::app);
//
//	if (!to_file_readable.is_open())
//	{
//		cout << "readable not open" << endl;
//	}
//
//	temp_Board board(_RED_);
//	board.write_board_to_file(to_file_for_cmprss, to_file_readable);
//
//	if (!to_file.is_open()) 
//	{
//		cout << "*********************************************************" << endl;
//		cout << "ERROR OPENING FILE: PROBABLY NOT WRITING GAME DATA" << endl;
//		cout << "PLEASE CHECK IF THE FILE NAME IS CORRECT FOR YOUR VERSION" << endl;
//		cout << "*********************************************************" << endl;
//	}
//
//	int next_move;
//
//	int start_piece_id = 33;
//	int end_piece_id = 33;
//	int mouse_selected_index = 64;
//	int window_loop_cycles = 0;
//	int ai_wait_time = 300;
//
//	bool draw_selector = false;
//	bool red_is_ai = false;
//	bool black_is_ai = false;
//	bool last_move = false;
//
//	unsigned int board_size = 8;
//	unsigned int board_width = 700;
//	unsigned int board_height = 700;
//	unsigned int side_display_width = 200;
//	unsigned int board_boarder = 30;
//	unsigned int slot_width = (board_width - board_boarder * 2) / board_size;
//	unsigned int slot_height = (board_width - board_boarder * 2) / board_size;
//	unsigned int piece_distance_from_edge = 10;
//
//	sf::RenderWindow window(sf::VideoMode(board_width + side_display_width, board_height), "CHECKERS");
//
//	sf::RectangleShape board_base(sf::Vector2f(board_width, board_height));
//	sf::RectangleShape selector(sf::Vector2f(slot_width, slot_height));
//	sf::RectangleShape slot(sf::Vector2f(slot_width, slot_height));
//	sf::Sprite piece;
//	piece.setScale(0.2375, 0.2375);
//
//	sf::Vector2f board_base_origin = board_base.getPosition();
//	sf::Vector2f slot_origin = board_base_origin + sf::Vector2f(board_boarder, board_boarder);
//
//	board_base.setFillColor(sf::Color(85, 35, 5));
//	selector.setFillColor(sf::Color::Transparent);
//	selector.setOutlineThickness(10);
//	selector.setOutlineColor(sf::Color(55, 0, 130));
//
//
//	sf::Font font;
//
//	//sorry, for my version I have to enter the "ai-playing-checkers" direcotry to open the files
//	//just remove the "ai-playing-checkers/" part of the string for it to work for you (probably)
//	if (!font.loadFromFile("ai-playing-checkers/res/cour.ttf"))
//	{
//		cout << "font load failed" << endl;
//	}
//
//	sf::Texture red_king;
//	if (!red_king.loadFromFile("ai-playing-checkers/res/red_king.png"))
//	{
//		cout << "red_king load failed" << endl;
//	}
//	red_king.setSmooth(true);
//
//	sf::Texture red_soldier;
//	if (!red_soldier.loadFromFile("ai-playing-checkers/res/red_soldier.png"))
//	{
//		cout << "red_soldier load failed" << endl;
//	}
//	red_soldier.setSmooth(true);
//
//	sf::Texture black_king;
//	if (!black_king.loadFromFile("ai-playing-checkers/res/black_king.png"))
//	{
//		cout << "black_king load failed" << endl;
//	}
//	black_king.setSmooth(true);
//
//	sf::Texture black_soldier;
//	if (!black_soldier.loadFromFile("ai-playing-checkers/res/black_soldier.png"))
//	{
//		cout << "black_soldier load failed" << endl;
//	}
//	black_soldier.setSmooth(true);
//
//	sf::Texture unseen_piece;
//	if (!unseen_piece.loadFromFile("ai-playing-checkers/res/empty.png"))
//	{
//		cout << "unseen_piece load failed" << endl;
//	}
//
//	srand(time(NULL));
//
//	while (window.isOpen())
//	{
//		// this is for ai wait time only, may remove
//		window_loop_cycles++;
//
//		sf::Event event;
//		sf::Mouse mouse;
//		int selected_board_index = 33;
//		vector<int> board_status;
//		board_status.resize(32);
//		for (int i = 0; i < 32; ++i) {
//			board_status.at(i) = board.get_board_status(i);
//		}
//
//		if (window_loop_cycles > ai_wait_time) {
//			if (red_is_ai && board.get_Player() == _RED_ && board.get_move_list().size() > 0) {
//				next_move = rand() % board.get_move_list().size();
//				board.process_output(next_move, to_file);
//				board.move_piece(next_move);
//				board.write_board_to_file(to_file_for_cmprss,to_file_readable);
//				window_loop_cycles = 0;
//			}
//		
//			if (black_is_ai && board.get_Player() == _BLACK_ && board.get_move_list().size() > 0) {
//				next_move = rand() % board.get_move_list().size();
//				board.process_output(next_move, to_file);
//				board.move_piece(next_move);
//				board.write_board_to_file(to_file_for_cmprss,to_file_readable);
//				window_loop_cycles = 0;
//			}
//		}
//
//		
//		//*************************************************************************
//		// EVENT POLLER -- ADD RUNTIME EVENTS HERE
//		//*************************************************************************
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::KeyPressed)
//			{
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
//				{
//					board.print_moves();
//				}
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
//				{
//					cout << "GUI OVERRIDE. ENTER MOVE ID OR q TO EXIT OVERRIDE: ";
//					cin >> next_move;
//					if (next_move == 'q')
//					{
//						break;
//					}
//					else {
//						board.process_output(next_move, to_file);
//						board.move_piece(next_move);
//						board.write_board_to_file(to_file_for_cmprss, to_file_readable);
//					}
//				}
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//				{
//					next_move = rand() % board.get_move_list().size();
//					board.process_output(next_move, to_file);
//					board.move_piece(next_move);
//					board.write_board_to_file(to_file_for_cmprss, to_file_readable);
//				}
//			}
//			if (event.type == sf::Event::MouseButtonPressed)
//			{
//				sf::Vector2i mouse_press_position = mouse.getPosition(window);
//				int mouse_x = mouse_press_position.x;
//				int mouse_y = mouse_press_position.y;
//				int mouse_index_x = (mouse_x - board_boarder) / slot_width;
//				int mouse_index_y = (mouse_y - board_boarder) / slot_width;
//
//				mouse_selected_index = mouse_index_x + mouse_index_y * board_size;
//				selected_board_index = mouse_selected_index_converter(
//					mouse_selected_index, mouse_index_x, mouse_index_y);
//			}
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//		}
//		//*************************************************************************
//		// END OF EVENT POLLER
//		//*************************************************************************
//
//
//		// Board Selector Set Up
//		if (selected_board_index != 33) { // location selected is valid
//			if (selected_board_index == start_piece_id) {
//				start_piece_id = 33;
//				end_piece_id = 33;
//				draw_selector = false;
//			}
//			else if (start_piece_id != 33) {
//				end_piece_id = selected_board_index;
//				draw_selector = false;
//			}
//			else {
//				start_piece_id = selected_board_index;
//				draw_selector = true;
//			}
//			cout << "start selected: " << start_piece_id << " end selected: " << end_piece_id << endl;
//		}
//
//
//		if (start_piece_id != 33 && end_piece_id != 33)
//		{
//			vector<int> attempted_move{ start_piece_id, end_piece_id };
//			vector<vector<int>> moves = board.get_move_list();
//			auto it = find(moves.begin(), moves.end(), attempted_move);
//			if (it != moves.end())
//			{
//				//cout << "move attempted is valid" << endl;
//				int move_id = it - moves.begin();
//				board.process_output(move_id, to_file);
//				board.move_piece(move_id);
//				board.write_board_to_file(to_file_for_cmprss, to_file_readable);
//
//			}
//			//else cout << "move attempted is INVALID" << endl;
//			start_piece_id = 33;
//			end_piece_id = 33;
//		}
//
//		//*************************************************************************
//		//*************************************************************************
//		window.clear();
//		window.draw(board_base);
//		bool playable_slot = false;
//		sf::Vector2f selector_draw_position;
//		for (int col = 0; col < board_size; ++col)
//		{
//			for (int row = 0; row < board_size; ++row)
//			{
//				sf::Vector2f position_on_board =
//					sf::Vector2f(slot_origin.x, slot_origin.y) +
//					sf::Vector2f(slot_width * col, slot_height * row);
//				slot.setPosition(position_on_board);
//
//				sf::Vector2f piece_dfe_holder(piece_distance_from_edge, piece_distance_from_edge);
//				piece.setPosition(position_on_board + piece_dfe_holder);
//
//				int playable_slot_id = (row * board_size + col) / 2;
//				int current_status = board_status[playable_slot_id];
//
//				switch (current_status)
//				{
//				case _RED_MAN_:
//					piece.setTexture(red_soldier);
//					break;
//				case _RED_KING_:
//					piece.setTexture(red_king);
//					break;
//				case _BLACK_MAN_:
//					piece.setTexture(black_soldier);
//					break;
//				case _BLACK_KING_:
//					piece.setTexture(black_king);
//					break;
//				case _PLAYABLE_:
//					piece.setTexture(unseen_piece);
//					break;
//				}
//
//				if (playable_slot)
//				{
//					string p_slot_id_str = to_string(playable_slot_id);
//					sf::Text slot_id(p_slot_id_str, font, 15);
//					slot_id.setPosition(position_on_board);
//					slot.setFillColor(sf::Color(125, 75, 30));
//					window.draw(slot);
//					window.draw(slot_id);
//					window.draw(piece);
//					if (draw_selector)
//						selector_draw_position = position_on_board;
//					playable_slot = !playable_slot;
//				}
//				else
//				{
//					slot.setFillColor(sf::Color(240, 195, 150));
//					window.draw(slot);
//					playable_slot = !playable_slot;
//				}
//			}
//			playable_slot = !playable_slot;
//		}
//		// selector drawer
//		if (mouse_selected_index != 64 && start_piece_id != 33)
//		{
//			int col = mouse_selected_index % 8;
//			int row = mouse_selected_index / 8;
//			int col_translate = col * slot_width + board_boarder;
//			int row_translate = row * slot_height + board_boarder;
//			sf::Vector2f selector_draw_location(col_translate, row_translate);
//			selector.setPosition(selector_draw_location);
//			window.draw(selector);
//		}
//
//		vector<string> strings_to_draw;
//
//		string player = "null";
//		sf::Text player_text(player, font, 30);
//		if (board.get_Player() == _RED_) { 
//			player = "RED TURN";
//			player_text.setFillColor(sf::Color::Red);
//		}
//		else { 
//			player = "BLACK TURN"; 
//			player_text.setFillColor(sf::Color::White);
//		}
//		
//		if (board.is_over()) {
//			if (board.get_Player() == _RED_) {
//				player = "BLACK WINS";
//				player_text.setFillColor(sf::Color::White);
//			}
//			else {
//				player = "RED WINS";
//				player_text.setFillColor(sf::Color::Red);
//			}
//		}
//
//		player_text.setString(player);
//
//		player_text.setPosition(board_width + 10, 5);
//		window.draw(player_text);
//
//		window.display();
//
//		if (board.is_over())
//		{
//			if (last_move)
//			{
//				board.denote_endgame(player, to_file);
//				cout << "GAME ENDED. RETURNED TO CONSOLE." << endl;
//				break;
//			}
//			last_move = true;
//		}
//	}
//
//	// update to show last move and ask to close?
//	std::cout << "game over, press 'x' to close game window" << std::endl;
//	to_file.close();
//	to_file_for_cmprss.close();
//	to_file_readable.close();
//
//	while (cin.get() != 'x');
//	return 0;
//}