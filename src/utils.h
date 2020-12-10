#pragma once
#include <algorithm>
#include <chrono>
#include <locale>
#include <map>
#include <string>
#include <vector>

struct csv_reader : std::ctype<char> {
	csv_reader() : std::ctype<char>(get_table()) {}
	static std::ctype_base::mask const* get_table() {
		static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

		rc[','] = std::ctype_base::space;
		rc[' '] = std::ctype_base::space;
		return &rc[0];
	}
};

struct backslash_reader : std::ctype<char> {
	backslash_reader() : std::ctype<char>(get_table()) {}
	static std::ctype_base::mask const* get_table() {
		static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

		rc['/'] = std::ctype_base::space;
		rc[' '] = std::ctype_base::space;
		return &rc[0];
	}
};

int getValue(std::string value, std::map<std::string, int>& registers) {
	if (std::all_of(begin(value), end(value), isalpha)) {
		return registers[value];
	}
	return std::stoi(value);
}

long long getValueLong(std::string value, std::map<std::string, long long>& registers) {
	if (std::all_of(begin(value), end(value), isalpha)) {
		return registers[value];
	}
	return std::stoll(value);
}

struct PrecisionTimer {
	std::chrono::high_resolution_clock::time_point startTime;

	void tick() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	std::string tock() {
		return  std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count());
	}
};
