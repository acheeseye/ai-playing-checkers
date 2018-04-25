// main.cpp
// cs 405/605 introduction to ai spring 2018
// ai playing checkers project
// members: jason hsi, jesse keller, and addeline mitchell
// created jan 23, 2018

// INCLUDES
#include "board.h"
#include "NeuralNetwork_PERF.h"
#include "offspringproducer.h"
#include "checkers.hpp"
#include "checkers_client.hpp"
#include "neuralnet.hpp"
#include "../filehandler.h"

#include <SFML\Graphics.hpp>
#include "gnugraph\GnuGraph.h"

#include <time.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <utility>
using std::pair;
using std::make_pair;
#include <string>
using std::string;
using std::to_string; 
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <limits>
using std::numeric_limits;
#include <chrono>
#include <random>
using std::normal_distribution;
using std::random_device;
using std::mt19937;
#include <sstream>
using std::stringstream;
#include <thread>

// USINGS
using std::streamsize;

enum
{
	PIECE_COUNT_AI,
	NN_BOARD_EVAL,
	NN_ALPHA_BETA
};

enum
{ // THESE ARE THE DIFFERENT TYPES OF main_state
	PLAY_CHECKERS,
	REPLAY_SAVED_GAME,
	NEURAL_NETWORK_TIMING_PERF,
	GEN0_GENERATE,	// generates 30 random gen 0 topologies
	GAUSSIAN_GRAPHING,
	NNvNN,						// network vs network (EACH RUN RESETS THE naming_status.txt FILE, WATCH OUT)
	NNP_TEST,
	NETWORK
};

bool GLOBAL_DO_WRITE = true;
char GLOBAL_WINNER_DENOTER;
int mms_eval_count;
int ab_eval_count;
int call_count;

//**********************************************************************************************
//CHANGE main_state VARIABLE TO DESIRED MAIN
//MAINS MERGED ON 2/23/2018
//**********************************************************************************************
int main_state = NETWORK;

//**********************************************************************************************
//**********************************************************************************************
//**********************************************************************************************
//**********************************************************************************************

string process_to_json_string(const vector<int> & board)
{
	string ret_str = "";

	for (auto i = 0; i < 32; ++i)
	{
		int ibuf = board[i];
		if (ibuf == -1)
		{
			ret_str += 'r';
		}
		else if (ibuf == -2)
		{
			ret_str += 'R';
		}
		else if (ibuf == 1)
		{
			ret_str += 'b';
		}
		else if (ibuf == 2)
		{
			ret_str += 'B';
		}
		else if (ibuf == 4)
		{
			ret_str += '_';
		}
		else
		{
			cout << "INVALID INT DETECTED" << ibuf << endl;
		}
	}
	return ret_str;
}

vector<int> process_to_nn_vec(const string & board_str)
{
	vector<int> ret_vec;
	for (auto i = 0; i < board_str.size(); ++i)
	{
		char cbuf = board_str[i];
		if (cbuf == 'r')
		{
			ret_vec.push_back(-1);
		}
		else if (cbuf == 'R')
		{
			ret_vec.push_back(-2);
		}
		else if (cbuf == 'b')
		{
			ret_vec.push_back(1);
		}
		else if (cbuf == 'B')
		{
			ret_vec.push_back(2);
		}
		else if (cbuf == '_')
		{
			ret_vec.push_back(0);
		}
		else
		{
			cout << "INVALID CHARACTER DETECTED" << endl;
		}
	}
	return ret_vec;
}


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

int find_move(const string & move, temp_Board t, const int i)
{
	t.move_piece(i);
	vector<int> state = t.get_board_as_vector();
	string iter = process_to_json_string(state);
	cout << "     " << iter << endl;
	if(move == iter)
	{
		return i;
	}
	else
	{
		return -1;
	}
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

void fn_play_checkers()
{
	// SETTINGS ******************************************
	//****************************************************
	const auto red_is_ai = true;
	const auto black_is_ai = true;
	const auto red_pc = false;
	const auto black_pc = true;
	const int starting_player = _RED_;
	const int ply = 10;
	const string ai_topo = R"(ai-playing-checkers\nn_topologies\GEN4\nn21_brunette26_topology.txt)";
	const int random_move_count = 3;
	const int ai_wait_time = 300;
	//GLOBAL_DO_WRITE = false;
	//****************************************************
	//****************************************************


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
	string leaf_nodes_evaluated = "ai-playing-checkers\\nn_topologies\\LNE.txt";

	ofstream LNE_fout;
	ofstream to_file;
	to_file.open(file_name, ofstream::out | ofstream::app);
	LNE_fout.open(leaf_nodes_evaluated, ofstream::out | ofstream::app);

	if (!to_file.is_open())//|| !to_compressed_file.is_open())
	{
		cout << "*********************************************************" << endl;
		cout << "ERROR OPENING FILE: PROBABLY NOT WRITING GAME DATA" << endl;
		cout << "PLEASE CHECK IF THE FILE NAME IS CORRECT FOR YOUR VERSION" << endl;
		cout << "*********************************************************" << endl;
		cout << endl << "press ENTER to quit";
		while (cin.get() != '\n');
		return;
	}

	temp_Board board(starting_player);
	OffspringProducer osp;
	FileHandler fh;

	fh.set_file(ai_topo);
	skynet::neuralnet_t nn({32, 40, 10, 1},fh.get_weights(), fh.get_king());

	// declarations, initializations, GUI settings
	int next_move;

	int start_piece_id = 33;
	int end_piece_id = 33;
	int mouse_selected_index = 64;
	int window_loop_cycles = 0;

	bool draw_selector = false;
	bool last_move = false;

	int random_moves_made = 0;

	const unsigned int board_size = 8;
	const unsigned int board_width = 700;
	const unsigned int board_height = 700;
	const unsigned int side_display_width = 200;
	const unsigned int board_boarder = 30;
	const unsigned int slot_width = (board_width - board_boarder * 2) / board_size;
	const unsigned int slot_height = (board_width - board_boarder * 2) / board_size;
	const unsigned int piece_distance_from_edge = 10;

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
		if (window_loop_cycles > ai_wait_time)
		{
			double val;
			if (red_is_ai && board.get_Player() == _RED_ && !board.get_move_list().empty())
			{
				if (random_moves_made < random_move_count)
				{
					next_move = rand() % board.get_move_list().size();
					random_moves_made++;
				}
				else
				{

					//vector<double> min_max_move = min_max_search(nnp, board, 1);
					if(red_pc)
					{
						vector<int> pcmove = piece_count_search(board, ply);
						next_move = pcmove[0];
						val = pcmove[1];
					}
					else
					{
						vector<double> alpha_beta_move = alpha_beta(nn, board, 6, false, -999999, 999999);
						next_move = alpha_beta_move[0];
						val = alpha_beta_move[1];
					}
					cout << "red alpha beta move: id(" << next_move << ") val(" << val << ")" << endl;
					//double val = min_max_move[1];
				
					//cout << "chosen: " << next_move << " " << val << endl;
				
				}
				board.move_piece(next_move);
				window_loop_cycles = 0;
			}
			else if (black_is_ai && board.get_Player() == _BLACK_ && !board.get_move_list().empty())
			{
				if (random_moves_made < random_move_count)
				{
					next_move = rand() % board.get_move_list().size();
					random_moves_made++;
				}
				else {
					if(black_pc)
					{
						vector<int> pcmove = piece_count_search(board, 6);
						next_move = pcmove[0];
						val = pcmove[1];
					}
					else
					{
						vector<double> min_max_move = alpha_beta(nn, board, ply, true, -999999, 999999);
						next_move = min_max_move.at(0);
						val = min_max_move[1];
					}
					cout << "black alpha beta move: id(" << next_move << ") val(" << val <<  ")" << endl;
				}
				board.move_piece(next_move);
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
				board.write_board_to_file(to_file);
				window_loop_cycles = 0;
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

		// board drawing
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

		// selector drawing
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

		// sidebar information
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
}
int main() {
	if (main_state == PLAY_CHECKERS)
	{
		fn_play_checkers();
		cout << endl << "GAME OVER >> press ENTER to exit" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (cin.get() != '\n');
		return 0;
	}
	else if (main_state == REPLAY_SAVED_GAME)
	{
		cout << "main_state: REPLAY_SAVED_GAME" << endl << endl;
		int geninp;
		cout << "Please enter a VALID generation (does not handle incorrect input): ";
		cin >> geninp;
		while (true)
		{
			int good_input_count = 0;
			int friendly = -1;
			int enemy;
			while (good_input_count != 2)
			{
				int cbuf;
				if (good_input_count == 0)
				{
					cout << endl << "Please enter the friendly network: ";
				}
				else
				{
					cout << "Network " << friendly << " against: ";
				}
				cin >> cbuf;
				if (cbuf < 0 || cbuf > GLOBAL_MAX_POPULATION_PER_GEN - 1)
				{
					cout << "INVALID INPUT" << endl;
				}
				else if (good_input_count == 0)
				{
					friendly = cbuf;
					good_input_count++;
				}
				else if (good_input_count == 1)
				{
					enemy = cbuf;
					good_input_count++;
				}
			}

			cout << endl << "Replaying Network " << friendly << " against Network " << enemy << endl << endl;
			const string file_name = 
				"ai-playing-checkers\\nn_topologies\\GEN" + 
				to_string(geninp) + 
				"\\games_played\\" +
				to_string(friendly) +
				"_" +
				to_string(enemy) +
				".txt";

			ifstream in_file;
			in_file.open(file_name);

			if (!in_file.is_open())
			{
				cout << "*********************************************************" << endl;
				cout << "ERROR OPENING FILE: PROBABLY NOT READING GAME DATA" << endl;
				cout << "PLEASE CHECK IF THE FILE NAME IS CORRECT FOR YOUR VERSION" << endl;
				cout << "*********************************************************" << endl;
				cout << endl << "press ENTER to quit";
				while (cin.get() != '\n');
				return 0;
			}

			vector<vector<int>> parsed_states;

			string line;
			int token;

			while (getline(in_file, line))
			{
				vector<int> parsed_move;
				stringstream ss(line);

				while (ss >> token)
				{
					parsed_move.push_back(token);
				}
				parsed_states.push_back(parsed_move);
			}

			in_file.close();

			if (parsed_states[parsed_states.size() - 1][0] != 100 &&
				parsed_states[parsed_states.size() - 1][0] != -100 &&
				parsed_states[parsed_states.size() - 1][0] != 50)
			{
				cout << "INCOMPLETE GAME FILE: CANNOT REPLAY GAME" << endl;
				cout << endl << "press ENTER to quit";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (cin.get() != '\n');
				return 0;
			}

			bool player_is_red = false;
			bool red_moved = false;
			bool go_red = false;

			for (int k = 0; k < 12; ++k)
			{
				if (parsed_states[1][k] != -1)
				{
					red_moved = true;
				}
			}
			if (red_moved)
			{
				player_is_red = true;
			}

			if (player_is_red)
			{
				go_red = true;
			}

			int step = 0;
			const int wait_time = 300;

			temp_Board board(_RED_);

			bool last_move = false;

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

			bool stepper = false;

			sf::Event event;

			while (window.isOpen())
			{
				if (stepper)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
				}

				vector<int> board_status;
				board_status.resize(32);


				//*************************************************************************
				// EVENT POLLER -- ADD RUNTIME EVENTS HERE
				//*************************************************************************

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							stepper = !stepper;
							//cout << "stepping: " << stepper << endl;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							//cout << "stepping backward" << endl;
							if (step == 0)
							{
								step = parsed_states.size() - 2;
							}
							else
							{
								--step;
							}
							stepper = false;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							//cout << "stepping forward" << endl;
							if (step == parsed_states.size() - 2)
							{
								step = 0;
							}
							else
							{
								++step;
							}
							stepper = false;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
						{
							if (step == parsed_states.size() - 2 && stepper)
							{
								//cout << "restarting" << endl;
								step = 0;
							}
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						{
							window.close();
							return 0;
						}
					}
					if (event.type == sf::Event::Closed)
					{
						window.close();
					}
				}
				//*************************************************************************
				// END OF EVENT POLLER
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
						int current_status = parsed_states.at(step).at(playable_slot_id);

						switch (current_status)
						{
						case -1:
							piece.setTexture(red_soldier);
							break;
						case -2:
							piece.setTexture(red_king);
							break;
						case 1:
							piece.setTexture(black_soldier);
							break;
						case 2:
							piece.setTexture(black_king);
							break;
						case 0:
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

				if (player_is_red && step % 2 == 0)
				{
					go_red = true;
				}
				else if (player_is_red && step % 2 == 1)
				{
					go_red = false;
				}
				else if (!player_is_red && step % 2 == 0)
				{
					go_red = false;
				}
				else if (!player_is_red && step % 2 == 1)
				{
					go_red = true;
				}

				// window text management
				vector<string> strings_to_draw;
				string player = "null";
				sf::Text player_text(player, font, 30);

				string pieces = "null";
				sf::Text pieces_text(player, font, 30);

				string moves = "null";
				sf::Text moves_text(player, font, 30);

				if (go_red)//board.get_Player() == _RED_)
				{
					player = "RED   TURN";
					player_text.setFillColor(sf::Color::Red);
				}
				else
				{
					player = "BLACK TURN";
					player_text.setFillColor(sf::Color::White);
				}

				if (step == parsed_states.size() - 2)
				{
					if (parsed_states[parsed_states.size() - 1][0] == 100)
					{
						player = "BLACK WINS";
						player_text.setFillColor(sf::Color::White);
					}
					else if (parsed_states[parsed_states.size() - 1][0] == -100)
					{
						player = "RED   WINS";
						player_text.setFillColor(sf::Color::Red);
					}
					else if (parsed_states[parsed_states.size() - 1][0] == 50)
					{
						player = "   DRAW";
						player_text.setFillColor(sf::Color::Cyan);
					}
				}

				board.handle_replay_count(parsed_states.at(step), pieces, pieces_text); // live piece count

				moves = "MOVE #" + to_string(step);
				moves_text.setFillColor(sf::Color::White);

				player_text.setString(player);
				pieces_text.setString(pieces);
				moves_text.setString(moves);

				player_text.setPosition(board_width + 10, 5);
				pieces_text.setPosition(board_width + 10, 100);
				moves_text.setPosition(board_width + 10, 225);

				window.draw(player_text);
				window.draw(pieces_text);
				window.draw(moves_text);

				window.display();

				if (stepper && step < parsed_states.size() - 2)
				{
					++step;
				}
			}
		}

		cout << endl << "END OF REPLAY >> press ENTER to exit";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (cin.get() != '\n');
		return 0;
	}
	else if (main_state == NEURAL_NETWORK_TIMING_PERF)
	{
		OffspringProducer osp;
		const vector<int> input = {
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
		};

		NeuralNetwork_PERF nn0(_RED_);
		nn0.set_input_layer(input);
		nn0.set_topology(osp.generate_random_topology());

		cout.precision(6);
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
		{
			int times = 1000000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
			}
			double avg = t_sum / times;
			cout << times << ": calculation_output elapsed time: " << avg << " ns (";
			avg = avg / 1000000000;
			cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
		}
		{
			int times = 2000000;
			double t_sum = 0;
			for (int i = 0; i < times; ++i) {
				auto begin = std::chrono::high_resolution_clock::now();
				nn0.calculate();
				auto end = std::chrono::high_resolution_clock::now();
				auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
				t_sum += (ns);
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
	else if (main_state == GEN0_GENERATE)
	{
		//string parent_file = "ai-playing-checkers\\nn_topologies\\GEN0\\nn0_brunette26_topology.txt";
		OffspringProducer osp;
		osp.reset_counter();

		for (auto i = 0; i < 30; ++i) {
			osp.generate_random_topology();
			try { osp.record_current(); }
			catch (std::exception & e) { cout << "EXCEPTION CAUGHT: " << e.what() << endl; }
		}
		return 0;
	}
	else if (main_state == GAUSSIAN_GRAPHING)
	{
		//	GnuGraph graph("C:/Program Files/gnuplot/bin/gnuplot.exe"); // provide path to executable
		//	
		//	vector<double> g_vals, width;
		//	map<double, double> vals;
		//	
		//	random_device rnd;
		//	mt19937 e2(rnd());
		//	
		//	normal_distribution<> gauss(0, 1);
		//	
		//	for (int i = 0; i < 1000; ++i)
		//	{
		//		++vals[round(gauss(e2))];
		//	}
		//	
		//	for (auto & p : vals)
		//	{
		//		cout << p.first << ' ' << string(p.second / 200, '*') << '\n';
		//		
		//		g_vals.push_back(p.second);
		//		width.push_back(p.first);
		//	}
		//	
		//	const string output = graph.plot(width, g_vals, "gauss check");
		//	cout << output << '\n'; // print any errors to console
		//	
		//	cout << "press ENTER to quit" << endl;
		//	//cin.clear();
		//	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//	while (cin.get() != '\n');
		//	
		return 0;
	}
	else if (main_state == NNvNN)
	{
		// SETTINGS **************************************
		//************************************************
		int ply = 6;
		int gens_to_train = 5;
		//************************************************
		//************************************************

		ifstream fin;
		ofstream fout;
		ofstream result_out;
		ofstream LNE_fout;
		OffspringProducer osp;
		//NeuralNetwork_PERF nnpr(_RED_);	// network for red player (active network)
		//NeuralNetwork_PERF nnpb(_BLACK_);	// network for black player (oppposing network)
		FileHandler fhand;
		int oppo_list[GLOBAL_OPPO_COUNT];

		result_out.open("ai-playing-checkers\\nn_topologies\\timing.txt", ofstream::out | ofstream::trunc);

		osp.reset_counter();
		cout.precision(6);

		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_int_distribution<> int_dist(0, GLOBAL_MAX_POPULATION_PER_GEN - 1);

		cout << "TRAINING BEGIN\n\n";

		//clock start
		const auto begin = std::chrono::high_resolution_clock::now();
		while (osp.get_current_generation_id() != gens_to_train)
		{
			const auto begin_gen = std::chrono::high_resolution_clock::now();

			const auto gen = osp.get_current_generation_id();
			cout << "training GEN" << gen << "..." << endl;
			const auto gen_str = to_string(gen);
			const auto gen_wrapper = "ai-playing-checkers\\nn_topologies\\GEN" + gen_str;
			const auto result_txt = gen_wrapper + "\\games_played\\_result.txt";

			// iterate through all 30 networks
			for (auto active_nn_id = 0; active_nn_id < GLOBAL_MAX_POPULATION_PER_GEN; ++active_nn_id)
			{
				string result_out = to_string(active_nn_id);

				//populating opponent list
				for (auto i = 0; i < GLOBAL_OPPO_COUNT; ++i)
				{
					int oppo = int_dist(e1);

					// nn should not play against self
					while (oppo == active_nn_id) {
						oppo = int_dist(e1);
					}
					// nn should not play the same oppo
					for (auto j = 0; j < i; ++j) {
						if (oppo == oppo_list[j])
						{
							oppo = int_dist(e1);
							break;
						}
					}

					oppo_list[i] = oppo;
					result_out += " ";
					result_out += to_string(oppo);
				}

				result_out += " ";

				// setting "our side" topology string
				string active_nn_topo = gen_wrapper;
				active_nn_topo += "\\nn";
				active_nn_topo += to_string(active_nn_id);
				active_nn_topo += "_brunette26_topology.txt";

				const vector<size_t> topo_layout { 32, 40, 10, 1 };
				try { fhand.set_file(active_nn_topo); }
				catch (...)
				{
					cout << "fhand set_file throw for active" << endl;
				}


				skynet::neuralnet_t nnred(topo_layout, fhand.get_weights(), fhand.get_king()); 

				for (auto i = 0; i < GLOBAL_OPPO_COUNT; ++i) {
					const auto oppo_nn_id = oppo_list[i];

					// setting "against" topology string
					string against_nn_topo = "";
					against_nn_topo += gen_wrapper;
					against_nn_topo += "\\nn";
					against_nn_topo += to_string(oppo_nn_id);
					against_nn_topo += "_brunette26_topology.txt";

					try { fhand.set_file(against_nn_topo); }
					catch (...)
					{
						cout << "fhand set file throw for against" << endl;
					}

					skynet::neuralnet_t nnblk(topo_layout, fhand.get_weights(), fhand.get_king());

					string game_played_destination = "ai-playing-checkers\\nn_topologies\\GEN" + gen_str;
					game_played_destination += "\\games_played\\";
					game_played_destination += to_string(active_nn_id);
					game_played_destination += "_";
					game_played_destination += to_string(oppo_nn_id);
					game_played_destination += ".txt";

					// board set up
					temp_Board board(_BLACK_); // black is starting player
					const int random_move_count = 3;
					int move_count = 0;
					int next_move = -1;
					// game begin
					fout.open(game_played_destination, ofstream::out | ofstream::app);
					if (!fout.is_open())
					{
						cout << "game_played_destination declared in main.cpp not opened: " << game_played_destination << endl;
						return 0;
					}

					board.write_board_to_file(fout); // initial gameboard

					//const auto begin_game = std::chrono::high_resolution_clock::now();

					while (!board.is_over() && move_count < 100)
					{
						//const auto move_begin = std::chrono::high_resolution_clock::now();
						mms_eval_count = 0;
						ab_eval_count = 0;
						call_count = 1;

						if (move_count < random_move_count) next_move = rand() % board.get_move_list().size();

						else if (board.get_Player() == _RED_ && !board.get_move_list().empty()) {
							//const auto begin_calc = std::chrono::high_resolution_clock::now();
							vector<double> alpha_beta_move = alpha_beta(nnred, board, ply, false, -10000, 10000);
							//const auto end_calc = std::chrono::high_resolution_clock::now();
							//const auto ns_calc = std::chrono::duration_cast<std::chrono::nanoseconds>(end_calc - begin_calc).count();
							//const auto s_per_calc = double(ns_calc) / double(1000) / double(1000000);
							// << s_per_calc << endl;
							next_move = alpha_beta_move[0];
						}

						else if (board.get_Player() == _BLACK_ && !board.get_move_list().empty()) {
							vector<double> alpha_beta_move = alpha_beta(nnblk, board, ply, true, -10000, 10000);
							next_move = alpha_beta_move[0];

							//const auto begin_calc = std::chrono::high_resolution_clock::now();
							//double * min_max_move = alpha_beta(nnpb, board, ply, -10000, 10000);
							//const auto end_calc = std::chrono::high_resolution_clock::now();
							//const auto ns_calc = std::chrono::duration_cast<std::chrono::nanoseconds>(end_calc - begin_calc).count();
							//const auto s_per_calc = double(ns_calc) / double(1000) / double(1000000);
							//cout << s_per_calc << endl;
							//next_move = min_max_move[0];
						}

						if(next_move != -1) board.move_piece(next_move);
						board.write_board_to_file(fout);
						move_count++;
						//const auto move_end = std::chrono::high_resolution_clock::now();
						//const auto ns_move = std::chrono::duration_cast<std::chrono::nanoseconds>(move_end - move_begin).count();
						//const auto s_per_move = double(ns_move) / double(1000) / double(1000000);

						//if (move_count > 3) { // 0 == starting, 1~3 == random, 4 == first AI move
						//	LNE_fout << "move_id: " << move_count;
						//	LNE_fout << " eval_count: " << eval_count;
						//	LNE_fout << " fn_call_count: " << call_count;
						//	LNE_fout << " nonleaf_leaf: " << call_count - eval_count << ":" << eval_count;
						//	LNE_fout << " leaf_percent: " << double(eval_count) / double(call_count) * 100;
						//	LNE_fout << " over_seconds: " << s_per_move;
						//	LNE_fout << " eval/sec: " << eval_count / s_per_move << endl;
						//}
					}

					// denote draw status
					if (move_count == 100)
					{
						fout << "50";
						GLOBAL_WINNER_DENOTER = '0';
					}

					result_out += GLOBAL_WINNER_DENOTER;
					result_out += ' ';

					fout.close();

					//const auto end_game = std::chrono::high_resolution_clock::now();
					//const auto ns_game = std::chrono::duration_cast<std::chrono::nanoseconds>(end_game - begin_game).count();
					//const auto min_per_game = double(ns_game) / double(1000) / double(1000000) / double(60);
					//cout << move_count << " " << ply << "-ply game played in: " << min_per_game << " min (" << min_per_game * 60 << " sec)" << endl;
				}

				fout.open(result_txt, ofstream::out | ofstream::app);
				if (!fout.is_open())
				{
					cout << "cannot open result.txt in main" << endl;
					return 0;
				}
				fout << result_out << endl;
				fout.close();
			}
			// after 150 games, advancing generation and producing offspring
			try { osp.determine_survivors(result_txt); }
			catch (...)
			{
				cout << "determine survivor throw" << endl;
			}
			try { osp.produce_next_generation(); }
			catch (...)
			{
				cout << "produce next gen throw" << endl;
			}
			const auto end_gen = std::chrono::high_resolution_clock::now();
			const auto ns_gen = std::chrono::duration_cast<std::chrono::nanoseconds>(end_gen - begin_gen).count();
			const auto min_per_gen = double(ns_gen) / double(1000) / double(1000000) / double(60);
			const auto maincpp_gen = osp.get_current_generation_id();
			cout << "    " << maincpp_gen - 1 << " -> " << maincpp_gen << " generation advanced: " << min_per_gen << " min" << endl;
			result_out << maincpp_gen - 1 << " -> " << maincpp_gen << " generation advanced: " << min_per_gen << " min" << endl;
		}
		//clock end
		const auto end = std::chrono::high_resolution_clock::now();
		const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		const auto min = double(ns) / double(1000) / double(1000000) / double(60);
		cout << "estimated total time taken: " << min << endl;
		//LNE_fout.close();
		cout << "\nTRAINING SUCCESS" << endl;
		while (cin.get() != '\n');
		return 0;
	}
	else if (main_state == NNP_TEST)
	{
		const string ai_topo = "ai-playing-checkers\\nn_topologies\\GEN0\\nn0_brunette26_topology.txt";
		vector<int> nn_input_0
		{
			0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0
		};
		vector<int> nn_input_1
		{
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1
		};
		vector<int> nn_input_2
		{
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			-1,-1,-1,-1,
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1
		};

		FileHandler fh;
		OffspringProducer osp;
		temp_Board board(_RED_);

		fh.set_file(ai_topo);
		vector<double> weights = fh.get_weights();
		vector<double> sigmas = fh.get_sigmas();
		const vector<size_t> topo_layout { 32, 40, 10, 1 };

		skynet::neuralnet_t nnred(topo_layout, fh.get_weights(), fh.get_king());
		vector<double> minimax = alpha_beta(nnred, board, 6, false, -10000, 10000);
		cout << minimax[0] << " " << minimax[1] << endl;
		//osp.set_topology(ai_topo);

		//nnp.set_topology(osp.get_topology());
		//nnp.calculate();
		//cout << nnp.get_result() << endl;
		return 0;
	}
	else if (main_state == NETWORK)
	{
		int player_enum;
		string game_name;
		FileHandler fh;
		string topo = "mostrecent\\nn27_brunette26_topology.txt";

		cout << "main_mode NETWORK\n";

		try { fh.set_file(topo); }
		catch (...)
		{
			cout << "exception caught" << endl;
			return 0;
		}

		cout << "ENTER THE GAME NAME: ";
		cin >> game_name;
		cout << "THIS SIDE NETWORK IS RED(0) OR BLACK(1): ";
		cin >> player_enum;

		int ply = 6;
		int starting_player = _RED_;

		ofstream fout;
		ifstream fin;
		fout.open("network_game.txt", ofstream::out | ofstream::trunc);

		temp_Board board(starting_player);
		//nnp.set_topology(osp.get_topology());
		board.write_board_to_file(fout);

		int red_turn = 0;
		int black_turn = 1;
		int turn_id = 0;

		auto game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);
		//skynet::checkers::play_game("skynet.cs.uaf.edu", game_name, "rrrrrrrrrrr____r____bbbbbbbbbbbb");
		skynet::neuralnet_t nn({ 32, 40, 10 ,1 }, fh.get_weights(), fh.get_king());
		int next_move;
		while (!board.is_over()) {
			game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);
			string board_to_eval_str;

			while (game.status != player_enum) {
				/* wait */
				cout << "waiting as black" << endl;
				game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);
			}
			cout << "turn id" << turn_id << endl;

			if(turn_id == 0 && player_enum == 1)
			{
				cout << "moving red's first" << endl;
				game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);
				board_to_eval_str = game.boards[game.boards.size() - 1];
				cout << "red: " << board_to_eval_str << endl;
				vector<int> ene_move = process_to_nn_vec(board_to_eval_str);
				auto possible = board.get_move_list();
				int ene_move_id;
				for(auto i = 0; i < possible.size(); ++i)
				{
					if(find_move(board_to_eval_str, board, i) != -1)
					{
						cout << "found" << endl;
						ene_move_id = i;
						break;
					}
					else
					{
						cout << "invalid detect" << endl;
					}
				}
				board.move_piece(ene_move_id);
				turn_id++;
				cout << "red first ok" << endl;
			}

			if(turn_id <= 3)
			{
				cout << "random move" << endl;
				next_move = rand() % board.get_move_list().size();
				board.move_piece(next_move);
				cout << "called move" << endl;
				vector<int> current_move = board.get_board_as_vector();
				string skynet_input = process_to_json_string(current_move);
				cout << "sending" << endl;
				skynet::checkers::play_game("skynet.cs.uaf.edu", game_name, skynet_input);
				turn_id++;
				cout << "random ok" << endl;
			}
			else {
				cout << "normal move" << endl;
				board_to_eval_str = game.boards[game.boards.size() - 1]; // to pass into an eval func
				vector<int> input_board = process_to_nn_vec(board_to_eval_str);
				//vector<int> move_pair = piece_count_search(board, ply);
				vector<double> move_pair = alpha_beta(nn, board, ply, false, -999999, 999999);
				next_move = move_pair[0];
				board.move_piece(next_move);
				//board.write_board_to_file(fout);
				vector<int> current_move = board.get_board_as_vector();
				string skynet_input = process_to_json_string(current_move);
				skynet::checkers::play_game("skynet.cs.uaf.edu", game_name, skynet_input);
				turn_id++;
				cout << "normal ok" << endl;
			}
		
			game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);

			while (game.status != player_enum)
			{
				cout << "waiting for other" << endl;
				game = skynet::checkers::info_game("skynet.cs.uaf.edu", game_name);
				if(board.is_over())
				{
					cout << "game over" << endl;
					return 0;
				}
			}

			cout << "process enemy" << endl;
			board_to_eval_str = game.boards[game.boards.size() - 1]; // to pass into an eval func
			vector<int> ene_move = process_to_nn_vec(board_to_eval_str);
			auto possible = board.get_move_list();
			int ene_move_id;
			for(auto i = 0; i < possible.size(); ++i)
			{
				if(find_move(board_to_eval_str, board, i) != -1)
				{
					ene_move_id = i;
					break;
				}
				else
				{
					cout << "invalid detect" << endl;
				}
			}
			board.move_piece(ene_move_id);
			turn_id++;
			//vector<int> move_pair2 = piece_count_search(board, ply);
			//next_move = move_pair2[0];
			//board.move_piece(next_move);
			////board.write_board_to_file(fout);
			//current_move = board.get_board_as_vector();
			//skynet_input = process_to_json_string(current_move);
			//skynet::checkers::play_game("skynet.cs.uaf.edu", game_name, skynet_input);
			//turn_id++;
		}
		//auto game000 = skynet::checkers::info_game("skynet.cs.uaf.edu", "000");
		//std::cout << "test " << std::to_string(game000.status) << game000.status << std::endl;
		//skynet::checkers::play_game("skynet.cs.uaf.edu", "000", "rrrrrrrr_rrr_r______bbbbbbbbbbbb");
		return 0;
	}
	cout << "You should not be here." << endl;
	cout << endl << "press ENTER to quit" << endl;
	while (cin.get() != '\n');
	return 0;
}
