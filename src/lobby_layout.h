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

namespace day24 {
	using namespace std;
	using op_value_type = int;

	enum class TileTypes {
		WHITE,
		BLACK
	};

	enum class HexDir {
		EAST,
		SOUTH_EAST,
		SOUTH_WEST,
		WEST,
		NORTH_WEST,
		NORTH_EAST
	};

	template<typename T>
	class HexGrid {
	public:
		HexGrid(int width, int height, T start_val) : width{ width }, height{ height } {
			grid = vector<vector<T>>(height, vector<T>(width, start_val));
		}

		void move_coord(int& x, int& y, HexDir dir) {
			switch (dir)
			{
			case day24::HexDir::EAST:
				x++;
				break;
			case day24::HexDir::SOUTH_EAST:
				x += (y % 2);
				y--;
				break;
			case day24::HexDir::SOUTH_WEST:
				x -= (1 - (y % 2));
				y--;
				break;
			case day24::HexDir::WEST:
				x--;
				break;
			case day24::HexDir::NORTH_EAST:
				x += (y % 2);
				y++;
				break;
			case day24::HexDir::NORTH_WEST:
				x -= (1 - (y % 2));
				y++;
				break;
			default:
				break;
			}
		}

		void set_val(int x, int y, T val) {
			grid[y][x] = val;
		}

		T get_val(int x, int y) {
			return grid[y][x];
		}

		vector<vector<T>> grid;
		int width, height;
	};

	bool check_bounds(shared_ptr<HexGrid<TileTypes>> grid, int x, int y) {
		return x >= 0 && y >= 0 && y < grid->grid.size() && x < grid->grid[y].size();
	}

	int count_hext_grid_neighbours(shared_ptr<HexGrid<TileTypes>> grid, int x, int y) {
		int count = 0;
		int curr_x = x;
		int curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::EAST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		curr_x = x;
		curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::SOUTH_EAST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		curr_x = x;
		curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::SOUTH_WEST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		curr_x = x;
		curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::WEST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		curr_x = x;
		curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::NORTH_WEST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		curr_x = x;
		curr_y = y;
		grid->move_coord(curr_x, curr_y, HexDir::NORTH_EAST);
		if (check_bounds(grid, curr_x, curr_y) && grid->get_val(curr_x, curr_y) == TileTypes::BLACK) {
			count++;
		}
		return count;
	}

	tuple<op_value_type, op_value_type> get_tile_info(istream& file) {
		string line;
		vector<vector<HexDir>> directions;
		int grid_width = 150, grid_height = 150;
		int reference_point_x = grid_width / 2, reference_point_y = grid_height / 2;
		HexGrid<TileTypes>  grid(grid_width, grid_height, TileTypes::WHITE);

		while (getline(file, line)) {
			int i = 0;
			vector<HexDir> curr_directions;
			while (i < line.size()) {
				switch (line[i])
				{
				case 'e':
					curr_directions.push_back(HexDir::EAST);
					break;
				case 's':
					if (line[i + 1] == 'e') {
						curr_directions.push_back(HexDir::SOUTH_EAST);
					}
					else if (line[i + 1] == 'w') {
						curr_directions.push_back(HexDir::SOUTH_WEST);
					}
					i++;
					break;
				case 'w':
					curr_directions.push_back(HexDir::WEST);
					break;
				case 'n':
					if (line[i + 1] == 'e') {
						curr_directions.push_back(HexDir::NORTH_EAST);
					}
					else if (line[i + 1] == 'w') {
						curr_directions.push_back(HexDir::NORTH_WEST);
					}
					i++;
					break;
				default:
					break;
				}
				i++;
			}
			directions.push_back(curr_directions);
		}

		op_value_type black_count = 0;
		for (vector<HexDir> curr_dirs : directions) {
			int x = reference_point_x, y = reference_point_y;
			for (HexDir dir : curr_dirs) {
				grid.move_coord(x, y, dir);
			}

			TileTypes tile_type = grid.get_val(x, y);
			if (tile_type == TileTypes::WHITE) {
				grid.set_val(x, y, TileTypes::BLACK);
				black_count++;
			}
			else {
				grid.set_val(x, y, TileTypes::WHITE);
				black_count--;
			}
		}

		//Second task, (Game of life)
		shared_ptr<HexGrid<TileTypes>> src_ptr = make_shared< HexGrid<TileTypes>>(grid_width, grid_height, TileTypes::WHITE),
			dst_ptr = make_shared< HexGrid<TileTypes>>(grid_width, grid_height, TileTypes::WHITE), tmp_ptr;

		for (int y = 0; y < grid.grid.size(); ++y) {
			for (int x = 0; x < grid.grid[y].size(); ++x) {
				src_ptr->grid[y][x] = grid.grid[y][x];
			}
		}

		int turn = 0;
		while (turn < 100) {
			for (int y = 0; y < src_ptr->grid.size(); ++y) {
				for (int x = 0; x < src_ptr->grid[y].size(); ++x) {
					TileTypes res = src_ptr->get_val(x, y);
					int neighbours = count_hext_grid_neighbours(src_ptr, x, y);
					if (src_ptr->get_val(x, y) == TileTypes::BLACK) {
						if (neighbours < 1 || neighbours > 2) {
							res = TileTypes::WHITE;
						}
					}
					else if (src_ptr->get_val(x, y) == TileTypes::WHITE) {
						if (neighbours == 2) {
							res = TileTypes::BLACK;
						}
					}
					dst_ptr->set_val(x, y, res);
				}
			}

			tmp_ptr = src_ptr;
			src_ptr = dst_ptr;
			dst_ptr = tmp_ptr;
			turn++;
		}

		int curr_black_count = 0;
		for (int y = 0; y < src_ptr->grid.size(); ++y) {
			for (int x = 0; x < src_ptr->grid[y].size(); ++x) {
				if (src_ptr->get_val(x, y) == TileTypes::BLACK) {
					curr_black_count++;
				}
			}
		}

		return { black_count, curr_black_count };
	}
}