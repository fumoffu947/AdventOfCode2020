// AdventOfCode2020.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <any>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <tuple>
#include "src/utils.h"
#include <vector>
using namespace std;

#include "src/report_repair.h"
#include "src/password_philosophy.h"
#include "src/toboggan_traj.h"
#include "src/passport_processing.h"
#include "src/binary_boarding.h"
#include "src/custom_customs.h"
#include "src/handy_haversacks.h"
#include "src/handheld_halting.h"
#include "src/encoder_error.h"
#include "src/adapter_array.h"
#include "src/seting_system.h"
#include "src/rain_risk.h"

// Need global for the function list to be able to take the lambdas
vector<any> functionResult(25);
vector<string> executionTimeForCuntion{ 25 };

int main()
{
	vector<void(*)(int index)> threadFunctions{
		[](int index) {
		// Day 1
		PrecisionTimer timer;
		timer.tick();
		ifstream fs("Resources/ProblemDay1.txt");
		tuple<int, int> sum_info = day1::get_sum_info(fs);
		functionResult[index] = sum_info;
		executionTimeForCuntion[index] = timer.tock();
		fs.close();
		},
		[](int index) {
			// Day 2
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay2.txt");
			tuple<int, int> passw_info = get_password_info(fs);
			functionResult[index] = passw_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 3
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay3.txt");
			tuple<long long, long long> toboggan_info = day3::get_toboggan_info(fs);
			functionResult[index] = toboggan_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 4
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay4.txt");
			tuple<int, int> passport_validation = day4::get_passport_validation_info(fs);
			functionResult[index] = passport_validation;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 5
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay5.txt");
			tuple<int, int> plane_seatings = day5::get_boarding_seat(fs);
			functionResult[index] = plane_seatings;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 6
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay6.txt");
			tuple<int, int> declaration_from_info = day6::get_declaration_form_answers(fs);
			functionResult[index] = declaration_from_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 7
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay7.txt");
			tuple<int, int> shiny_gold_bag_info = day7::get_bag_info(fs);
			functionResult[index] = shiny_gold_bag_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 8
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay8.txt");
			tuple<int, int> boot_prog_info = day8::get_program_info(fs);
			functionResult[index] = boot_prog_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 9
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay9.txt");
			tuple<long long, long long> encoding_info = day9::get_encoding_info(fs);
			functionResult[index] = encoding_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 10
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay10.txt");
			tuple<long long, long long> adapter_info = day10::get_adapter_info(fs);
			functionResult[index] = adapter_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
		[](int index) {
			// Day 11
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay11.txt");
			tuple<int, int> seat_info = day11::get_seat_info(fs);
			functionResult[index] = seat_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 12
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay12.txt");
			tuple<int, int> boat_pos_info = day12::get_boat_info(fs);
			functionResult[index] = boat_pos_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		}
	};

	vector<void(*)(any value, string executionTime)> threadPrintFunctions{
		[](any value, string executionTime) {
			tuple<int, int> sum_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 1  ----------------" << endl;
			std::cout << "The multiplication of the two values that sum to 2020 is : " << get<0>(sum_info) << " the multiplication of three values that sum to 2020 is : " <<
				get<1>(sum_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> passw_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 2  ----------------" << endl;
			std::cout << "The number of passwords ok according to policy one is : " << get<0>(passw_info) << " the number of passwords ok according to policy two is : " <<
				get<1>(passw_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<long long, long long> toboggan_info = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 3  ----------------" << endl;
			std::cout << "The number of trees hit with traj (3,1) is : " << get<0>(toboggan_info) << " the multiplication of all trajectories is: " <<
				get<1>(toboggan_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> passport_validation = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 4  ----------------" << endl;
			std::cout << "The number of passports that have the reqiured fields are : " << get<0>(passport_validation) << " the number of valid passports are: " <<
				get<1>(passport_validation) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> plane_seatings = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 5  ----------------" << endl;
			std::cout << "The seat id that is highest is : " << get<0>(plane_seatings) << " my seat number is: " <<
				get<1>(plane_seatings) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> declaration_form_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 6  ----------------" << endl;
			std::cout << "The sum of questions unique in the groups are : " << get<0>(declaration_form_info) << " the sum of question common for the each group is : " <<
				get<1>(declaration_form_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> shiny_gold_bag_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 7  ----------------" << endl;
			std::cout << "The number of bags containing a shiny gold bag is : " << get<0>(shiny_gold_bag_info) << " the number of bags in a shiny gold bag is : " <<
				get<1>(shiny_gold_bag_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> boot_prog_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 8  ----------------" << endl;
			std::cout << "The accumulator value before a line i executed again is : " << get<0>(boot_prog_info) << " the accumulator value after fix (prog end) is: " <<
				get<1>(boot_prog_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<long long, long long> encoding_info = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 9  ----------------" << endl;
			std::cout << "The error number is : " << get<0>(encoding_info) << " the bounds of the range summing up to the error number is: " <<
				get<1>(encoding_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<long long, long long> adapter_info = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 10  ----------------" << endl;
			std::cout << "The number of adapters with differense 1 and 3 multiplied is : " << get<0>(adapter_info) << " the number of different permutaions of adapters that are valid is : " <<
				get<1>(adapter_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> seat_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 11  ----------------" << endl;
			std::cout << "The number of seat occupied after equilibrium reqched with normal rules is : " << get<0>(seat_info) << " the number of seat occupied after equilibrium reqched with advanced rules is : " <<
				get<1>(seat_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> boat_pos_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 12  ----------------" << endl;
			std::cout << "The manhattan distance to the boat destination with first steering rules is : " << get<0>(boat_pos_info) << " the manhattan distance to the boat destination with first steering rules is : " <<
				get<1>(boat_pos_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		}
	};

	vector<thread> threadVector;

	PrecisionTimer timerMain;
	timerMain.tick();

	bool skippThreads = false;

	//stringstream fs("409551");
	//ifstream fs("Resources/example.txt");
	//ifstream fs("Resources/ProblemDay12.txt");
	//tuple<long long, long long> res = day12::get_boat_info(fs);
	//cout << get<0>(res) << " : " << get<1>(res) << endl;

	cout << "Helping Santa, calculating problems..." << endl;
	// Start all the problem solutions
	for (unsigned int threadIndex = 0; !skippThreads && threadIndex < threadFunctions.size(); threadIndex++) {
		thread currThread{ threadFunctions[threadIndex], threadIndex };
		threadVector.push_back(move(currThread));
	}

	// Wait for the result from all the solutions
	for (int threadIndex = 0; !skippThreads && threadIndex < threadFunctions.size(); threadIndex++) {
		threadVector[threadIndex].join();
		threadPrintFunctions[threadIndex](functionResult[threadIndex], executionTimeForCuntion[threadIndex]);
	}

	std::cout << "The total run time is: " << timerMain.tock() << endl;
	std::cin.get();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
