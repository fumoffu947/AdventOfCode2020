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
#include "src/shuttle_search.h"
#include "src/docking_data.h"
#include "src/rambunctious_recitation.h"
#include "src/ticker_translation.h"
#include "src/conway_cubes.h"
#include "src/operation_order.h"
#include "src/monster_messages.h"
#include "src/jurassic_jigsaw.h"
#include "src/allergen_assessment.h"

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
		},
			[](int index) {
			// Day 13
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay13.txt");
			tuple<long long, long long> bus_schedule_info = day13::get_bus_schedule_info(fs);
			functionResult[index] = bus_schedule_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 14
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay14.txt");
			tuple<unsigned long long, unsigned long long> docking_init_data = day14::get_docking_data(fs);
			functionResult[index] = docking_init_data;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 15
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay15.txt");
			tuple<int, int> mem_game_info = day15::get_mem_game_info(fs);
			functionResult[index] = mem_game_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close(); 
		},
			[](int index) {
			// Day 16
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay16.txt");
			tuple<long long, long long> ticket_info = day16::get_ticket_info(fs);
			functionResult[index] = ticket_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 17
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay17.txt");
			tuple<int, int> energy_grid_info = day17::get_energy_info(fs);
			functionResult[index] = energy_grid_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 18
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay18.txt");
			tuple<long long, long long> equations_info = day18::get_math_result(fs);
			functionResult[index] = equations_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 19
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay19.txt");
			tuple<int, int> messages_info = day19::get_message_info(fs);
			functionResult[index] = messages_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 20
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay20.txt");
			tuple<unsigned long long, unsigned long long> satelite_info = day20::get_camera_tile_info(fs);
			functionResult[index] = satelite_info;
			executionTimeForCuntion[index] = timer.tock();
			fs.close();
		},
			[](int index) {
			// Day 21
			PrecisionTimer timer;
			timer.tick();
			ifstream fs("Resources/ProblemDay21.txt");
			tuple<int, string> ingredients_info = day21::get_ingredient_info(fs);
			functionResult[index] = ingredients_info;
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
		},
		[](any value, string executionTime) {
			tuple<long long, long long> bus_schedule_info = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 13  ----------------" << endl;
			std::cout << "The the time to the earliest times the id is : " << get<0>(bus_schedule_info) << " the first time the buses right after each other is : " <<
				get<1>(bus_schedule_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<unsigned long long, unsigned  long long> docking_init_data = any_cast<tuple<unsigned long long, unsigned long long>>(value);
			std::cout << endl << "----------------  Day 14  ----------------" << endl;
			std::cout << "The sum of the docking initialisation values is : " << get<0>(docking_init_data) << " the sum of the docking initialisation values with addres maskingis : " <<
				get<1>(docking_init_data) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> mem_game_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 15  ----------------" << endl;
			std::cout << "The 2020th number of the memory game is : " << get<0>(mem_game_info) << " the 30 000 000th number of the memory game is : " <<
				get<1>(mem_game_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<long long, long long> ticket_into = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 16  ----------------" << endl;
			std::cout << "The the error sum of the unvalid tickets is : " << get<0>(ticket_into) << " the multiplication of the departure fiels is : " <<
				get<1>(ticket_into) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> energy_grid_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 17  ----------------" << endl;
			std::cout << "The number of active cubes with 3 dimentions after 6 iterations is : " << get<0>(energy_grid_info) << " the number of active cubes with 4 dimentions after 6 iterations is : " <<
				get<1>(energy_grid_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<long long, long long> equations_info = any_cast<tuple<long long, long long>>(value);
			std::cout << endl << "----------------  Day 18  ----------------" << endl;
			std::cout << "The sum of the math equation results with first set of rules is : " << get<0>(equations_info) << " the sum of the math equation results with second set of rules is : " <<
				get<1>(equations_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, int> equations_info = any_cast<tuple<int, int>>(value);
			std::cout << endl << "----------------  Day 19  ----------------" << endl;
			std::cout << "The number of messages that match without loops is : " << get<0>(equations_info) << " the number of messages that match with loops is : " <<
				get<1>(equations_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<unsigned long long, unsigned long long> equations_info = any_cast<tuple<unsigned long long, unsigned long long>>(value);
			std::cout << endl << "----------------  Day 20  ----------------" << endl;
			std::cout << "The multiplication of corner ids is : " << get<0>(equations_info) << " the number of squares excluding the monsters is : " <<
				get<1>(equations_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		},
		[](any value, string executionTime) {
			tuple<int, string> ingredients_info = any_cast<tuple<int, string>>(value);
			std::cout << endl << "----------------  Day 21  ----------------" << endl;
			std::cout << "The number of times an allergen free ingredient appears is : " << get<0>(ingredients_info) << " the ingredients sorted by the containing allergen are : " <<
				get<1>(ingredients_info) << endl << "The calculations took: " << executionTime << endl;
			std::cout << "-----------------------------------------" << endl;
		}
	};

	vector<thread> threadVector;

	PrecisionTimer timerMain;
	timerMain.tick();

	bool skippThreads = false;

	//stringstream fs("409551");
	//ifstream fs("Resources/example.txt");
	//ifstream fs("Resources/ProblemDay21.txt");
	//tuple<int, string> res = day21::get_ingredient_info(fs);
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
