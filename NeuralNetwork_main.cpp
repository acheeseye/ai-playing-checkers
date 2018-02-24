//#include "NeuralNetwork.h"
//#include "board.h"
//
//#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//using std::streamsize;
//#include <string>
//using std::string;
//using std::to_string;
//#include <limits>
//using std::numeric_limits;
//#include <vector>
//using std::vector;
//#include <time.h>
//#include <chrono>
//
//clock_t t;
//
//
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
//int main()
//{
//	NeuralNetwork nn0;
//	nn0.init();
//	nn0.set_board_record_with("ai-playing-checkers\\games_played\\game_20180219_142934.txt");
//
//	cout.precision(6);
//	cout << "nn0 weights: " << GLOBAL_WEIGHT_COUNT << endl;
//	{
//		int times = 10;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 100;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 1000;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 10000;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 100000;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 200000;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//	{
//		int times = 250000;
//		double t_sum = 0;
//		for (int i = 0; i < times; ++i) {
//			nn0.set_input_layer(0);
//			auto begin = std::chrono::high_resolution_clock::now();
//			nn0.calculate_output();
//			auto end = std::chrono::high_resolution_clock::now();
//			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
//			t_sum += (ns);
//			//cout << nn0.get_output() << endl;
//		}
//		double avg = t_sum / times;
//		cout << times << ": calculation_output elapsed time: " << avg << " ns (";
//		avg = avg / 1000000000;
//		cout << 1.0 / avg << " BEF/sec, " << 1.0 / avg * 15 << " BEF/15 sec)" << endl;
//	}
//
//	cout << endl;
//	cout << "'Enter' to quit . . .";
//	while (cin.get() != '\n');
//
//	return 0;
//}