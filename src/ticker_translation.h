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

namespace day16 {
	using namespace std;
	using op_value_type = long long;

	class FieldRule {
	public:
		FieldRule(string name, vector<tuple<op_value_type, op_value_type>> rules) : name{ name }, rules{ rules } {}

		bool valid(op_value_type val) {
			bool valid = false;
			for (tuple<op_value_type, op_value_type> range : rules) {
				if (val >= get<0>(range) && val <= get<1>(range)) {
					valid = true;
					break;
				}
			}
			return valid;
		}

		string name;
		vector<tuple<op_value_type, op_value_type>> rules;
	};

	tuple<op_value_type, op_value_type> get_ticket_info(istream& file) {
		string line;

		vector<FieldRule> rules;
		vector<op_value_type> my_ticket;
		vector<vector<op_value_type>> nerby_tickets;
		vector<vector<op_value_type>> ok_tickets;

		int parser = 0;
		while (getline(file, line)) {
			if (line.size() == 0) {
				parser++;
			}
			else if (parser == 0) {
				string part, name;
				vector<tuple<op_value_type, op_value_type>> curr_rules;
				size_t pos = line.find(':');
				name = line.substr(0, pos);
				istringstream iss(line.substr(pos+1));

				while (iss >> part) {
					if (isdigit(part[0])) {
						op_value_type low, high;
						size_t split = part.find('-');
						low = stoi(part.substr(0, split));
						high = stoi(part.substr(split+1));
						curr_rules.push_back({ low, high });
					}
				}
				rules.push_back({ name, curr_rules });
			}
			else if (parser == 1) {
				if (isdigit(line[0])) {
					string part;
					istringstream iss(line);
					vector<op_value_type> ticket;
					while (getline(iss, part, ',')) {
						my_ticket.push_back(stoi(part));
					}
				}

			}
			else if (parser == 2) {
				if (isdigit(line[0])) {
					string part;
					istringstream iss(line);
					vector<op_value_type> ticket;
					while (getline(iss, part, ',')) {
						ticket.push_back(stoi(part));
					}
					nerby_tickets.push_back(ticket);
				}
			}
		}

		op_value_type non_valid_sum = 0;
		for (vector<op_value_type> ticket : nerby_tickets) {
			bool valid_ticket = true;
			for (op_value_type val : ticket) {
				bool any_valid = false;
				for (FieldRule fr : rules) {
					if (fr.valid(val)) {
						any_valid = true;
					}
					else {
					}
				}
				if (!any_valid) {
					non_valid_sum += val;
					valid_ticket = false;
				}
			}
			if (valid_ticket) {
				ok_tickets.push_back(ticket);
			}
		}

		vector<vector<int>> fields_valid_poses(nerby_tickets[0].size(), vector<int>(rules.size(), 0));
		for (vector<op_value_type> ticket : ok_tickets) {
			for (int i = 0; i < ticket.size(); ++i) {
				for (int j = 0; j < rules.size(); ++j) {
					if (rules[j].valid(ticket[i])) {
						fields_valid_poses[i][j]++;
					}
				}
			}
		}

		for (int i = 0; i < fields_valid_poses.size(); ++i) {
			for (int j = 0; j < fields_valid_poses[i].size(); ++j) {
				if (fields_valid_poses[i][j] == ok_tickets.size()) {
					fields_valid_poses[i][j] = 1;
				}
				else {
					fields_valid_poses[i][j] = 0;
				}
			}
		}

		//Selct fields
		int selected_fields = 0;
		vector<int> rules_field_ind(rules.size(), 0);
		while (selected_fields < fields_valid_poses.size()) {
			int lonly_row = -1;
			int lonly_col = -1;
			int val_count = 0;
			for (int i = 0; i < fields_valid_poses.size(); ++i) {
				val_count = 0;
				for (int j = 0; j < fields_valid_poses[i].size(); ++j) {
					if (fields_valid_poses[i][j] == 1) {
						val_count++;
						lonly_row = i;
						lonly_col = j;
					}
				}
				if (val_count == 1) {
					break;
				}
			}

			if (val_count == 1) {
				rules_field_ind[lonly_col] = lonly_row;
				selected_fields++;
				for (int i = 0; i < fields_valid_poses.size(); ++i) {
					fields_valid_poses[i][lonly_col] = 0;
				}
			}
		}

		op_value_type mul_res = 1;
		for (int i = 0; i < rules_field_ind.size(); ++i) {
			if (rules[i].name.rfind("departure", 0) == 0) {
				mul_res *= my_ticket[rules_field_ind[i]];
			}
		}

		return { non_valid_sum, mul_res };
	}
}