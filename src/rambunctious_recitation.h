#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>
#include <set>
#include <string>
#include <valarray>
#include <regex>
#include <map>
#include <cmath>
#include <numeric>
#include <bitset>

namespace day15 {
	using namespace std;
	using op_value_type = int;

	tuple<op_value_type, op_value_type> get_mem_game_info(istream& file) {
		string line;
		int curr_ind = 0;
		map<op_value_type, op_value_type> num_mem;
		vector<op_value_type> num_seq;
		op_value_type prev_val = -1;
		int wanted_seq = 2020;
		int wanted_second = 30000000;

		getline(file, line, ',');
		prev_val = stol(line);

		while (getline(file, line, ',')) {
			op_value_type val = stol(line);
			num_mem[prev_val] = curr_ind;
			curr_ind++;
			prev_val = val;
		}

		while (curr_ind < wanted_seq-1) {
			if (num_mem.find(prev_val) != num_mem.end()) {
				op_value_type tmp = curr_ind - num_mem[prev_val];
				num_mem[prev_val] = curr_ind;
				prev_val = tmp;
			}
			else {
				num_mem[prev_val] = curr_ind;
				prev_val = 0;
			}
			curr_ind++;
		}
		op_value_type the_2020th_num = prev_val;

		while (curr_ind < wanted_second - 1) {
			if (num_mem.find(prev_val) != num_mem.end()) {
				op_value_type tmp = curr_ind - num_mem[prev_val];
				num_mem[prev_val] = curr_ind;
				prev_val = tmp;
			}
			else {
				num_mem[prev_val] = curr_ind;
				prev_val = 0;
			}
			curr_ind++;
		}

		op_value_type the_30000000th_num = prev_val;

		return { the_2020th_num, the_30000000th_num };
	}
}