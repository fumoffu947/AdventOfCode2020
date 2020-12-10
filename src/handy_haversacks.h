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

namespace day7 {
	using namespace std;
	using op_value_type = int;

	struct BagSubRule {
		int count;
		string colour;
	};

	bool find_type(string start_name, map<string, vector<BagSubRule>> rules, string &target_colour) {

		for (BagSubRule brule : rules[start_name]) {
			if (brule.colour.compare(target_colour) == 0) {
				return true;
			}
			if (find_type(brule.colour, rules, target_colour)) {
				return true;
			}
		}
		return false;
	}

	void find_bottom_colours(string start_name, set<string> &top_colours, map<string, vector<string>> &rev_rules, set<string>& bottom_rules) {
		if (top_colours.find(start_name) != top_colours.end()) {
			bottom_rules.insert(start_name);
		}
		for (string colour : rev_rules[start_name]) {
			find_bottom_colours(colour, top_colours, rev_rules, bottom_rules);
		}
	}

	int count_sub_bags(string bag_name, map<string, vector<BagSubRule>>& rules) {
		int count = 0;
		for (BagSubRule brule : rules[bag_name]) {
			count += brule.count;
			count += brule.count * count_sub_bags(brule.colour, rules);
		}
		return count;
	}

	tuple<op_value_type, op_value_type> get_bag_info(istream& file) {
		string line;
		map<string, vector<BagSubRule>> rules;
		map<string, vector<string>> rev_rules;
		set<string> top_colours;
		string target_bag = "shiny gold";

		while (getline(file, line)) {
			vector<BagSubRule> curr_rules;
			istringstream iss(line);
			string colour;
			bool name_part_done = false;
			string tmp = "";
			//Find name
			while (!name_part_done) {
				string part;
				iss >> part;
				if (part.rfind("bags") != string::npos) {
					iss >> part;
					name_part_done = true;
					colour = tmp;
					tmp = "";
				}
				else {
					if (tmp.size() == 0) {
						tmp = part;
					}
					else {
						tmp += " " + part;
					}
				}
			}
			top_colours.insert(colour);
			//Find sub bags
			bool sub_bags_done = false;
			while (!sub_bags_done) {
				string part, tmp_sub_name = "", curr_colour;
				bool sub_bag_name_done = false;
				iss >> part;
				if (part.compare("no") == 0) {
					sub_bags_done = true;
					continue;
				}
				int count = stoi(part);
				while (!sub_bag_name_done) {
					iss >> part;
					if (part.rfind("bag") != string::npos) {
						sub_bag_name_done = true;
						curr_colour = tmp_sub_name;
					}
					else {
						if (tmp_sub_name.size() == 0) {
							tmp_sub_name = part;
						}
						else {
							tmp_sub_name += " " + part;
						}
					}
				}
				rev_rules[curr_colour].push_back(colour);
				curr_rules.push_back({ count, curr_colour });
				if (part[part.size() - 1] == '.') {
					sub_bags_done = true;
				}
			}
			rules[colour] = curr_rules;
		}

		op_value_type target_bag_count = 0;
		set<string> top_colours_link;
		find_bottom_colours(target_bag, top_colours, rev_rules, top_colours_link);
		top_colours_link.erase(target_bag);
		target_bag_count = top_colours_link.size();

		//count the number of bags for shiny gold
		op_value_type shiny_bag_contain_count = count_sub_bags(target_bag, rules);

		return { target_bag_count,shiny_bag_contain_count };
	}
}
