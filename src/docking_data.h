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

namespace day14 {
	using namespace std;
	using op_value_type = unsigned long long;

	enum DockOperations {
		MASK,
		MEM
	};

	void mask_val_str(string mask, string& val_str) {
		for (int i = 0; i < mask.size(); ++i) {
			if (mask[i] == '1') {
				val_str[i] = '1';
			}
			else if (mask[i] == 'X') {
				val_str[i] = 'X';
			}
		}
	}

	void set_floating_addr_val(string& addr, map<string, op_value_type>& memory_map, int ind, op_value_type val) {
		if (ind >= addr.size()) {
			memory_map[addr] = val;
			return;
		}
		else {
			if (addr[ind] == 'X') {
				addr[ind] = '0';
				set_floating_addr_val(addr, memory_map, ind + 1, val);
				addr[ind] = '1';
				set_floating_addr_val(addr, memory_map, ind + 1, val);
				addr[ind] = 'X';
			}
			else {
				set_floating_addr_val(addr, memory_map, ind + 1, val);
			}
		}
	}

	void string_mask_to_ul(string mask, op_value_type& or_mask, op_value_type& and_mask) {
		or_mask = 0x0;
		and_mask = 0xfffffffff;
		for (int i = mask.size() -1; i >= 0; --i) {
			if (mask[i] == '0') {
				and_mask &= ~(1ULL << (mask.size() - i - 1));
			}
			else if (mask[i] == '1') {
				or_mask |= (1ULL << (mask.size() - i - 1));
			}
		}
	}

	struct Action {
		DockOperations op;
		string addr;
		string val;
	};

	tuple<op_value_type, op_value_type> get_docking_data(istream& file) {
		string line;
		op_value_type or_mask = 0, and_mask = 0xfffffffff;
		vector<Action> actions;
		map<op_value_type, op_value_type> memory_map;
		map<string, op_value_type> memory_map_second;

		while (getline(file, line)) {
			string operation, tmp, val, addr = "";
			DockOperations op;
			op_value_type mem_addr;
			istringstream iss(line);
			iss >> operation >> tmp >> val;
			if (operation[operation.size() - 1] == ']') {
				size_t pos1 = operation.find('[');
				size_t pos2 = operation.find(']');
				addr = operation.substr(pos1 + 1, pos2 - pos1 - 1);
				op = DockOperations::MEM;
			}
			else {
				op = DockOperations::MASK;
			}
			actions.push_back({op, addr, val});
		}

		for (Action action : actions) {
			switch (action.op)
			{
			case DockOperations::MASK:
				string_mask_to_ul(action.val, or_mask, and_mask);
				break;
			case DockOperations::MEM:
				op_value_type tmp_val = stoul(action.val);
				op_value_type addr = stoul(action.addr);
				tmp_val &= and_mask;
				tmp_val |= or_mask;
				memory_map[addr] = tmp_val;
				break;
			}
		}

		op_value_type mem_sum = 0;
		for (auto it : memory_map) {
			mem_sum += it.second;
		}

		string curr_mask;
		for (Action action : actions) {
			switch (action.op)
			{
			case DockOperations::MASK:
				curr_mask = action.val;
				break;
			case DockOperations::MEM:
				string mask_addr = bitset<36>(stoul(action.addr)).to_string();
				mask_val_str(curr_mask, mask_addr);
				set_floating_addr_val(mask_addr, memory_map_second, 0, stoul(action.val));
				break;
			}
		}

		op_value_type mem_sum_second = 0;
		for (auto it : memory_map_second) {
			mem_sum_second += it.second;
		}

		return { mem_sum,mem_sum_second };
	}
}
