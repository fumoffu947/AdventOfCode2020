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

namespace day19 {
	using namespace std;
	using op_value_type = int;

	string create_complete_rules_regex(string rule_name, op_value_type rule_num, map<string, vector<vector<string>>>& rule_links,
		map<op_value_type, string>& complete_rules) {
		if (complete_rules.find(rule_num) != complete_rules.end()) {
			return complete_rules[rule_num];
		}

		vector<string> all_rules;
		for (vector<string> part_rule : rule_links[rule_name]) {
			string curr_rules;
			for (string link : part_rule) {
				if (isdigit(link[0])) {
					curr_rules += create_complete_rules_regex(link, stoi(link), rule_links, complete_rules);
				}
				else {
					curr_rules += link;
				}
			}
			all_rules.push_back(curr_rules);
		}

		if (all_rules.size() == 1) {
			complete_rules[rule_num] = all_rules[0];
			return all_rules[0];
		}
		else {
			string tmp = "";
			for (string part : all_rules) {
				if (tmp.size() == 0) {
					tmp = "(" + part;
				}
				else {
					tmp += "|" + part;
				}
			}
			tmp += ")";
			complete_rules[rule_num] = tmp;
			return tmp;
		}
	}

	string create_complete_rules_regex_loop(string rule_name, op_value_type rule_num, map<string, vector<vector<string>>>& rule_links,
		map<op_value_type, string>& complete_rules) {
		if (complete_rules.find(rule_num) != complete_rules.end()) {
			return complete_rules[rule_num];
		}

		vector<string> all_rules_prefix;
		bool recursive = false;
		for (vector<string> part_rule : rule_links[rule_name]) {
			string curr_rules;
			bool added_after_rec = false;
			for (string link : part_rule) {
				if (link.compare(rule_name) == 0) {
					curr_rules += ")+(";
					recursive = true;
					added_after_rec = false;
				}
				else if (isdigit(link[0])) {
					if (recursive) {
						added_after_rec = true;
					}
					curr_rules += create_complete_rules_regex_loop(link, stoi(link), rule_links, complete_rules);
				}
				else {
					if (recursive) {
						added_after_rec = true;
					}
					curr_rules += link;
				}
			}
			if (added_after_rec) {
				//To handle last bit after recursive stuff
				curr_rules += ")+(";
			}
			if (recursive) {
				curr_rules = "(" + curr_rules.substr(0, curr_rules.size() - 1);
			}
			all_rules_prefix.push_back(curr_rules);
		}

		if (all_rules_prefix.size() == 1) {
			complete_rules[rule_num] = all_rules_prefix[0];
			return all_rules_prefix[0];
		}
		else {
			string tmp = "";
			for (string part : all_rules_prefix) {
				if (tmp.size() == 0) {
					tmp = "(" + part;
				}
				else {
					tmp += "|" + part;
				}
			}
			tmp += ")";
			complete_rules[rule_num] = tmp;
			return tmp;
		}
	}

	tuple<op_value_type, op_value_type> get_message_info(istream& file) {
		string line;
		map<string, vector<vector<string>>> rule_links;
		map<op_value_type, set<string>> complete_rules, complete_rules_second;
		map<op_value_type, string> complete_rules_regx, complete_rules_second_regx;
		vector<string> messages;

		int read_mode = 0;
		while (getline(file, line)) {
			if (line.size() == 0) {
				read_mode++;
			}
			else if (read_mode == 0) {
				istringstream iss(line);
				string tmp;
				iss >> tmp;
				string rule_name = tmp.substr(0, tmp.size()-1);
				vector<string> curr_rules_links;
				while (iss >> tmp) {
					if (tmp[0] == '"') {
						curr_rules_links.push_back(tmp.substr(1, tmp.size() - 2));
					}
					else if (tmp[0] == '|') {
						rule_links[rule_name].push_back(curr_rules_links);
						curr_rules_links.clear();
					}
					else {
						curr_rules_links.push_back(tmp);
					}
				}
				if (curr_rules_links.size() > 0) {
					rule_links[rule_name].push_back(curr_rules_links);
				}

			}
			else if (read_mode == 1) {
				messages.push_back(line);
			}
		}

		//First task regex, check for messages that match rule 0
		for (auto it : rule_links) {
			op_value_type rule_num = stoi(it.first);
			string complete_rule = create_complete_rules_regex(it.first, rule_num, rule_links, complete_rules_regx);
			if (complete_rules_regx.find(rule_num) != complete_rules_regx.end()) {
				complete_rules_regx[rule_num] = complete_rule;
			}
		}

		string zero_rule = complete_rules_regx[0];
		op_value_type match_rules_count = 0;
		regex regex_zero{ zero_rule };

		for (string msg : messages) {
			if (regex_match(msg, regex_zero)) {
				match_rules_count++;
			}
		}

		//Second regex
		rule_links["8"] = { {"42"},{"42","8"} };
		rule_links["11"] = { {"42", "31"},{"42","11", "31"} };
		for (auto it : rule_links) {
			op_value_type rule_num = stoi(it.first);
			string complete_rule = create_complete_rules_regex_loop(it.first, rule_num, rule_links, complete_rules_second_regx);
			if (complete_rules_second_regx.find(rule_num) != complete_rules_second_regx.end()) {
				complete_rules_second_regx[rule_num] = complete_rule;
			}
		}

		string zero_rule_second = complete_rules_second_regx[0];
		string regex_str_42 = complete_rules_second_regx[42];
		string regex_str_31 = complete_rules_second_regx[31];
		string regex_str_8 = complete_rules_second_regx[8];
		op_value_type match_rules_count_second = 0;
		regex regex_zero_second{ zero_rule_second };
		regex regex_42{ regex_str_42 };
		regex regex_31{ regex_str_31 };
		regex regex_8{ regex_str_8 };

		for (string msg : messages) {
			if (regex_match(msg, regex_zero_second)) {
				smatch matches_8;
				regex_search(msg, matches_8, regex_8);

				//Filter out the first part that might contain matches....
				string msg_substr = msg.substr(matches_8.length(0));
				std::ptrdiff_t const rule_42_match_count(std::distance(
					std::sregex_iterator(msg_substr.begin(), msg_substr.end(), regex_42),
					std::sregex_iterator()));

				std::ptrdiff_t const rule_31_match_count(std::distance(
					std::sregex_iterator(msg_substr.begin(), msg_substr.end(), regex_31),
					std::sregex_iterator()));

				if (rule_42_match_count == rule_31_match_count) {
					match_rules_count_second++;
				}
			}
		}
		return { match_rules_count, match_rules_count_second };
	}
}