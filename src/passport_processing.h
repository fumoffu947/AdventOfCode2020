#pragma once
#include <iostream>
#include <istream>
#include <tuple>
#include <vector>
#include <string>
#include <valarray>
#include <regex>

namespace day4 {
	using namespace std;
	using op_value_type = long long;

	struct Passport {
		string byr;
		string iyr;
		string eyr;
		string hgt;
		string hcl;
		string ecl;
		string pid;
		string cid;
		string line;
	} ;

	void print_passport(Passport p) {
		cout << "curr pp " <<
			"byr:" << p.byr << "," <<	
			"iyr:" << p.iyr << "," <<
			"eyr:" << p.eyr << "," <<
			"hgt:" << p.hgt << "," <<
			"hcl:" << p.hcl << "," <<
			"ecl:" << p.ecl << "," <<
			"pid:" << p.pid << "," <<
			"cid:" << p.cid << "," << endl;
	}

	tuple<op_value_type, op_value_type> get_passport_validation_info(istream& file) {
		string line;
		vector<Passport> passports;

		Passport curr_pp;
		while (getline(file, line)) {
			if (line.size() == 0) {
				passports.push_back(curr_pp);
				curr_pp = {};
			}
			else {
				curr_pp.line += line;
				bool parsing = true;
				size_t pair_sep_pos, end_pos = -1;
				while (parsing) {
					size_t start_pos = end_pos + 1;
					pair_sep_pos = line.find(':', start_pos);
					end_pos = line.find(' ', pair_sep_pos);
					parsing = end_pos != string::npos;
					string key_str = line.substr(start_pos, pair_sep_pos - start_pos);
					string val_str = line.substr(pair_sep_pos + 1, end_pos != string::npos ? end_pos - (pair_sep_pos + 1) : line.size());

					if (key_str.compare("byr") == 0) {
						curr_pp.byr = val_str;
					}
					else if (key_str.compare("iyr") == 0) {
						curr_pp.iyr = val_str;
					}
					else if (key_str.compare("eyr") == 0) {
						curr_pp.eyr = val_str;
					}
					else if (key_str.compare("hgt") == 0) {
						curr_pp.hgt = val_str;
					}
					else if (key_str.compare("hcl") == 0) {
						curr_pp.hcl = val_str;
					}
					else if (key_str.compare("ecl") == 0) {
						curr_pp.ecl = val_str;
					}
					else if (key_str.compare("pid") == 0) {
						curr_pp.pid = val_str;
					}
					else if (key_str.compare("cid") == 0) {
						curr_pp.cid = val_str;
					}
				}
			}
		}
		passports.push_back(curr_pp);

		int valid_passports_first = 0;
		int valid_passports_second = 0;
		for (Passport p : passports) {
			bool valid_first = true;
			bool valid_second = true;
			if (p.byr.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				if (p.byr.size() != 4) {
					valid_second = false;
				}
				int byr = stoi(p.byr);
				if (byr < 1920 || byr > 2002) {
					valid_second = false;
				}
			}
			if (p.iyr.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				if (p.iyr.size() != 4) {
					valid_second = false;
				}
				int iyr = stoi(p.iyr);
				if (iyr < 2010 || iyr > 2020) {
					valid_second = false;
				}
			}
			if (p.eyr.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				if (p.eyr.size() != 4) {
					valid_second = false;
				}
				int eyr = stoi(p.eyr);
				if (eyr < 2020 || eyr > 2030) {
					valid_second = false;
				}
			}
			if (p.hgt.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				int si_pos = p.hgt.size() - 2;
				if (p.hgt[si_pos] == 'c') {
					int height = stoi(p.hgt.substr(0, p.hgt.size() - 2));
					if (height < 150 || height > 193) {
						valid_second = false;
					}
				}
				else if (p.hgt[p.hgt.size() - 2] == 'i') {
					int height = stoi(p.hgt.substr(0, p.hgt.size() - 2));
					if (height < 59 || height > 76) {
						valid_second = false;
					}
				}
				else {
					valid_second = false;
				}

			}

			if (p.hcl.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				regex regex_str{ "#[a-f0-9]{6}" };
				if (!regex_match(p.hcl, regex_str)) {
					valid_second = false;
				}
			}
			if (p.ecl.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				regex regex_str{ "amb|blu|brn|gry|grn|hzl|oth" };
				if (!regex_match(p.ecl, regex_str)) {
					valid_second = false;
				}
			}
			if (p.pid.size() == 0) {
				valid_first = false;
				valid_second = false;
			}
			else {
				regex regex_str{ "[0-9]{9}" };
				if (!regex_match(p.pid, regex_str)) {
					valid_second = false;
				}
			}

			if (valid_first) {
				valid_passports_first++;
			}
			if (valid_second) {
				valid_passports_second++;
			}
		}

		return { valid_passports_first, valid_passports_second};
	}
}