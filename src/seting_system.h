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

namespace day11 {
	using namespace std;
	using op_value_type = int;
	using w_type = vector<string>;
	using w_ptr = shared_ptr<w_type>;

	int count_neighbours(w_ptr world, int row, int col, char neighbour_val) {
		int count = 0;
		for (int y = row - 1; y < row + 2; ++y) {
			for (int x = col - 1; x < col + 2; ++x) {
				if (y == row && x == col) {
					continue;
				}
				if (x >= 0 && y >= 0 &&
					y < world->size() && x < (*world)[y].size()) {
					//cout << "char att pos is " << x << ":" << y << " val " << (*world)[y][x] << " compare val is " << neighbour_val << endl;
					if ((*world)[y][x] == neighbour_val) {
						//cout << "adding 1 " << endl;
						count++;
					}
				}
			}
		}
		return count;
	}

	int count_neighbours_advanced(w_ptr world, int row, int col, char neighbour_val, char none) {
		valarray<valarray<int>> dirs = { {0,1}, {1,1}, {1,0}, {1,-1},{0,-1},{-1,-1}, {-1,0}, {-1, 1} };
		int count = 0;
		for (valarray<int> dir : dirs) {
			valarray<int> curr_pos = { row,col };
			curr_pos += dir;
			bool found = false, out_of_bound = false;
			while (!found && !out_of_bound) {
				if (curr_pos[0] < 0 ||
					curr_pos[1] < 0 ||
					curr_pos[0] >= world->size() ||
					curr_pos[1] >= (*world)[0].size()) {
					out_of_bound = true;
				}
				else if ((*world)[curr_pos[0]][curr_pos[1]] != none) {
					found = true;
				}
				else {
					curr_pos += dir;
				}
			}

			if (found && (*world)[curr_pos[0]][curr_pos[1]] == neighbour_val) {
				count++;
			}
		}
		return count;
	}

	int step_world(w_ptr src_world, w_ptr dest_world, char empty, char filled) {
		int change_count = 0;
		for (int y = 0; y < src_world->size(); ++y) {
			for (int x = 0; x < (*src_world)[y].size(); ++x) {
				char res = (*src_world)[y][x];
				int neighbour_count = count_neighbours(src_world, y, x, filled);
				if ((*src_world)[y][x] == empty) {
					if (neighbour_count == 0) {
						res = filled;
						change_count++;
					}
				}
				else if ((*src_world)[y][x] == filled) {
					if (neighbour_count > 3) {
						res = empty;
						change_count++;
					}
				}
				(*dest_world)[y][x] = res;
			}
		}
		return change_count;
	}

	int step_world_advanced(w_ptr src_world, w_ptr dest_world, char empty, char filled, char none, int to_empty_count, bool advanced) {
		int change_count = 0;
		for (int y = 0; y < src_world->size(); ++y) {
			for (int x = 0; x < (*src_world)[y].size(); ++x) {
				char res = (*src_world)[y][x];
				int neighbour_count;
				if (advanced) {
					neighbour_count = count_neighbours_advanced(src_world, y, x, filled, none);

				}
				else {
					neighbour_count = count_neighbours(src_world, y, x, filled);

				}
				if ((*src_world)[y][x] == empty) {
					if (neighbour_count == 0) {
						res = filled;
						change_count++;
					}
				}
				else if ((*src_world)[y][x] == filled) {
					if (neighbour_count >= to_empty_count) {
						res = empty;
						change_count++;
					}
				}
				(*dest_world)[y][x] = res;
			}
		}
		return change_count;
	}

	tuple<op_value_type, op_value_type> get_seat_info(istream& file) {
		string line;
		char empty = 'L', filled = '#', floor = '.';
		w_type seat_world1, seat_world2;
		
		while (getline(file, line)) {
			seat_world1.push_back(line);
			seat_world2.push_back(line);
		}

		w_ptr src_world = make_shared<w_type>(seat_world1), dst_world = make_shared<w_type>(seat_world2);

		bool world_changed = true;
		while (world_changed) {

			int change_count = step_world_advanced(src_world, dst_world, empty, filled, floor, 4, false);
			w_ptr tmp = dst_world;
			dst_world = src_world;
			src_world = tmp;

			world_changed = change_count != 0;
		}


		op_value_type filled_count_first = 0;
		for (string row : *src_world) {
			for (char seat : row) {
				if (seat == filled) {
					filled_count_first++;
				}
			}
		}


		//Second part
		src_world = make_shared<w_type>(seat_world1);
		dst_world = make_shared<w_type>(seat_world2);

		world_changed = true;
		while (world_changed) {

			int change_count = step_world_advanced(src_world, dst_world, empty, filled, floor, 5, true);
			w_ptr tmp = dst_world;
			dst_world = src_world;
			src_world = tmp;

			world_changed = change_count != 0;
		}

		op_value_type filled_count_second = 0;
		for (string row : *src_world) {
			for (char seat : row) {
				if (seat == filled) {
					filled_count_second++;
				}
			}
		}

		return { filled_count_first, filled_count_second };
	}
}