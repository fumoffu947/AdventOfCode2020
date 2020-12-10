#pragma once
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <string>

using namespace std;
using op_value_type = int;

struct PasswordPolicy {
	string passwd;
	char policy_char;
	int low_count, high_count;
};

tuple<op_value_type, op_value_type> get_password_info(istream& file) {
	string line;
	vector<PasswordPolicy> passwd_lines;
	int sum_val = 2020;

	while (getline(file, line)) {
		size_t pos1 = line.find('-', 0);
		size_t pos2 = line.find(' ', pos1);
		int low_count = stoi(line.substr(0, pos1));
		int high_count = stoi(line.substr(pos1 + 1, pos2));
		pos1 = line.find(':', pos2);
		char policy_char = line[pos1 - 1];
		pos2 = line.find(' ', pos1);
		string passwd = line.substr(pos2 + 1);
		passwd_lines.push_back({ passwd, policy_char, low_count, high_count });
	}

	int ok_psswd_count = 0;
	int ok_psswd_count_second = 0;
	for (PasswordPolicy pp : passwd_lines) {
		int policy_char_count = 0;
		for (char c : pp.passwd) {
			if (c == pp.policy_char) {
				policy_char_count++;
			}
		}
		if (policy_char_count >= pp.low_count&& policy_char_count <= pp.high_count) {
			ok_psswd_count++;
		}

		int char_equal_count = 0;
		if (pp.passwd[pp.low_count - 1] == pp.policy_char) {
			char_equal_count++;
		}
		if (pp.passwd[pp.high_count - 1] == pp.policy_char) {
			char_equal_count++;
		}

		if (char_equal_count == 1) {
			ok_psswd_count_second++;
		}
	}

	return { ok_psswd_count, ok_psswd_count_second };
}