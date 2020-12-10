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

namespace day9 {
	using namespace std;
	using op_value_type = long long;

	tuple<op_value_type, op_value_type> get_encoding_info(istream& file) {
		string line;
		vector<op_value_type> values;
		int preamble = 25;

		while (getline(file, line)) {
			values.push_back(stoll(line));
		}

		int curr_ind = preamble + 1;
		op_value_type first_non_ok = 0;
		while (curr_ind < values.size()) {
			bool ok_val = false;
			for (int i = curr_ind - preamble; i < curr_ind && !ok_val; ++i) {
				for (int j = i + 1; j < curr_ind && !ok_val; ++j) {
					if ((values[i] + values[j]) == values[curr_ind]) {
						ok_val = true;
						break;
					}
				}
			}
			if (!ok_val) {
				first_non_ok = values[curr_ind];
			}
			curr_ind++;
		}

		int lower_bound = 0;
		op_value_type curr_sum = 0;
		op_value_type bound_sum = 0;
		while (lower_bound < values.size()) {
			curr_sum = 0;
			bool ok_val = false;
			int upper_bound = lower_bound;
			op_value_type lowest = values[lower_bound];
			op_value_type highest = values[lower_bound];
			while (upper_bound < values.size() && curr_sum < first_non_ok) {
				curr_sum += values[upper_bound];
				if (values[upper_bound] < lowest) {
					lowest = values[upper_bound];
				}
				if (values[upper_bound] > highest) {
					highest = values[upper_bound];
				}
				++upper_bound;
			}
			if ((upper_bound - lower_bound) >= 2 && curr_sum == first_non_ok) {
				bound_sum = lowest + highest;
			}
			lower_bound++;
		}

		return { first_non_ok, bound_sum };
	}
}
