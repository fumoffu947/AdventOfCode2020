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

namespace day22 {
	using namespace std;
	using op_value_type = int;

	template<typename T>
	class Player {
	public:
		Player(vector<T> start_cards) {
			for (T val : start_cards) {
				deck.push_back(val);
			}
		}

		T draw_card() {
			T card = deck.front();
			deck.pop_front();
			return card;
		}

		void add_card(T card) {
			deck.push_back(card);
		}

		size_t size() {
			return deck.size();
		}

		bool check_repeat_n_set_state() {
			ostringstream oss;
			for (T val : deck) {
				oss << val << ",";
			}
			string curr_state = oss.str();
			if (prev_states.find(curr_state) != prev_states.end()) {
				return true;
			}
			prev_states.insert(curr_state);
			return false;
		}

		set<string> prev_states;

		deque<T> deck;
	};


	int play_game_recbat(Player<op_value_type>& player1, Player<op_value_type>& player2, bool& end_game) {
		int total_game_turns = 1;
		while (player1.size() > 0 && player2.size() > 0) {
			int winner = -1;
			//check states
			if (player1.check_repeat_n_set_state() || player2.check_repeat_n_set_state()) {
				end_game = true;
				//Player 1 won
				return 1;
			}

			op_value_type player1_card = player1.draw_card();
			op_value_type player2_card = player2.draw_card();

			if (player1_card <= player1.size() &&
				player2_card <= player2.size()) {
				vector<op_value_type> player1_sub_game_card(player1.deck.begin(), player1.deck.begin() + player1_card);
				vector<op_value_type> player2_sub_game_card(player2.deck.begin(), player2.deck.begin() + player2_card);
				Player<op_value_type> p1sg(player1_sub_game_card);
				Player<op_value_type> p2sg(player2_sub_game_card);
				winner = play_game_recbat(p1sg, p2sg, end_game);
				if (end_game && false) {
					return winner;
				}
			}

			if (winner == 1) {
				player1.add_card(player1_card);
				player1.add_card(player2_card);
			}
			else if (winner == 2) {
				player2.add_card(player2_card);
				player2.add_card(player1_card);
			}
			else {
				if (player1_card > player2_card) {
					player1.add_card(player1_card);
					player1.add_card(player2_card);
				}
				else {
					player2.add_card(player2_card);
					player2.add_card(player1_card);
				}
			}

			total_game_turns++;
		}

		if (player1.size() > 0) {
			return 1;
		}
		else {
			return 2;
		}
	}

	tuple<op_value_type, op_value_type> get_game_result(istream& file) {
		string line;
		vector<Player<op_value_type>> players;
		vector<Player<op_value_type>> players_rec_bat;

		vector<op_value_type> deck;
		while (getline(file, line)) {
			if (line.size() == 0) {
				players.push_back({ deck });
				players_rec_bat.push_back({ deck });
				deck.clear();
			}
			if (isdigit(line[0])) {
				deck.push_back(stoi(line));
			}
		}
		players.push_back({ deck });
		players_rec_bat.push_back({ deck });

		int total_game_turns = 1;
		while (players[0].size() > 0 && players[1].size() > 0) {
			op_value_type player1_card = players[0].draw_card();
			op_value_type player2_card = players[1].draw_card();

			if (player1_card > player2_card) {
				players[0].add_card(player1_card);
				players[0].add_card(player2_card);
			}
			else {
				players[1].add_card(player2_card);
				players[1].add_card(player1_card);
			}

			total_game_turns++;
		}

		int sum_mul_res = 0;
		for (Player<op_value_type> p : players) {
			for (int i = 0; i < p.deck.size(); ++i) {
				sum_mul_res += p.deck[p.deck.size() - i - 1] * (i + 1);
			}
		}

		bool end_game = false;
		int winner_rec_bat = play_game_recbat(players_rec_bat[0], players_rec_bat[1], end_game);

		int sum_mul_res_rec_bat = 0;
		for (int j = 0; j < players_rec_bat.size(); ++j) {
			for (int i = 0; i < players_rec_bat[j].deck.size(); ++i) {
				sum_mul_res_rec_bat += players_rec_bat[j].deck[players_rec_bat[j].deck.size() - i - 1] * (i + 1);
			}
		}

		return { sum_mul_res,sum_mul_res_rec_bat };
	}
}