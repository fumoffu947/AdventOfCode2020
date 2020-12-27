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
#include <iomanip>
#include <queue>

namespace day25 {
	using namespace std;
	using op_value_type = long long;

	op_value_type find_loop_size(op_value_type transform_res, op_value_type div_val, op_value_type subject_num) {
		op_value_type loop_size = 0;
		op_value_type res = 1;
		while (res != transform_res) {
			res *= subject_num;
			res %= div_val;
			loop_size++;
			if (loop_size % 100000 == 0) {
			}
		}
		return loop_size;
	}

	op_value_type transform_num(op_value_type loop_size, op_value_type div_val, op_value_type subject_num) {
		op_value_type i = 0;
		op_value_type res = 1;
		while (i < loop_size) {
			res *= subject_num;
			res %= div_val;
			i++;
		}
		return res;
	}

	tuple<op_value_type, op_value_type> get_encryption_info(istream& file) {
		string line;

		op_value_type transform_div = 20201227, subject_num = 7;
		op_value_type card_public_key, door_public_key;

		getline(file, line);
		card_public_key = stoi(line);
		getline(file, line);
		door_public_key = stoi(line);

		op_value_type card_loop_size = find_loop_size(card_public_key, transform_div, subject_num);
		op_value_type door_loop_size = find_loop_size(door_public_key, transform_div, subject_num);

		op_value_type card_encryption_key = transform_num(card_loop_size, transform_div, door_public_key);
		op_value_type door_encryption_key = transform_num(door_loop_size, transform_div, card_public_key);

		return  { card_encryption_key, 0 };
	}

}
