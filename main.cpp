// main.cpp
// cs 405/605 introduction to ai spring 2018
// ai playing checkers project
// members: jason hsi, jesse keller, and addeline mitchell
// created jan 23, 2018

// INCLUDES
#include "board.h"
#include "NeuralNetwork.h"
#include "NeuralNetwork_PERF.h"
#include "offspringproducer.h"
#include "GnuGraph.h"

#include <time.h>
#include <SFML\Graphics.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <limits>
#include <chrono>
#include <random>

// USINGS
using std::cout;
using std::endl;
using std::cin;
using std::streamsize;
using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::to_string;
using std::ofstream;
using std::ifstream;
using std::numeric_limits;
using std::normal_distribution;
using std::random_device;
using std::mt19937;
using std::map;


enum { // THESE ARE THE DIFFERENT TYPES OF main_state
	PLAY_CHECKERS,
	NEURAL_NETWORK_TIMING,
	NEURAL_NETWORK_TESTING,
	NEURAL_NETWORK_TIMING_PERF,
	NEURAL_NETWORK_OFFSPRING,
	GAUSSIAN_GRAPHING
};

//**********************************************************************************************
//CHANGE main_state VARIABLE TO DESIRED MAIN
//MAINS MERGED ON 2/23/2018
//**********************************************************************************************
int main_state = PLAY_CHECKERS;
//**********************************************************************************************
//**********************************************************************************************

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

string adjust_time(int unit)
{
	string str;
	if (unit < 10)
	{
		str = "0" + to_string(unit);
	}
	else
	{
		str = to_string(unit);
	}
	return str;
}

double do_calculation(double input, double weight)
{
	cout << input << " * " << weight << " = " << input*weight << endl;
	return input * weight;
}

void apply_sigma_t(double & input)
{
	cout << "		DID SIGMA: s(" << input << ") = ";
	input = (2 / (1 + exp(-input)) - 1);
	cout << input << endl << endl;
}

int main() {
	if (main_state == PLAY_CHECKERS) {
		//Game of checkers using temp_Board
		struct tm timeinfo;
		time_t now = time(0);
		localtime_s(&timeinfo, &now);

		string year = to_string(1900 + timeinfo.tm_year);
		string month = adjust_time(1 + timeinfo.tm_mon);
		string day = adjust_time(timeinfo.tm_mday);

		string hour = adjust_time(timeinfo.tm_hour);
		string minute = adjust_time(timeinfo.tm_min);
		string second = adjust_time(timeinfo.tm_sec);

		//sorry, for my version I have to enter the "ai-playing-checkers" direcotry to open the files
		//just remove the "ai-playing-checkers" part of the string for it to work for you (probably)
		string file_name = "ai-playing-checkers\\games_played\\game_" + year + month + day + '_' + hour + minute + second + ".txt";

		ofstream to_file;
		to_file.open(file_name, ofstream::out | ofstream::app);

		if (!to_file.is_open())//|| !to_compressed_file.is_open())
		{
			cout << "*********************************************************" << endl;
			cout << "ERROR OPENING FILE: PROBABLY NOT WRITING GAME DATA" << endl;
			cout << "PLEASE CHECK IF THE FILE NAME IS CORRECT FOR YOUR VERSION" << endl;
			cout << "*********************************************************" << endl;
		}

		temp_Board board(_RED_);
		Board_tree board_tree(board);
		vector<int> tree_result = min_max_search(board, 1);
		board.write_board_to_file(to_file);

		int next_move;

		int start_piece_id = 33;
		int end_piece_id = 33;
		int mouse_selected_index = 64;
		int window_loop_cycles = 0;
		int ai_wait_time = 300;

		bool draw_selector = false;
		bool red_is_ai = true;
		bool black_is_ai = true;
		bool last_move = false;

		int random_moves_made = 0;
		int random_move_count = 3;

		unsigned int board_size = 8;
		unsigned int board_width = 700;
		unsigned int board_height = 700;
		unsigned int side_display_width = 200;
		unsigned int board_boarder = 30;
		unsigned int slot_width = (board_width - board_boarder * 2) / board_size;
		unsigned int slot_height = (board_width - board_boarder * 2) / board_size;
		unsigned int piece_distance_from_edge = 10;

		// SFML INITIALIZATIONS
		sf::RenderWindow window(sf::VideoMode(board_width + side_display_width, board_height), "CHECKERS");

		sf::RectangleShape board_base(sf::Vector2f(board_width, board_height));
		sf::RectangleShape selector(sf::Vector2f(slot_width, slot_height));
		sf::RectangleShape slot(sf::Vector2f(slot_width, slot_height));
		sf::Sprite piece;
		piece.setScale(0.2375, 0.2375);

		sf::Vector2f board_base_origin = board_base.getPosition();
		sf::Vector2f slot_origin = board_base_origin + sf::Vector2f(board_boarder, board_boarder);

		board_base.setFillColor(sf::Color(85, 35, 5));
		selector.setFillColor(sf::Color::Transparent);
		selector.setOutlineThickness(10);
		selector.setOutlineColor(sf::Color(55, 0, 130));

		sf::Font font;

		//sorry, for my version I have to enter the "ai-playing-checkers" direcotry to open the files
		//just remove the "ai-playing-checkers/" part of the string for it to work for you (probably)
		if (!font.loadFromFile("ai-playing-checkers/res/cour.ttf"))
		{
			cout << "font load failed" << endl;
		}

		sf::Texture red_king;
		if (!red_king.loadFromFile("ai-playing-checkers/res/red_king.png"))
		{
			cout << "red_king load failed" << endl;
		}
		red_king.setSmooth(true);

		sf::Texture red_soldier;
		if (!red_soldier.loadFromFile("ai-playing-checkers/res/red_soldier.png"))
		{
			cout << "red_soldier load failed" << endl;
		}
		red_soldier.setSmooth(true);

		sf::Texture black_king;
		if (!black_king.loadFromFile("ai-playing-checkers/res/black_king.png"))
		{
			cout << "black_king load failed" << endl;
		}
		black_king.setSmooth(true);

		sf::Texture black_soldier;
		if (!black_soldier.loadFromFile("ai-playing-checkers/res/black_soldier.png"))
		{
			cout << "black_soldier load failed" << endl;
		}
		black_soldier.setSmooth(true);

		sf::Texture unseen_piece;
		if (!unseen_piece.loadFromFile("ai-playing-checkers/res/empty.png"))
		{
			cout << "unseen_piece load failed" << endl;
		}

		srand(time(NULL));


		while (window.isOpen())
		{
			// this is for ai wait time only, may remove
			window_loop_cycles++;

			sf::Event event;
			sf::Mouse mouse;
			int selected_board_index = 33;
			vector<int> board_status;
			board_status.resize(32);
			for (int i = 0; i < 32; ++i) {
				board_status.at(i) = board.get_board_status(i);
			}

			// AI movement
			if (window_loop_cycles > ai_wait_time) {
				if (red_is_ai && board.get_Player() == _RED_ && board.get_move_list().size() > 0) {
					if (random_moves_made < random_move_count)
					{
						next_move = rand() % board.get_move_list().size();
						random_moves_made++;
					}
					else {
						vector<int> min_max_move = min_max_search(board, 4);
						next_move = min_max_move.at(0);
						int val = min_max_move.at(1);
					}
					board.move_piece(next_move);
					board.write_board_to_file(to_file);
					window_loop_cycles = 0;
				}

				else if (black_is_ai && board.get_Player() == _BLACK_ && board.get_move_list().size() > 0) {
					if (random_moves_made < random_move_count)
					{
						next_move = rand() % board.get_move_list().size();
						random_moves_made++;
					}
					else {
						vector<int> min_max_move = min_max_search(board, 4);
						next_move = min_max_move.at(0);
						int val = min_max_move.at(1);
					}
					board.move_piece(next_move);
					board.write_board_to_file(to_file);
					window_loop_cycles = 0;
				}
			}

			//*************************************************************************
			// EVENT POLLER -- ADD RUNTIME EVENTS HERE
			//*************************************************************************
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
						cout << "GUI OVERRIDE; POSSIBLE MOVES LISTED." << endl;
						board.print_moves();
						cout << "ENTER MOVE ID OR q TO EXIT OVERRIDE: ";
						cin >> next_move;
						if (next_move == 'q')
						{
							break;
						}
						else {
							board.move_piece(next_move);
							board.write_board_to_file(to_file);
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						next_move = rand() % board.get_move_list().size();
						board.move_piece(next_move);
						board.write_board_to_file(to_file);
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
				{
					window.close();
				}
			}
			//*************************************************************************
			// END OF EVENT POLLER
			//*************************************************************************

			// Board Selector Set Up
			if (selected_board_index != 33) // location selected is valid
			{
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

			// Piece moving
			if (start_piece_id != 33 && end_piece_id != 33)
			{
				vector<int> attempted_move{ start_piece_id, end_piece_id };
				vector<vector<int>> moves = board.get_move_list();
				auto it = find(moves.begin(), moves.end(), attempted_move);
				if (it != moves.end())
				{
					//cout << "move attempted is valid" << endl;
					int move_id = it - moves.begin();
					board.move_piece(move_id);
					window_loop_cycles = 0;
					board.write_board_to_file(to_file);

				}
				//else cout << "move attempted is INVALID" << endl;
				start_piece_id = 33;
				end_piece_id = 33;
			}

			//*************************************************************************
			//*************************************************************************
			window.clear();
			window.draw(board_base);
			bool playable_slot = false;
			sf::Vector2f selector_draw_position;

			// Main chunk of drawing
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
						piece.setTexture(red_soldier);
						break;
					case _RED_KING_:
						piece.setTexture(red_king);
						break;
					case _BLACK_MAN_:
						piece.setTexture(black_soldier);
						break;
					case _BLACK_KING_:
						piece.setTexture(black_king);
						break;
					case _PLAYABLE_:
						piece.setTexture(unseen_piece);
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

			// window text management
			vector<string> strings_to_draw;
			string player = "null";
			sf::Text player_text(player, font, 30);

			string pieces = "null";
			sf::Text pieces_text(player, font, 30);

			if (board.get_Player() == _RED_) {
				player = "RED TURN";
				player_text.setFillColor(sf::Color::Red);
			}
			else {
				player = "BLACK TURN";
				player_text.setFillColor(sf::Color::White);
			}

			if (board.is_over()) {
				if (board.get_Player() == _RED_) {
					player = "BLACK WINS";
					player_text.setFillColor(sf::Color::White);
				}
				else {
					player = "RED WINS";
					player_text.setFillColor(sf::Color::Red);
				}
			}

			board.handle_count(pieces, pieces_text); // live piece count

			player_text.setString(player);
			pieces_text.setString(pieces);

			player_text.setPosition(board_width + 10, 5);
			pieces_text.setPosition(board_width + 10, 100);

			window.draw(player_text);
			window.draw(pieces_text);

			window.display();

			if (board.is_over())
			{
				if (last_move)
				{
					//board.denote_endgame(player, to_file);
					cout << "GAME ENDED. RETURNED TO CONSOLE." << endl;
					break;
				}
				last_move = true;
			}
		}

		to_file.close();

		cout << endl << "GAME OVER >> press ENTER to exit" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (cin.get() != '\n');

		return 0;
	}
	else if (main_state == NEURAL_NETWORK_TIMING)
	{
		NeuralNetwork nn0;
		nn0.init();
		nn0.set_board_record_with("ai-playing-checkers\\games_played\\game_20180219_142934.txt");

		cout.precision(6);
		cout << "nn0 weights: " << GLOBAL_WEIGHT_COUNT << endl;
		{
			int times = 10;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 100;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 1000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 10000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 100000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 200000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 250000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				nn0.set_input_layer(0);
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate_output();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}

		cout << endl;
		cout << "'Enter' to quit . . .";
		while (cin.get() != '\n');

		return 0;
	}
	else if (main_state == NEURAL_NETWORK_TESTING)
	{
		NeuralNetwork nn_TESTING;

		vector<double> input_TESTING = { -1, 0, 0, 1 };
		vector<double> weights_TESTING = {
			0.1732, -0.0460, -0.1104, 0.1161, 0.0372,
			0.1322, 0.1705, 0.1428, 0.888, 0.697,
			-0.0652, 0.1425, 0.1563, 0.0889, 0.1031,
			-0.1840, 0.0333, -0.0699, -0.0944, -0.1409 };
		nn_TESTING.init_TESTING(input_TESTING, weights_TESTING);

		//LAYER 1
		double layer_1_node_0_result = 0.0;
		layer_1_node_0_result += do_calculation(input_TESTING[0], weights_TESTING[0]);
		layer_1_node_0_result += do_calculation(input_TESTING[1], weights_TESTING[1]);
		layer_1_node_0_result += do_calculation(input_TESTING[2], weights_TESTING[2]);
		layer_1_node_0_result += do_calculation(input_TESTING[3], weights_TESTING[3]);
		apply_sigma_t(layer_1_node_0_result);
		double layer_1_node_1_result = 0.0;
		layer_1_node_1_result += do_calculation(input_TESTING[0], weights_TESTING[4]);
		layer_1_node_1_result += do_calculation(input_TESTING[1], weights_TESTING[5]);
		layer_1_node_1_result += do_calculation(input_TESTING[2], weights_TESTING[6]);
		layer_1_node_1_result += do_calculation(input_TESTING[3], weights_TESTING[7]);
		apply_sigma_t(layer_1_node_1_result);
		double layer_1_node_2_result = 0.0;
		layer_1_node_2_result += do_calculation(input_TESTING[0], weights_TESTING[8]);
		layer_1_node_2_result += do_calculation(input_TESTING[1], weights_TESTING[9]);
		layer_1_node_2_result += do_calculation(input_TESTING[2], weights_TESTING[10]);
		layer_1_node_2_result += do_calculation(input_TESTING[3], weights_TESTING[11]);
		apply_sigma_t(layer_1_node_2_result);

		//LAYER 2
		double layer_2_node_0_result = 0.0;
		layer_2_node_0_result += do_calculation(layer_1_node_0_result, weights_TESTING[12]);
		layer_2_node_0_result += do_calculation(layer_1_node_1_result, weights_TESTING[13]);
		layer_2_node_0_result += do_calculation(layer_1_node_2_result, weights_TESTING[14]);
		apply_sigma_t(layer_2_node_0_result);
		double layer_2_node_1_result = 0.0;
		layer_2_node_1_result += do_calculation(layer_1_node_0_result, weights_TESTING[15]);
		layer_2_node_1_result += do_calculation(layer_1_node_1_result, weights_TESTING[16]);
		layer_2_node_1_result += do_calculation(layer_1_node_2_result, weights_TESTING[17]);
		apply_sigma_t(layer_2_node_1_result);

		//LAYER 3
		double layer_3_node_0_result = 0.0;
		layer_3_node_0_result += do_calculation(layer_2_node_0_result, weights_TESTING[18]);
		layer_3_node_0_result += do_calculation(layer_2_node_1_result, weights_TESTING[19]);
		apply_sigma_t(layer_3_node_0_result);

		cout << "\nOutput with non-NeuralNetwork calculations: " << layer_3_node_0_result << endl;

		nn_TESTING.calculate_output_TESTING();
		cout << "Output with NeuralNetwork object: " << nn_TESTING.get_output() << endl;

		// -1 * 0.1732 = -0.1732
		// 0 * -0.0460 = 0
		// 0 * -0.1104 = 0
		// 1 * 0.0372
	}
	else if (main_state == NEURAL_NETWORK_TIMING_PERF)
	{
		OffspringProducer osp;
		vector<double> input = {
		-1,-1,-1,-1,
		-1,-1,-1,-1,
		-1,-1,-1,-1,
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		};

		NeuralNetwork_PERF nn0(input, osp.generate_random_topology());

		cout.precision(6);
		cout << "nn0 weights: " << GLOBAL_WEIGHT_COUNT << endl;
		{
			int times = 10;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 100;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 1000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 10000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 100000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 150000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 200000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 300000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 500000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
				//cout << nn0.get_output() << endl;
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		cout << endl;
		cout << "'Enter' to quit . . .";
		while (cin.get() != '\n');

		return 0;
	}
	else if (main_state == NEURAL_NETWORK_OFFSPRING)
	{
		// due to the nature of attempting-to-unclutter-NeuralNetwork_PERF,
		// it must take an argument during construction
		vector<double> dummy_input = {
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
		};

		string parent_file = "ai-playing-checkers\\nn_topologies\\GEN0\\nn0_brunette26_topology.txt";
		OffspringProducer osp;
		osp.reset_counter();

		for (auto i = 0; i < 1; ++i) {
			vector<double> topo_holder = osp.generate_random_topology();

			NeuralNetwork_PERF(dummy_input, topo_holder);
			try { osp.record(); }
			catch (std::exception e) { cout << "EXCEPTION CAUGHT: " << e.what() << endl; }
			for (auto j = 0; j < 5; ++j) {
				osp.produce_offspring(parent_file);
				osp.record();
			}
		}
	}
	else if (main_state == GAUSSIAN_GRAPHING)
	{
		GnuGraph graph("C:/Program Files/gnuplot/bin/gnuplot.exe"); // provide path to executable
		
		vector<double> g_vals, width;
		map<double, double> vals;
		
		random_device rnd;
		mt19937 e2(rnd());
		
		normal_distribution<> gauss(0, 1);
		
		for (int i = 0; i < 1000; ++i)
		{
			++vals[round(gauss(e2))];
		}
		
		for (auto & p : vals)
		{
			cout << p.first << ' ' << string(p.second / 200, '*') << '\n';
			
			g_vals.push_back(p.second);
			width.push_back(p.first);
		}
		
		const string output = graph.plot(width, g_vals, "gauss check");
		cout << output << '\n'; // print any errors to console
		
		cout << "press ENTER to quit" << endl;
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (cin.get() != '\n');
		
		return 0;
	}

	cout << "You should not be here." << endl;
	cout << endl << "press ENTER to quit" << endl;
	while (cin.get() != '\n');
	return 0;
}