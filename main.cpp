// main.cpp
// cs 405/605 introduction to ai spring 2018
// ai playing checkers project
// members: jason hsi, jesse keller, and addeline mitchell
// created jan 23, 2018
//
//#include "board.h"
//#include "neuralnetwork.h"
//#include <random>
//#include <time.h>
//#include <sfml\graphics.hpp>
//
//#include <iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//using std::streamsize;
//#include <vector>
//using std::vector;
//#include <utility>
//using std::pair;
//using std::make_pair;
//#include <string>
//using std::string;
//using std::to_string;
//#include <fstream>
//using std::ofstream;
//using std::ifstream;
//#include <limits>
//using std::numeric_limits;
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
//	game of checkers using temp_board
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
//	sorry, for my version i have to enter the "ai-playing-checkers" direcotry to open the files
//	just remove the "ai-playing-checkers" part of the string for it to work for you (probably)
//	string file_name = "ai-playing-checkers\\games_played\\game_" + year + month + day + '_' + hour + minute + second + ".txt";
//
//	std::ofstream to_file;
//	to_file.open(file_name, std::ofstream::out | std::ofstream::app);
//
//	temp_board board(_red_);
//	board_tree board_tree(board);
//	vector<int> tree_result = min_max_search(board, 1);
//	for (auto n : tree_result)
//	{
//		cout << n << endl;
//	}
//	board.write_board_to_file(to_file);
//
//	if (!to_file.is_open())//|| !to_compressed_file.is_open())
//	{
//		cout << "*********************************************************" << endl;
//		cout << "error opening file: probably not writing game data" << endl;
//		cout << "please check if the file name is correct for your version" << endl;
//		cout << "*********************************************************" << endl;
//	}
//
//	int next_move;
//
//	int start_piece_id = 33;
//	int end_piece_id = 33;
//	int mouse_selected_index = 64;
//	int window_loop_cycles = 0;
//	int ai_wait_time = 200;
//
//	int random_move_count = 3;
//	int random_moves_made = 0;
//
//	bool draw_selector = false;
//	bool red_is_ai = true;
//	bool black_is_ai = true;
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
//	sf::renderwindow window(sf::videomode(board_width + side_display_width, board_height), "checkers");
//
//	sf::rectangleshape board_base(sf::vector2f(board_width, board_height));
//	sf::rectangleshape selector(sf::vector2f(slot_width, slot_height));
//	sf::rectangleshape slot(sf::vector2f(slot_width, slot_height));
//	sf::sprite piece;
//	piece.setscale(0.2375, 0.2375);
//
//	sf::vector2f board_base_origin = board_base.getposition();
//	sf::vector2f slot_origin = board_base_origin + sf::vector2f(board_boarder, board_boarder);
//
//	board_base.setfillcolor(sf::color(85, 35, 5));
//	selector.setfillcolor(sf::color::transparent);
//	selector.setoutlinethickness(10);
//	selector.setoutlinecolor(sf::color(55, 0, 130));
//
//
//	sf::font font;
//
//	sorry, for my version i have to enter the "ai-playing-checkers" direcotry to open the files
//	just remove the "ai-playing-checkers/" part of the string for it to work for you (probably)
//	if (!font.loadfromfile("ai-playing-checkers/res/cour.ttf"))
//	{
//		cout << "font load failed" << endl;
//	}
//
//	sf::texture red_king;
//	if (!red_king.loadfromfile("ai-playing-checkers/res/red_king.png"))
//	{
//		cout << "red_king load failed" << endl;
//	}
//	red_king.setsmooth(true);
//
//	sf::texture red_soldier;
//	if (!red_soldier.loadfromfile("ai-playing-checkers/res/red_soldier.png"))
//	{
//		cout << "red_soldier load failed" << endl;
//	}
//	red_soldier.setsmooth(true);
//
//	sf::texture black_king;
//	if (!black_king.loadfromfile("ai-playing-checkers/res/black_king.png"))
//	{
//		cout << "black_king load failed" << endl;
//	}
//	black_king.setsmooth(true);
//
//	sf::texture black_soldier;
//	if (!black_soldier.loadfromfile("ai-playing-checkers/res/black_soldier.png"))
//	{
//		cout << "black_soldier load failed" << endl;
//	}
//	black_soldier.setsmooth(true);
//
//	sf::texture unseen_piece;
//	if (!unseen_piece.loadfromfile("ai-playing-checkers/res/empty.png"))
//	{
//		cout << "unseen_piece load failed" << endl;
//	}
//
//	srand(time(null));
//
//
//	while (window.isopen())
//	{
//		 this is for ai wait time only, may remove
//		window_loop_cycles++;
//
//		sf::event event;
//		sf::mouse mouse;
//		int selected_board_index = 33;
//		vector<int> board_status;
//		board_status.resize(32);
//		for (int i = 0; i < 32; ++i) {
//			board_status.at(i) = board.get_board_status(i);
//		}
//
//		 ai movement
//		if (window_loop_cycles > ai_wait_time) {
//			if (red_is_ai && board.get_player() == _red_ && board.get_move_list().size() > 0) {
//				if (random_moves_made != random_move_count)
//				{
//					next_move = rand() % board.get_move_list().size();
//					random_moves_made++;
//				}
//				else {
//					std::vector<int> min_max_move = min_max_search(board, 4);
//					next_move = min_max_move.at(0);
//					int val = min_max_move.at(1);
//				}
//				board.move_piece(next_move);
//				board.write_board_to_file(to_file);
//				window_loop_cycles = 0;
//			}
//
//			else if (black_is_ai && board.get_player() == _black_ && board.get_move_list().size() > 0) {
//				if (random_moves_made != random_move_count)
//				{
//					next_move = rand() % board.get_move_list().size();
//					random_moves_made++;
//				}
//				else {
//					std::vector<int> min_max_move = min_max_search(board, 4);
//					next_move = min_max_move.at(0);
//					int val = min_max_move.at(1);
//				}
//				board.move_piece(next_move);
//				board.write_board_to_file(to_file);
//				window_loop_cycles = 0;
//			}
//		}
//
//		*************************************************************************
//		 event poller -- add runtime events here
//		*************************************************************************
//		while (window.pollevent(event))
//		{
//
//			if (event.type == sf::event::keypressed)
//			{
//				if (sf::keyboard::iskeypressed(sf::keyboard::f))
//				{
//					board.print_moves();
//				}
//				if (sf::keyboard::iskeypressed(sf::keyboard::m))
//				{
//					cout << "gui override. enter move id or q to exit override: ";
//					cin >> next_move;
//					if (next_move == 'q')
//					{
//						break;
//					}
//					else {
//						board.move_piece(next_move);
//						board.write_board_to_file(to_file);
//					}
//				}
//				if (sf::keyboard::iskeypressed(sf::keyboard::right))
//				{
//					next_move = rand() % board.get_move_list().size();
//					board.move_piece(next_move);
//					board.write_board_to_file(to_file);
//				}
//			}
//			if (event.type == sf::event::mousebuttonpressed)
//			{
//				sf::vector2i mouse_press_position = mouse.getposition(window);
//				int mouse_x = mouse_press_position.x;
//				int mouse_y = mouse_press_position.y;
//				int mouse_index_x = (mouse_x - board_boarder) / slot_width;
//				int mouse_index_y = (mouse_y - board_boarder) / slot_width;
//
//				mouse_selected_index = mouse_index_x + mouse_index_y * board_size;
//				selected_board_index = mouse_selected_index_converter(
//					mouse_selected_index, mouse_index_x, mouse_index_y);
//			}
//			if (event.type == sf::event::closed)
//			{
//				window.close();
//			}
//		}
//		*************************************************************************
//		 end of event poller
//		*************************************************************************
//
//		 board selector set up
//		if (selected_board_index != 33) // location selected is valid
//		{
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
//		 piece moving
//		if (start_piece_id != 33 && end_piece_id != 33)
//		{
//			vector<int> attempted_move{ start_piece_id, end_piece_id };
//			vector<vector<int>> moves = board.get_move_list();
//			auto it = find(moves.begin(), moves.end(), attempted_move);
//			if (it != moves.end())
//			{
//				cout << "move attempted is valid" << endl;
//				int move_id = it - moves.begin();
//				board.move_piece(move_id);
//				window_loop_cycles = 0;
//				board.write_board_to_file(to_file);
//
//			}
//			else cout << "move attempted is invalid" << endl;
//			start_piece_id = 33;
//			end_piece_id = 33;
//		}
//
//		*************************************************************************
//		*************************************************************************
//		window.clear();
//		window.draw(board_base);
//		bool playable_slot = false;
//		sf::vector2f selector_draw_position;
//
//		 main chunk of drawing
//		for (int col = 0; col < board_size; ++col)
//		{
//			for (int row = 0; row < board_size; ++row)
//			{
//				sf::vector2f position_on_board =
//					sf::vector2f(slot_origin.x, slot_origin.y) +
//					sf::vector2f(slot_width * col, slot_height * row);
//				slot.setposition(position_on_board);
//
//				sf::vector2f piece_dfe_holder(piece_distance_from_edge, piece_distance_from_edge);
//				piece.setposition(position_on_board + piece_dfe_holder);
//
//				int playable_slot_id = (row * board_size + col) / 2;
//				int current_status = board_status[playable_slot_id];
//
//				switch (current_status)
//				{
//				case _red_man_:
//					piece.settexture(red_soldier);
//					break;
//				case _red_king_:
//					piece.settexture(red_king);
//					break;
//				case _black_man_:
//					piece.settexture(black_soldier);
//					break;
//				case _black_king_:
//					piece.settexture(black_king);
//					break;
//				case _playable_:
//					piece.settexture(unseen_piece);
//					break;
//				}
//
//				if (playable_slot)
//				{
//					string p_slot_id_str = to_string(playable_slot_id);
//					sf::text slot_id(p_slot_id_str, font, 15);
//					slot_id.setposition(position_on_board);
//					slot.setfillcolor(sf::color(125, 75, 30));
//					window.draw(slot);
//					window.draw(slot_id);
//					window.draw(piece);
//					if (draw_selector)
//						selector_draw_position = position_on_board;
//					playable_slot = !playable_slot;
//				}
//				else
//				{
//					slot.setfillcolor(sf::color(240, 195, 150));
//					window.draw(slot);
//					playable_slot = !playable_slot;
//				}
//			}
//			playable_slot = !playable_slot;
//		}
//
//		 selector drawer
//		if (mouse_selected_index != 64 && start_piece_id != 33)
//		{
//			int col = mouse_selected_index % 8;
//			int row = mouse_selected_index / 8;
//			int col_translate = col * slot_width + board_boarder;
//			int row_translate = row * slot_height + board_boarder;
//			sf::vector2f selector_draw_location(col_translate, row_translate);
//			selector.setposition(selector_draw_location);
//			window.draw(selector);
//		}
//
//		vector<string> strings_to_draw;
//
//		string player = "null";
//		sf::text player_text(player, font, 30);
//
//		string pieces = "null";
//		sf::text pieces_text(player, font, 30);
//
//		if (board.get_player() == _red_) {
//			player = "red turn";
//			player_text.setfillcolor(sf::color::red);
//		}
//		else {
//			player = "black turn";
//			player_text.setfillcolor(sf::color::white);
//		}
//
//		if (board.is_over()) {
//			if (board.get_player() == _red_) {
//				player = "black wins";
//				player_text.setfillcolor(sf::color::white);
//			}
//			else {
//				player = "red wins";
//				player_text.setfillcolor(sf::color::red);
//			}
//		}
//
//		board.handle_count(pieces, pieces_text); // live piece count
//
//		player_text.setstring(player);
//		pieces_text.setstring(pieces);
//
//		player_text.setposition(board_width + 10, 5);
//		pieces_text.setposition(board_width + 10, 100);
//
//		window.draw(player_text);
//		window.draw(pieces_text);
//
//		window.display();
//
//		if (board.is_over())
//		{
//			if (last_move)
//			{
//				board.denote_endgame(player, to_file);
//				cout << "game ended. returned to console." << endl;
//				break;
//			}
//			last_move = true;
//		}
//	}
//
//	to_file.close();
//
//	cout << endl << "game over >> press enter to exit" << endl;
//	cin.clear();
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	while (cin.get() != '\n');
//
//	return 0;
//}