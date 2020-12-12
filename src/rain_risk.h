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

namespace day12 {
	const double PI = 3.14159265358979323846;
	using namespace std;
	using op_value_type = int;

	enum Direction {
		N,
		S,
		E,
		W,
		L,
		R,
		F
	};

	struct Actions {
		Direction dir;
		op_value_type value;
	};

	double toRad(int deg) {
		return ((double)deg) * (PI / 180.0);
	}

	template<typename T>
	class Boat {
	public:
		Boat() : x{ 0 }, y{ 0 }, dir{ 0 } {}

		void handle_action(Actions action) {
			switch (action.dir) {
			case N:
			case E:
			case S:
			case W:
			case F:
				move(action.dir, action.value);
				break;
			case R:
			case L:
				turn(action.dir, action.value);
				break;
			}
		}

		void move(Direction direction, T dist) {
			switch (direction) {
			case N:
				y += dist;
				break;
			case E:
				x += dist;
				break;
			case S:
				y -= dist;
				break;
			case W:
				x -= dist;
				break;
			case F:
				x += dist * (T)round(cos(toRad(dir)));
				y += dist * (T)round(sin(toRad(dir)));
				break;
			}
		}

		void turn(Direction direction, T deg) {
			switch (direction) {
			case R:
				dir -= deg;
				if (dir < 0) {
					dir += 360;
				}
				break;
			case L:
				dir += deg;
				dir %= 360;
				break;
			default:
				break;
			}
		}

		T x, y;
		T dir;
	};

	template<typename T>
	class WaypointBoat {
	public:
		WaypointBoat(op_value_type wp_x, op_value_type wp_y) : x{ 0 }, y{ 0 }, waypoint_x{ wp_x }, waypoint_y{ wp_y }, dir{ 0 } {}

		void handle_action(Actions action) {
			switch (action.dir) {
			case N:
			case E:
			case S:
			case W:
				move_wp(action.dir, action.value);
				break;
			case F:
				move(action.dir, action.value);
				break;
			case R:
			case L:
				turn_wp(action.dir, action.value);
				break;
			}
		}

		void move(Direction direction, T dist) {
			switch (direction) {
			case F:
				x += dist * waypoint_x;
				y += dist * waypoint_y;
				break;
			default:
				break;
			}
		}

		void move_wp(Direction direction, T dist) {
			switch (direction) {
			case N:
				waypoint_y += dist;
				break;
			case E:
				waypoint_x += dist;
				break;
			case S:
				waypoint_y -= dist;
				break;
			case W:
				waypoint_x -= dist;
				break;
			default:
				break;
			}
		}

		void turn_wp(Direction direction, T deg) {
			switch (direction) {
			case R:
				deg = -deg;
				break;
			default:
				break;
			}
			double cos_v = cos(toRad(deg));
			double sin_v = sin(toRad(deg));
			
			double tmp_x = waypoint_x * cos_v - waypoint_y * sin_v;
			double tmp_y = waypoint_x * sin_v + waypoint_y * cos_v;
			waypoint_x = (int)round(tmp_x);
			waypoint_y = (int)round(tmp_y);
		}

		T x, y;
		T waypoint_x, waypoint_y;
		T dir;
	};

	tuple<op_value_type, op_value_type> get_boat_info(istream& file) {
		string line;
		Boat<op_value_type> boat;
		WaypointBoat<op_value_type> wp_boat = { 10,1 };
		vector<Actions> actions;

		while (getline(file, line)) {
			op_value_type val = stoi(line.substr(1));
			char action = line[0];
			switch (action) {
			case 'N':
				actions.push_back({ Direction::N, val });
				break;
			case 'S':
				actions.push_back({ Direction::S, val });
				break;
			case 'E':
				actions.push_back({ Direction::E, val });
				break;
			case 'W':
				actions.push_back({ Direction::W, val });
				break;
			case 'L':
				actions.push_back({ Direction::L, val });
				break;
			case 'R':
				actions.push_back({ Direction::R, val });
				break;
			case 'F':
				actions.push_back({ Direction::F, val });
				break;
			}
		}

		for (Actions action : actions) {
			boat.handle_action(action);
			wp_boat.handle_action(action);
		}

		return { abs(boat.x) + abs(boat.y), abs(wp_boat.x) + abs(wp_boat.y) };
	}
}
