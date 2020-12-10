#pragma once
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <string>
#include <valarray>

namespace day3 {
	using namespace std;
	using op_value_type = long long;

	bool all_done(vector<valarray<op_value_type>> poses, vector<string> tree_map) {
		for (valarray<op_value_type> pos : poses) {
			if (pos[1] < tree_map.size()) {
				return false;
			}
		}
		return true;
	}

	tuple<op_value_type, op_value_type> get_toboggan_info(istream& file) {
		string line;
		vector<string> tree_map;
		char tree = '#';
		char no_tree = '.';
		vector<valarray<op_value_type>> tbg_trajs = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

		while (getline(file, line)) {
			tree_map.push_back(line);
		}

		vector<valarray<op_value_type>> curr_poses = { { 0,0 }, {0,0}, {0,0}, {0,0}, {0,0} };
		vector<op_value_type> tree_counts = { 0,0,0,0,0 };
		while (!all_done(curr_poses, tree_map)) {
			for (int i = 0; i < curr_poses.size(); ++i) {
				if (curr_poses[i][1] < tree_map.size() &&
					tree_map[curr_poses[i][1]][curr_poses[i][0] % tree_map[0].size()] == tree) {
					tree_counts[i]++;
				}

				curr_poses[i] = curr_poses[i] + tbg_trajs[i];
			}
		}

		op_value_type mult_res = 1;
		for (op_value_type count : tree_counts) {
			mult_res *= count;
		}

		return { tree_counts[1], mult_res };
	}

}