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

namespace day17 {
	using namespace std;
	using op_value_type = int;

	class PocketDim3D {
	public:
		PocketDim3D(int x, int y, int z, char unactive) : size_x{ x }, size_y{ y }, size_z{ z },
			middle_x{ x / 2 }, middle_y{ y / 2 }, middle_z{ z / 2 }, unactive{ unactive } {
			world = vector<vector<string>>(x, vector<string>(y, string(z, unactive)));
			lowest_x = -middle_x;
			highest_x = x + lowest_x;
			lowest_y = -middle_y;
			highest_y = y + lowest_y;
			lowest_z = -middle_z;
			highest_z = z + lowest_z;
			max_x = lowest_x;
			min_x = highest_x;
			max_y = lowest_y;
			min_y = highest_y;
			max_z = lowest_z;
			min_z = highest_z;
		}

		char get_char_at(int x, int y, int z) {
			return world[x + middle_x][y + middle_y][z + middle_z];
		}

		void set_char_at(int x, int y, int z, char val) {
			world[x + middle_x][y + middle_y][z + middle_z] = val;
			if (val != unactive) {
				counter++;
				if (x < min_x) {
					min_x = x;
				}
				if (x > max_x) {
					max_x = x;
				}
				if (y < min_y) {
					min_y = y;
				}
				if (y > max_y) {
					max_y = y;
				}
				if (z < min_z) {
					min_z = z;
				}
				if (z > max_z) {
					max_z = z;
				}
			}
		}

		int count_not_val(int x, int y, int z, char val) {
			int count = 0;
			x += middle_x;
			y += middle_y;
			z += middle_z;
			for (int i = x - 1; i < x + 2; ++i) {
				for (int j = y - 1; j < y + 2; ++j) {
					for (int k = z - 1; k < z + 2; ++k) {
						if (i >= 0 && i < world.size() &&
							j >= 0 && j < world[i].size() &&
							k >= 0 && k < world[i][j].size() &&
							(i != x || j != y || k != z) &&
							world[i][j][k] != val) {
							count++;
						}
					}
				}
			}
			return count;
		}

		void reset_counter() {
			counter = 0;
		}

		vector<vector<string>> world;
		int counter = 0;
		int size_x, size_y, size_z;
		int middle_x, middle_y, middle_z;
		int lowest_x, highest_x;
		int lowest_y, highest_y;
		int lowest_z, highest_z;
		int max_x, min_x;
		int max_y, min_y;
		int max_z, min_z;
		char unactive;
	};

	class PocketDim4D {
	public:
		PocketDim4D(int x, int y, int z, int  v, char unactive) : size_x{ x }, size_y{ y }, size_z{ z }, size_v{ v },
			middle_x{ x / 2 }, middle_y{ y / 2 }, middle_z{ z / 2 }, middle_v{ v / 2 },
			unactive{ unactive } {
			world = vector<vector<vector<string>>>(x, vector<vector<string>>(y, vector<string>(z, string(v, unactive))));
			lowest_x = -middle_x;
			highest_x = x + lowest_x;
			lowest_y = -middle_y;
			highest_y = y + lowest_y;
			lowest_z = -middle_z;
			highest_z = z + lowest_z;
			lowest_v = -middle_v;
			highest_v = v + lowest_v;
			max_x = lowest_x;
			min_x = highest_x;
			max_y = lowest_y;
			min_y = highest_y;
			max_z = lowest_z;
			min_z = highest_z;
			max_v = lowest_v;
			min_v = highest_v;
		}

		char get_char_at(int x, int y, int z, int v) {
			return world[x + middle_x][y + middle_y][z + middle_z][v + middle_v];
		}

		void set_char_at(int x, int y, int z, int v, char val) {
			world[x + middle_x][y + middle_y][z + middle_z][v + middle_v] = val;
			if (val != unactive) {
				counter++;
				if (x < min_x) {
					min_x = x;
				}
				if (x > max_x) {
					max_x = x;
				}
				if (y < min_y) {
					min_y = y;
				}
				if (y > max_y) {
					max_y = y;
				}
				if (z < min_z) {
					min_z = z;
				}
				if (z > max_z) {
					max_z = z;
				}
				if (v < min_v) {
					min_v = v;
				}
				if (v > max_v) {
					max_v = v;
				}
			}
		}

		int count_not_val(int x, int y, int z, int v, char val) {
			int count = 0;
			x += middle_x;
			y += middle_y;
			z += middle_z;
			v += middle_v;
			for (int i = x - 1; i < x + 2; ++i) {
				for (int j = y - 1; j < y + 2; ++j) {
					for (int k = z - 1; k < z + 2; ++k) {
						for (int l = v - 1; l < v + 2; ++l) {
							if (i >= 0 && i < world.size() &&
								j >= 0 && j < world[i].size() &&
								k >= 0 && k < world[i][j].size() &&
								l >= 0 && l < world[i][j][k].size() &&
								(i != x || j != y || k != z || l != v) &&
								world[i][j][k][l] != val) {
								count++;
							}
						}
					}
				}
			}
			return count;
		}

		void reset_counter() {
			counter = 0;
		}

		vector<vector<vector<string>>> world;
		int counter = 0;
		int size_x, size_y, size_z, size_v;
		int middle_x, middle_y, middle_z, middle_v;
		int lowest_x, highest_x;
		int lowest_y, highest_y;
		int lowest_z, highest_z;
		int lowest_v, highest_v;
		int max_x, min_x;
		int max_y, min_y;
		int max_z, min_z;
		int max_v, min_v;
		char unactive;
	};

	tuple<op_value_type, op_value_type> get_energy_info(istream& file) {
		string line;
		vector<string> center_patch;
		char active = '#', unactive = '.';
		int x_size = 20, y_size = 20, z_size = 20, v_size = 20;
		int max_iter = 6;

		while (getline(file, line)) {
			center_patch.push_back(line);
		}

		shared_ptr<PocketDim3D> src_ptr = make_shared<PocketDim3D>(x_size, y_size, z_size, unactive), dst_ptr = make_shared<PocketDim3D>(x_size, y_size, z_size, unactive);
		shared_ptr<PocketDim3D> tmp_ptr;

		int i_size = center_patch.size(), j_size = center_patch[0].size();
		for (int i = 0; i < center_patch.size(); ++i) {
			for (int j = 0; j < center_patch[i].size(); ++j) {
				src_ptr->set_char_at(0, i - i_size / 2, j - j_size / 2, center_patch[i][j]);
			}
		}

		int iter = 0;
		int search_offset = 1;
		int first_count = 0;
		while (iter < max_iter) {
			for (int i = src_ptr->min_x - search_offset; i < src_ptr->max_x + search_offset + 1; ++i) {
				for (int j = src_ptr->min_y - search_offset; j < src_ptr->max_y + search_offset + 1; ++j) {
					for (int k = src_ptr->min_z - search_offset; k < src_ptr->max_z + search_offset + 1; ++k) {
						int neighour_count = src_ptr->count_not_val(i, j, k, unactive);
						char res = unactive;
						if (src_ptr->get_char_at(i, j, k) == active) {
							if (neighour_count == 2 || neighour_count == 3) {
								res = active;
							}
							else {
								res = unactive;
							}
						}
						else if (src_ptr->get_char_at(i, j, k) == unactive) {
							if (neighour_count == 3) {
								res = active;
							}
							else {
								res = unactive;
							}
						}
						dst_ptr->set_char_at(i, j, k, res);
					}
				}
			}

			if (iter == 5) {
				first_count = dst_ptr->counter;
			}

			tmp_ptr = dst_ptr;
			dst_ptr = src_ptr;
			src_ptr = tmp_ptr;
			dst_ptr->reset_counter();
			iter++;
		}

		//Second
		shared_ptr<PocketDim4D> tmp4d_ptr;
		shared_ptr<PocketDim4D> src4d_ptr = make_shared<PocketDim4D>(x_size, y_size, z_size, v_size, unactive),
			dst4d_ptr = make_shared<PocketDim4D>(x_size, y_size, z_size, v_size, unactive);

		for (int i = 0; i < center_patch.size(); ++i) {
			for (int j = 0; j < center_patch[i].size(); ++j) {
				src4d_ptr->set_char_at(0, 0, i - i_size / 2, j - j_size / 2, center_patch[i][j]);
			}
		}

		iter = 0;
		search_offset = 1;
		int second_count = 0;
		while (iter < max_iter) {
			for (int i = src4d_ptr->min_x - search_offset; i < src4d_ptr->max_x + search_offset + 1; ++i) {
				for (int j = src4d_ptr->min_y - search_offset; j < src4d_ptr->max_y + search_offset + 1; ++j) {
					for (int k = src4d_ptr->min_z - search_offset; k < src4d_ptr->max_z + search_offset + 1; ++k) {
						for (int l = src4d_ptr->min_v - search_offset; l < src4d_ptr->max_v + search_offset + 1; ++l) {
							int neighour_count = src4d_ptr->count_not_val(i, j, k, l, unactive);
							char res = unactive;
							if (src4d_ptr->get_char_at(i, j, k, l) == active) {
								if (neighour_count == 2 || neighour_count == 3) {
									res = active;
								}
								else {
									res = unactive;
								}
							}
							else if (src4d_ptr->get_char_at(i, j, k, l) == unactive) {
								if (neighour_count == 3) {
									res = active;
								}
								else {
									res = unactive;
								}
							}
							dst4d_ptr->set_char_at(i, j, k, l, res);
						}
					}
				}
			}

			if (iter == 5) {
				second_count = dst4d_ptr->counter;
			}

			tmp4d_ptr = dst4d_ptr;
			dst4d_ptr = src4d_ptr;
			src4d_ptr = tmp4d_ptr;
			dst4d_ptr->reset_counter();
			iter++;
		}

		return { first_count,second_count };
	}
}