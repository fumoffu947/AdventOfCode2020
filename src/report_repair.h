#pragma once
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <string>

namespace day1 {
	using namespace std;
	using op_value_type = int;

	tuple<op_value_type, op_value_type> get_sum_info(istream& file) {
		string line;
		vector<op_value_type> values;
		int sum_val = 2020;

		while (getline(file, line)) {
			values.push_back(stoi(line));
		}

		int res_sum_mul = 0;
		int res_sum_mul_three = 0;
		bool done = false;
		bool first_done = false;
		for (int i = 0; i < values.size() && !done; ++i) {
			for (int j = i + 1; j < values.size() && !done; ++j) {
				if (!first_done && (values[i] + values[j]) == sum_val) {
					res_sum_mul = values[i] * values[j];
					first_done = true;

				}
				for (int k = j + 1; k < values.size() && !done; ++k) {
					if ((values[i] + values[j] + values[k]) == sum_val) {
						res_sum_mul_three = values[i] * values[j] * values[k];
						first_done = true;

					}
				}
			}
		}

		return { res_sum_mul, res_sum_mul_three };
	}
}