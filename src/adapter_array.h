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

namespace day10 {
	using namespace std;
	using op_value_type = long long;

	bool valid_off(vector<op_value_type>& adapters, vector<int>& locked, vector<int>& on_off, int ind) {
		bool ok = false;
		op_value_type above = adapters[adapters.size() - 1], below = -10;
		for (int i = ind - 1; i > ind - 4 && i >= 0; --i) {
			if (on_off[i]) {
				below = adapters[i];
				break;
			}
		}
		for (int i = ind + 1; i < ind + 4 && i < adapters.size(); ++i) {
			if (on_off[i]) {
				above = adapters[i];
				break;
			}
		}
		return (above - below) < 4;
	}

	op_value_type find_permutations(vector<op_value_type> &adapters, vector<int> &locked, vector<int> &on_off, int ind, map<int, op_value_type>& mem_bank) {
		op_value_type res = 0;
		if (ind >= adapters.size()) {
			return 1;
		}

		if (!locked[ind]) {
			//ok off
			if (valid_off(adapters, locked, on_off, ind)) {
				on_off[ind] = 0;
				res = find_permutations(adapters, locked, on_off, ind + 1, mem_bank);
				on_off[ind] = 1;
			}
			//ok on
			res += find_permutations(adapters, locked, on_off, ind + 1, mem_bank);

		}
		else {
			//Use old values you already calculated.
			if (mem_bank.find(ind) != mem_bank.end()) {
				res = mem_bank[ind];
			}
			else {
				//Remember calculations
				res = find_permutations(adapters, locked, on_off, ind + 1, mem_bank);
				mem_bank[ind] = res;
			}
		}
		return res;

	}

	tuple<op_value_type, op_value_type> get_adapter_info(istream& file) {
		string line;
		vector<op_value_type> adapters;

		//Add the start charging outlet
		adapters.push_back(0);

		while (getline(file, line)) {
			adapters.push_back(stoll(line));
		}

		sort(adapters.begin(), adapters.end());

		vector<int> locked(adapters.size(), 0);
		locked[0] = 1; 
		locked[locked.size() - 1] = 1;
		map<op_value_type, op_value_type> diff_count;
		for (int i = 0; i < adapters.size() -1; ++i) {
			op_value_type diff = adapters[i + 1] - adapters[i];
			diff_count[diff]++;
			if (diff == 3) {
				locked[i] = 1;
				locked[i+1] = 1;
			}
		}

		op_value_type mul_res_first = (1 + diff_count[3]) * diff_count[1];

		vector<int> on_off(adapters.size(), 1);
		map<int, op_value_type> mem_bank;
		op_value_type count_permutations = find_permutations(adapters, locked, on_off, 0, mem_bank);

		return { mul_res_first, count_permutations };
	}
}
