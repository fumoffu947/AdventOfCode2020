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

namespace day23 {
	using namespace std;
	using op_value_type = long long;

	template<typename T>
	class CupLink {
	public :
		CupLink(T val) : val{ val } {}
		T val;
		shared_ptr<CupLink> right;
	};

	template<typename T>
	class CupGame {
	public:
		CupGame(vector<T> labels) {
			cups = vector<shared_ptr<CupLink<T>>>(labels.size()+1, nullptr);
			shared_ptr<CupLink<T>> prev_cup =  nullptr, start_cup;
			for (int i = 0; i < labels.size(); ++i) {
				shared_ptr<CupLink<T>> curr_cup = make_shared<CupLink<T>>(labels[i]);
				if (prev_cup == nullptr) {
					start_cup = curr_cup;
				}
				if (prev_cup != nullptr) {
					prev_cup->right = curr_cup;
				}
				prev_cup = curr_cup;
				cups[labels[i]] = curr_cup;

				if (i == (labels.size() - 1)) {
					curr_cup->right = start_cup;
				}
			}
			current_cup = start_cup;
		}

		T get_values_from(T val, int count) {
			taken_vals.clear();
			shared_ptr<CupLink<T>> start_link = cups[val], curr_cup, ret_cup, tmp;
			curr_cup = start_link;
			ret_cup = start_link->right;
			//get the one after
			for (int i = 0; i < count+1; ++i) {
				tmp = curr_cup->right;
				if (i == count) {
					curr_cup->right = nullptr;
				}
				if (i < count) {
					taken_vals.insert(tmp->val);
				}
				curr_cup = tmp;
			}
			start_link->right = curr_cup;
			return ret_cup->val;
		}

		void step_next() {
			current_cup = current_cup->right;
		}

		void insert(T start_val, T values_first) {
			shared_ptr<CupLink<T>> start_link = cups[start_val], next_cup, last_vals_cup;
			next_cup = start_link->right;
			start_link->right = cups[values_first];
			last_vals_cup = cups[values_first];
			
			while (last_vals_cup->right != nullptr) {
				last_vals_cup = last_vals_cup->right;
			}
			last_vals_cup->right = next_cup;
		}

		bool is_val_taken(T val) {
			if (cups[val] == nullptr) {
				return true;
			}
			return taken_vals.find(val) != taken_vals.end();
		}

		T get_current_val() {
			return current_cup->val;
		}

		string get_loop_string_from(T val) {
			shared_ptr<CupLink<T>> start_cup = cups[val], curr_cup;
			curr_cup = start_cup->right;
			ostringstream oss;
			while (curr_cup != start_cup) {
				oss << curr_cup->val;
				curr_cup = curr_cup->right;
			}
			return oss.str();
		}

		T get_val_after(T val) {
			return cups[val]->right->val;
		}

		shared_ptr<CupLink<T>> current_cup;
		set<T> taken_vals;
		vector<shared_ptr<CupLink<T>>> cups;
	};

	tuple<op_value_type, op_value_type> get_cup_info(istream& file) {
		string line;
		vector<op_value_type> values;
		op_value_type max_cup_val = 0;

		while (getline(file, line)) {
			for (char c : line) {
				op_value_type val = c - '0';
				if (val > max_cup_val) {
					max_cup_val = val;
				}
				values.push_back(val);
			}
		}

		CupGame<op_value_type> game(values);

		int turn = 0;
		while (turn < 100) {
			op_value_type curr_label = game.get_current_val();
			op_value_type curr_section = game.get_values_from(curr_label, 3);

			op_value_type insert_val = curr_label - 1;
			while (game.is_val_taken(insert_val)) {
				insert_val--;
				if (insert_val < 1) {
					insert_val = max_cup_val;
				}
			}

			game.insert(insert_val, curr_section);
			game.step_next();
			turn++;
		}

		string val = game.get_loop_string_from(1);


		//game 2
		for (op_value_type i = max_cup_val+1; i < 1000001; ++i) {
			values.push_back(i);
		}
		max_cup_val = 1000000;
		CupGame<op_value_type> large_game(values);

		turn = 0;
		//set<string> states;
		while (turn < 10000000) {
			op_value_type curr_label = large_game.get_current_val();
			op_value_type curr_section = large_game.get_values_from(curr_label, 3);

			op_value_type insert_val = curr_label - 1;
			while (large_game.is_val_taken(insert_val)) {
				insert_val--;
				if (insert_val < 1) {
					insert_val = max_cup_val;
				}
			}

			large_game.insert(insert_val, curr_section);
			large_game.step_next();
			turn++;
		}

		op_value_type first_after_1 = large_game.get_val_after(1);
		op_value_type second_after_1 = large_game.get_val_after(first_after_1);

		return { stoi(val), first_after_1 * second_after_1 };
	}
}