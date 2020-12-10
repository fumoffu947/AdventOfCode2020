#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <string>
#include <valarray>
#include <regex>

namespace day5 {
	using namespace std;
	using op_value_type = int;

	tuple<op_value_type, op_value_type> get_boarding_seat(istream& file) {
		string line;
		op_value_type row_count = 128;
		op_value_type col_count = 8;
		vector<string> taken_seats(row_count, "........");
		vector<string> seat_placements;

		while (getline(file, line)) {
			seat_placements.push_back(line);
		}

		op_value_type highest_seat_id = 0;
		vector<op_value_type> seat_ids;
		for (string seat_place : seat_placements) {
			op_value_type curr_row = 0;
			op_value_type left_space = row_count;
			for (int i = 0; i < 7; ++i) {
				if (seat_place[i] == 'F') {
					curr_row += 0;
				}
				if (seat_place[i] == 'B') {
					curr_row += left_space / 2;
				}
				left_space /= 2;
			}

			op_value_type curr_col = 0;
			left_space = col_count;
			for (int i = 7; i < 10; ++i) {
				if (seat_place[i] == 'L') {
					curr_col += 0;
				}
				if (seat_place[i] == 'R') {
					curr_col += left_space / 2;
				}
				left_space /= 2;
			}

			taken_seats[curr_row][curr_col] = '-';

			op_value_type curr_seat_id = curr_row * 8 + curr_col;
			if (curr_seat_id > highest_seat_id) {
				highest_seat_id = curr_seat_id;
			}
			seat_ids.push_back(curr_seat_id);
		}

		sort(seat_ids.begin(), seat_ids.end());

		int my_seat_id = 0;
		for (int i = 0; i < seat_ids.size()-1; ++i) {
			if (seat_ids[i + 1] - seat_ids[i] == 2) {
				my_seat_id = seat_ids[i] + 1;
			}
		}

		return { highest_seat_id, my_seat_id };
	}
}