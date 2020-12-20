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

namespace day20 {
	using namespace std;
	using op_value_type = unsigned long long;
	using ID_TYPE = int;

	enum BorderInd {
		TOP=0,
		RIGHT=1,
		BOTTOM=2,
		LEFT=3
	};

	class CameraTile {
	public:
		CameraTile(ID_TYPE id, vector<string> tile) : id{ id }, tile{ tile }, neighbours{ vector<shared_ptr<CameraTile>>(4, nullptr) } {}

		vector<string> get_borders() {
			vector<string> borders;
			//Top border
			borders.push_back(tile[0]);
			//Right border
			string right_border = "";
			for (int i = 0; i < tile.size(); ++i) {
				right_border += tile[i][tile[i].size() - 1];
			}
			borders.push_back(right_border);
			//Bottom border
			string bottom(tile[tile.size() - 1].rbegin(), tile[tile.size() - 1].rend());
			borders.push_back(bottom);
			//Left border
			string left_border = "";
			for (int i = tile.size() - 1; i >= 0; --i) {
				left_border += tile[i][0];
			}
			borders.push_back(left_border);
			return borders;
		}

		void rotate_right() {
			vector<string> tile_copy(tile.begin(), tile.end());
			for (int y = 0; y < tile_copy.size(); ++y) {
				for (int x = 0; x < tile_copy[y].size(); ++x) {
					tile[x][tile.size() - y - 1] = tile_copy[y][x];
				}
			}
		}

		void rotate(int num) {
			num %= 4;
			switch (num) {
			case 1:
				rotate_right();
				break;
			case 2:
				x_flip();
				y_flip();
				break;
			case 3:
				rotate_right();
				x_flip();
				y_flip();
				break;
			default:
				break;
			}
		}

		void x_flip() {
			if (transformation_locked) {
				//throw "Transformation is locked!!!";
				return;
			}
			for (int i = 0; i < tile.size(); ++i) {
				reverse(tile[i].begin(), tile[i].end());
			}
		}

		void y_flip() {
			if (transformation_locked) {
				//throw "Transformation is locked!!!";
				return;
			}
			reverse(tile.begin(), tile.end());
		}

		void done_transforming() {
			transformation_locked = true;
		}

		void add_neighbour(shared_ptr<CameraTile> neighbour_tile) {
			neighbours_unordered.push_back(neighbour_tile);
		}

		void set_neighbour_top(shared_ptr<CameraTile> neighbour_tile) {
			neighbours[BorderInd::TOP] = neighbour_tile;
		}

		void set_neighbour_right(shared_ptr<CameraTile> neighbour_tile) {
			neighbours[BorderInd::RIGHT] = neighbour_tile;
		}

		void set_neighbour_bottom(shared_ptr<CameraTile> neighbour_tile) {
			neighbours[BorderInd::BOTTOM] = neighbour_tile;
		}

		void set_neighbour_left(shared_ptr<CameraTile> neighbour_tile) {
			neighbours[BorderInd::LEFT] = neighbour_tile;
		}

		shared_ptr<CameraTile> get_neighbour_top() {
			return neighbours[BorderInd::TOP];
		}

		shared_ptr<CameraTile> get_neighbour_right() {
			return neighbours[BorderInd::RIGHT];
		}

		shared_ptr<CameraTile> get_neighbour_bottom() {
			return neighbours[BorderInd::BOTTOM];
		}

		shared_ptr<CameraTile> get_neighbour_left() {
			return neighbours[BorderInd::LEFT];
		}

		int x, y;
		bool transformation_locked = false;
		vector<shared_ptr<CameraTile>> neighbours;
		vector<shared_ptr<CameraTile>> neighbours_unordered;
		ID_TYPE id;
		vector<string> tile;
	};

	void rotate_right(vector<string>& world) {
		vector<string> tile_copy(world.begin(), world.end());
		for (int y = 0; y < tile_copy.size(); ++y) {
			for (int x = 0; x < tile_copy[y].size(); ++x) {
				world[x][world.size() - y - 1] = tile_copy[y][x];
			}
		}
	}

	shared_ptr<CameraTile> find_right_and_rotate(shared_ptr<CameraTile> curr_tile) {
		vector<string> my_borders = curr_tile->get_borders();
		string my_bottom_border = my_borders[BorderInd::RIGHT];
		for (int i = 0; i < curr_tile->neighbours_unordered.size(); ++i) {
			shared_ptr<CameraTile> candid_bottom_tile = curr_tile->neighbours_unordered[i];
			vector<string> candid_bottom_borders = candid_bottom_tile->get_borders();
			bool rev_border = false;
			int border_comp_ind = -1;
			//Find matching border and rotate to place
			for (int j = 0; j < candid_bottom_borders.size(); ++j) {
				string tmp_rev(candid_bottom_borders[j].rbegin(), candid_bottom_borders[j].rend());
				if (my_bottom_border.compare(candid_bottom_borders[j]) == 0) {
					border_comp_ind = j;
					break;
				}
				if (my_bottom_border.compare(tmp_rev) == 0) {
					rev_border = true;
					border_comp_ind = j;
					break;
				}
			}

			if (border_comp_ind != -1) {
				//Turn the tile correctly
				int rotate_dir = 3 - border_comp_ind;
				if (rotate_dir < 0) {
					rotate_dir += 4;
				}
				candid_bottom_tile->rotate(rotate_dir);
				if (!rev_border) {
					candid_bottom_tile->y_flip();
				}
				candid_bottom_tile->done_transforming();
				return candid_bottom_tile;
			}
		}
		return nullptr;
	}

	shared_ptr<CameraTile> find_bottom_and_rotate(shared_ptr<CameraTile> curr_tile) {
		vector<string> my_borders = curr_tile->get_borders();
		string my_bottom_border = my_borders[BorderInd::BOTTOM];
		for (int i = 0; i < curr_tile->neighbours_unordered.size(); ++i) {
			shared_ptr<CameraTile> candid_bottom_tile = curr_tile->neighbours_unordered[i];
			vector<string> candid_bottom_borders = candid_bottom_tile->get_borders();
			bool rev_border = false;
			int border_comp_ind = -1;
			//Find matching border and rotate to place
			for (int j = 0; j < candid_bottom_borders.size(); ++j) {
				string tmp_rev(candid_bottom_borders[j].rbegin(), candid_bottom_borders[j].rend());
				if (my_bottom_border.compare(candid_bottom_borders[j]) == 0) {
					border_comp_ind = j;
					break;
				}
				if (my_bottom_border.compare(tmp_rev) == 0) {
					rev_border = true;
					border_comp_ind = j;
					break;
				}
			}

			if (border_comp_ind != -1) {
				//Turn the tile correctly
				int rotate_dir = 0 - border_comp_ind;
				if (rotate_dir < 0) {
					rotate_dir += 4;
				}
				candid_bottom_tile->rotate(rotate_dir);
				if (!rev_border) {
					candid_bottom_tile->x_flip();
				}
				candid_bottom_tile->done_transforming();
				return candid_bottom_tile;
			}
		}
		return nullptr;
	}

	tuple<op_value_type, op_value_type> get_camera_tile_info(istream& file) {
		string line;
		vector<shared_ptr<CameraTile>> tiles;
		vector<shared_ptr<CameraTile>> done_tiles;
		vector<shared_ptr<CameraTile>> corner_tile;

		while (getline(file, line)) {
			istringstream iss(line);
			string dummy, name;
			ID_TYPE tile_id;
			iss >> dummy >> name;
			tile_id = stoi(name.substr(0, name.size() - 1));
			vector<string> tile_data;
			while (getline(file, line)) {
				if (line.size() == 0) {
					break;
				}
				else {
					tile_data.push_back(line);
				}
			}
			tiles.push_back(make_shared<CameraTile>(tile_id, tile_data));
		}

		//find edge tiles
		int corner_index = -1;
		op_value_type mul_res_first = 1;
		for (int i = 0; i < tiles.size(); ++i) {
			shared_ptr<CameraTile> curr_tile = tiles[i];
			vector<string> my_borders = curr_tile->get_borders();
			int found_matches = 0;
			for (int j = 0; j < tiles.size(); ++j) {
				shared_ptr<CameraTile> match_tile = tiles[j];
				if (curr_tile->id == match_tile->id) {
					continue;
				}
				bool found_match = false;
				for (string my_border : my_borders) {
					for (string match_border : match_tile->get_borders()) {
						string tmp_rev(match_border.rbegin(), match_border.rend());
						if (my_border.compare(match_border) == 0) {
							found_matches++;
							found_match = true;
							break;
						}
						else if (my_border.compare(tmp_rev) == 0) {
							found_matches++;
							found_match = true;
							break;
						}
					}
					if (found_match) {
						break;
					}
				}
				if (found_match) {
					curr_tile->add_neighbour(match_tile);
				}
			}
			if (found_matches == 2) {
				mul_res_first *= curr_tile->id;
				corner_index = i;
			}
		}

		//Build the map from the tiles
		tiles[corner_index]->rotate(3);
		tiles[corner_index]->done_transforming();
		tiles[corner_index]->x = 0;
		tiles[corner_index]->y = 0;
		bool first_dir_done = false;
		BorderInd build_dir_first, build_dir_second;
		shared_ptr<CameraTile> curr_tile = tiles[corner_index];
		vector<string> my_borders = curr_tile->get_borders();
		for (int k = 0; k < curr_tile->neighbours_unordered.size(); ++k) {
			vector<string> match_tile_borders = curr_tile->neighbours_unordered[k]->get_borders();
			bool rev_match = false;
			int my_boder_match_ind = -1;
			int border_match_ind = -1;
			for (int i = 0; i < my_borders.size() && my_boder_match_ind == -1; ++i) {
				for (int j = 0; j < match_tile_borders.size() && border_match_ind == -1; ++j) {
					string tmp_rev(match_tile_borders[j].rbegin(), match_tile_borders[j].rend());
					if (my_borders[i].compare(match_tile_borders[j]) == 0) {
						my_boder_match_ind = i;
						border_match_ind = j;
						break;
					}
					else if (my_borders[i].compare(tmp_rev) == 0) {
						my_boder_match_ind = i;
						border_match_ind = j;
						rev_match = true;
						break;
					}
				}
			}
			if (!first_dir_done) {
				first_dir_done = true;
				build_dir_first = static_cast<BorderInd>(my_boder_match_ind);
			}
			else {
				build_dir_second = static_cast<BorderInd>(my_boder_match_ind);
			}
		}

		vector<string> world_text;


		//build the map, use first to start;
		shared_ptr<CameraTile> start_tile = curr_tile, next_tile;
		int start_append_text = 0;
		for (int i = 1; i < curr_tile->tile.size() - 1; ++i) {
			world_text.push_back(curr_tile->tile[i].substr(1, curr_tile->tile[i].size() - 2));
		}
		bool building = true;
		while (building) {
			//Add text
			next_tile = nullptr;
			//find right match
			next_tile = find_right_and_rotate(curr_tile);

			if (next_tile == nullptr) {
				next_tile = find_bottom_and_rotate(start_tile);
				
				curr_tile = next_tile;
				start_tile = next_tile;

				if (curr_tile != nullptr) {
					for (int i = 1; i < curr_tile->tile.size() - 1; ++i) {
						world_text.push_back(curr_tile->tile[i].substr(1, curr_tile->tile[i].size()-2));
					}
					start_append_text += curr_tile->tile.size()-2;
				}
				else {
					building = false;
				}
			}
			else {
				curr_tile = next_tile;
				//Add to end of strings
				for (int i = 1; i < curr_tile->tile.size()-1; ++i) {
					world_text[start_append_text + i-1] += curr_tile->tile[i].substr(1, curr_tile->tile[i].size() - 2);
				}
			}
		}

		int square_count = 0;
		int match_count = 0;
		for (int i = 0; i < 8 && match_count == 0; ++i) {
			if (i % 4 == 0 && i > 0) {
				reverse(world_text.begin(), world_text.end());
			}
			rotate_right(world_text);

			vector<string> sea_monster = {"                  # ", "#    ##    ##    ###", " #  #  #  #  #  #   "};

			for (int y = 0; y < world_text.size() - sea_monster.size(); ++y) {
				for (int x = 0; x < world_text[y].size() - sea_monster[0].size(); ++x) {
					//Match sea monster
					bool match = true;
					for (int i = 0; i < sea_monster.size() && match; ++i) {
						for (int j = 0; j < sea_monster[i].size() && match; ++j) {
							if (sea_monster[i][j] == '#') {
								if (world_text[y + i][x + j] != '#') {
									match = false;
								}
							}
						}
					}
					if (match) {
						match_count++;
					}
				}
			}
			if (match_count > 0) {
				for (int y = 0; y < world_text.size() - sea_monster.size(); ++y) {
					for (int x = 0; x < world_text[y].size() - sea_monster[0].size(); ++x) {
						//Match sea monster
						bool match = true;
						for (int i = 0; i < sea_monster.size() && match; ++i) {
							for (int j = 0; j < sea_monster[i].size() && match; ++j) {
								if (sea_monster[i][j] == '#') {
									if (world_text[y + i][x + j] != '#') {
										match = false;
									}
								}
							}
						}
						if (match) {
							for (int i = 0; i < sea_monster.size() && match; ++i) {
								for (int j = 0; j < sea_monster[i].size() && match; ++j) {
									if (sea_monster[i][j] == '#') {
										world_text[y + i][x + j] = '|';
									}
								}
							}
						}
					}
				}

				//Count squares
				for (int y = 0; y < world_text.size(); ++y) {
					for (int x = 0; x < world_text[y].size(); ++x) {
						if (world_text[y][x] == '#') {
							square_count++;
						}
					}
				}
			}
		}

		return { mul_res_first,square_count };
	}
}