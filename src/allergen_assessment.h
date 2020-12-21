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

namespace day21 {
	using namespace std;
	using op_value_type = int;
	using c_type = set<string>;

	class FoodInfo {
	public:
		FoodInfo(c_type ingredients, c_type allergens) : ingredients{ ingredients }, allergens{ allergens } {}

		c_type ingredients;
		c_type allergens;
	};

	tuple<op_value_type, string> get_ingredient_info(istream& file) {
		string line;
		vector<FoodInfo> all_foods;

		while (getline(file, line)) {
			istringstream iss(line);
			int mode = 0;
			c_type ingreedients;
			c_type allergens;
			string ingred;
			while (iss >> ingred) {
				if (ingred[0] == '(') {
					mode++;
				}
				else if (mode == 0) {
					ingreedients.insert(ingred);
				}
				else {
					allergens.insert(ingred.substr(0, ingred.size() - 1));
				}
			}
			all_foods.push_back({ ingreedients, allergens });
		}

		//Reduce the number of matches
		map<string, c_type> allergenses;
		for (int i = 0; i < all_foods.size(); ++i) {
			for (string allergens : all_foods[i].allergens) {
				c_type tmp_c;
				if (allergenses.find(allergens) != allergenses.end()) {
					c_type prev_c = allergenses[allergens];
					c_type curr_c = all_foods[i].ingredients;
					set_intersection(prev_c.begin(), prev_c.end(), curr_c.begin(), curr_c.end(), inserter(tmp_c, tmp_c.begin()));
				}
				else {
					tmp_c = all_foods[i].ingredients;
				}
				allergenses[allergens] = tmp_c;
			}
		}

		//lock matches
		c_type locked;
		while (locked.size() != allergenses.size()) {
			for (auto it : allergenses) {
				if (allergenses[it.first].size() > 1) {
					c_type tmp_c;
					set_difference(allergenses[it.first].begin(), allergenses[it.first].end(), locked.begin(), locked.end(), inserter(tmp_c, tmp_c.begin()));
					allergenses[it.first] = tmp_c;
				}
				if (allergenses[it.first].size() == 1) {
					for (string val : it.second) {
						locked.insert(val);
					}
				}
			}
		}

		string sorted_allergens_ingredient_names = "";
		for (auto it : allergenses) {
			for (string val : it.second) {
				sorted_allergens_ingredient_names += val + ",";
			}
		}
		//Remove last character
		sorted_allergens_ingredient_names = sorted_allergens_ingredient_names.substr(0, sorted_allergens_ingredient_names.size() - 1);

		int non_allergens_apperance_count = 0;
		for (FoodInfo fi : all_foods) {
			for (string val : fi.ingredients) {
				if (locked.find(val) == locked.end()) {
					non_allergens_apperance_count++;
				}
			}
		}

		return { non_allergens_apperance_count,sorted_allergens_ingredient_names };
	}
}