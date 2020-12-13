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

namespace day13 {
	using namespace std;
	using op_value_type = long long;

	tuple<op_value_type, op_value_type> get_bus_schedule_info(istream& file) {
		string line, val_str;
		op_value_type port_arrival_time;
		vector<op_value_type> bus_ids;
		vector<op_value_type> time_offset;

		getline(file, line);
		port_arrival_time = stoll(line);
		getline(file, line);
		istringstream iss(line);
		size_t pos;
		op_value_type curr_offset = 0;
		while (getline(iss, val_str, ',')) {
			if (val_str[0] != 'x') {
				bus_ids.push_back(stoll(val_str));
				time_offset.push_back(curr_offset);
			}
			curr_offset++;
		}

		//Find departure after arrival
		vector<op_value_type> departure_after_arrival;
		for (op_value_type id : bus_ids) {
			op_value_type div_res = port_arrival_time / id;
			op_value_type dep_id_time = id * div_res;
			if (dep_id_time < port_arrival_time) {
				dep_id_time += id;
			}
			departure_after_arrival.push_back(dep_id_time);
		}

		op_value_type min_diff = departure_after_arrival[0] - port_arrival_time;
		int closes_bus = 0;
		for (int i = 0; i < departure_after_arrival.size(); ++i) {
			op_value_type diff = departure_after_arrival[i]- port_arrival_time;
			if (diff < min_diff) {
				min_diff = diff;
				closes_bus = i;
			}
		}

		//Bute force solution
		//find first point then step with new length
		int curr_bus_ind = 1;
		op_value_type step_size = bus_ids[0];
		op_value_type curr_time = bus_ids[0];
		op_value_type curr_lcm = 0;

		while (curr_bus_ind < bus_ids.size()) {
			if (((curr_time + time_offset[curr_bus_ind]) % bus_ids[curr_bus_ind]) == 0) {
				step_size = lcm(step_size, bus_ids[curr_bus_ind]);
				curr_bus_ind++;
				if (curr_bus_ind >= bus_ids.size()) {
					continue;
				}
				curr_lcm = lcm(step_size, bus_ids[curr_bus_ind]);
			}
			else {
				curr_time += step_size;
			}
		}

		return { min_diff * bus_ids[closes_bus],curr_time };
	}
}