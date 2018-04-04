// main.cpp
// cs 405/605 introduction to ai spring 2018
// ai playing checkers project
// members: jason hsi, jesse keller, and addeline mitchell
// created jan 23, 2018

// INCLUDES
#include "board.h"
#include "NeuralNetwork_PERF.h"
#include "offspringproducer.h"

#include <time.h>

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <limits>
#include <chrono>
#include <random>
#include <sstream>
#include <thread>

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
using std::stringstream;

bool GLOBAL_DO_WRITE = true;
char GLOBAL_WINNER_DENOTER;
int mms_eval_count;
int ab_eval_count;
int call_count;

//**********************************************************************************************
//CHANGE main_state VARIABLE TO DESIRED MAIN
//MAINS MERGED ON 2/23/2018
//**********************************************************************************************
int main_state = NEURAL_NETWORK_TIMING_PERF;
//**********************************************************************************************
//**********************************************************************************************
//**********************************************************************************************
//**********************************************************************************************

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

int main() {
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