#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <set>
#include <string>
#include <valarray>
#include <regex>

namespace day6 {
	using namespace std;
	using op_value_type = int;

	tuple<op_value_type, op_value_type> get_declaration_form_answers(istream& file) {
		string line;
		vector<vector<string>> groups_answers;

		vector<string> curr_group;
		while (getline(file, line)) {
			if (line.size() == 0) {
				groups_answers.push_back(curr_group);
				curr_group.clear();
			}
			else {
				curr_group.push_back(line);
			}
		}
		//Add last group!!
		groups_answers.push_back(curr_group);
		curr_group.clear();

		vector<set<char>> groups_set_answers;
		vector<set<char>> groups_intersect_answers;
		for (vector<string> group_answers : groups_answers) {
			set<char> curr_set;
			set<char> prev_set_res;
			bool first = true;
			for (string person_answers : group_answers) {
				set<char> person_set;
				for (char question_yes : person_answers) {
					curr_set.insert(question_yes);
					person_set.insert(question_yes);
				}
				if (first) {
					first = false;
					prev_set_res = person_set;
				}
				else {
					set<char> res;
					set_intersection(person_set.begin(), person_set.end(),
						prev_set_res.begin(), prev_set_res.end(),
						inserter(res, res.begin()));
					prev_set_res = res;

				}
			}
			groups_set_answers.push_back(curr_set);
			groups_intersect_answers.push_back(prev_set_res);
		}


		//Count the number of unique questions the groups answers yes to
		int groups_yes_set_sum = 0;
		for (set<char> answer_set : groups_set_answers) {
			groups_yes_set_sum += answer_set.size();
		}

		//Count the number of common answers in each group.
		int groups_yes_intersection_sum = 0;
		for (set<char> answer_set : groups_intersect_answers) {
			groups_yes_intersection_sum += answer_set.size();
		}

		return { groups_yes_set_sum, groups_yes_intersection_sum };
	}
}
