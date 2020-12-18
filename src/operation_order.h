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

namespace day18 {
	using namespace std;
	using op_value_type = long long;

	template<typename T>
	class MathOper {
	public:
		virtual T calculate() = 0;
	};

	enum MathOperations {
		ADD,
		MUL,
		NONE
	};

	template<typename T> 
	class MathValue : public MathOper<T> {
	public:
		MathValue(T val) : val{ val } {}

		T calculate() override {
			return val;
		}

		T val;
	};

	template<typename T>
	class MathAdd : public MathOper<T> {
	public:
		MathAdd(shared_ptr<MathOper<op_value_type>> l_val, shared_ptr<MathOper<op_value_type>> r_val) : l_val{ l_val }, r_val{ r_val } {}

		T calculate() {
			T lv = l_val->calculate();
			T rv = r_val->calculate();
			return lv + rv;
		}

		shared_ptr<MathOper<op_value_type>> l_val, r_val;
	};

	template<typename T>
	class MathMul : public MathOper<T> {
	public:
		MathMul(shared_ptr<MathOper<op_value_type>> l_val, shared_ptr<MathOper<op_value_type>> r_val) : l_val{ l_val }, r_val{ r_val } {}

		T calculate() {
			T lv = l_val->calculate();
			T rv = r_val->calculate();
			return lv * rv;
		}

		shared_ptr<MathOper<op_value_type>> l_val, r_val;
	};



	op_value_type get_val(string str, int& ind) {
		int start = ind;
		while (ind < str.size() && isdigit(str[ind])) {
			ind++;
		}
		string tmp = str.substr(start, (ind--) - start);
		return stoull(tmp);
	}

	shared_ptr<MathOper<op_value_type>> handle_oper(shared_ptr<MathOper<op_value_type>> prev_val, shared_ptr<MathOper<op_value_type>> curr_val, MathOperations oper_type) {
		if (prev_val == nullptr) {
			return curr_val;
		}
		else {
			switch (oper_type) {
			case MathOperations::ADD:
				return make_shared<MathAdd<op_value_type>>(prev_val, curr_val);
			case MathOperations::MUL:
				return make_shared<MathMul<op_value_type>>(prev_val, curr_val);
			case MathOperations::NONE:
				return make_shared<MathAdd<op_value_type>>(prev_val, curr_val);
			}
		}
	}

	shared_ptr<MathOper<op_value_type>> parse_line(string equation, int& ind) {
		MathOperations prev_type = MathOperations::NONE;
		shared_ptr<MathOper<op_value_type>> prev_val = nullptr;
		while (ind < equation.size()) {
			if (equation[ind] == ')') {
				return prev_val;
			}
			else if (equation[ind] == '(') {
				shared_ptr<MathOper<op_value_type>> curr_oper = parse_line(equation, ++ind);
				prev_val = handle_oper(prev_val, curr_oper, prev_type);
			}
			else if (equation[ind] == '+') {
				prev_type = MathOperations::ADD;
			}
			else if (equation[ind] == '*') {
				prev_type = MathOperations::MUL;
			}
			else if (isdigit(equation[ind])) {
				op_value_type val = get_val(equation, ind);
				shared_ptr<MathOper<op_value_type>> curr_oper = make_shared<MathValue<op_value_type>>(val);
				prev_val = handle_oper(prev_val, curr_oper, prev_type);
			}
			ind++;
		}
		return prev_val;
	}

	void handle_oper_advanced(shared_ptr<MathOper<op_value_type>>& first_val,
		shared_ptr<MathOper<op_value_type>>& middle_val,
		shared_ptr<MathOper<op_value_type>>& last_val,
		MathOperations& prev_type, MathOperations& curr_type, bool paren_end) {
		if (paren_end && curr_type == MathOperations::NONE) {
			if (prev_type == MathOperations::MUL) {
				middle_val = handle_oper(first_val, middle_val, prev_type);
				return;
			}
			else if (prev_type == MathOperations::NONE) {
				return;
			}
		}
		switch (curr_type) {
		case MathOperations::ADD:
			middle_val = handle_oper(middle_val, last_val, curr_type);
			curr_type = MathOperations::NONE;
			last_val = nullptr;
			break;
		case MathOperations::MUL:
			if (prev_type == MathOperations::MUL) {
				first_val = handle_oper(first_val, middle_val, prev_type);
				middle_val = last_val;
				last_val = nullptr;
				prev_type = curr_type;
				curr_type = MathOperations::NONE;
			}
			else {
				first_val = middle_val;
				middle_val = last_val;
				last_val = nullptr;
				prev_type = curr_type;
				curr_type = MathOperations::NONE;
			}
			break;
		case MathOperations::NONE:
			first_val = middle_val;
			middle_val = last_val;
			last_val = nullptr;
			prev_type = curr_type;
			curr_type = MathOperations::NONE;
			break;
		}

		if (paren_end) {
			if (prev_type == MathOperations::MUL) {
				middle_val = handle_oper(first_val, middle_val, prev_type);
			}
		}
	}

	shared_ptr<MathOper<op_value_type>> parse_line_advanced(string equation, int& ind) {
		MathOperations prev_type = MathOperations::NONE;
		MathOperations curr_type = MathOperations::NONE;
		shared_ptr<MathOper<op_value_type>> first_val = nullptr;
		shared_ptr<MathOper<op_value_type>> middle_val = nullptr;
		shared_ptr<MathOper<op_value_type>> last_val = nullptr;
		while (ind < equation.size()) {
			//cout << "at ind " << ind << endl;
			if (equation[ind] == ')') {
				handle_oper_advanced(first_val, middle_val, last_val, prev_type, curr_type, true);
				return middle_val;
			}
			else if (equation[ind] == '(') {
				last_val = parse_line_advanced(equation, ++ind);
				handle_oper_advanced(first_val, middle_val, last_val, prev_type, curr_type, false);
			}
			else if (equation[ind] == '+') {
				curr_type = MathOperations::ADD;
			}
			else if (equation[ind] == '*') {
				curr_type = MathOperations::MUL;
			}
			else if (isdigit(equation[ind])) {
				last_val = make_shared<MathValue<op_value_type>>(get_val(equation, ind));
				handle_oper_advanced(first_val, middle_val, last_val, prev_type, curr_type, false);
			}
			ind++;
		}
		handle_oper_advanced(first_val, middle_val, last_val, prev_type, curr_type, true);
		return middle_val;
	}

	tuple<op_value_type, op_value_type> get_math_result(istream& file) {
		string line;

		op_value_type first_sum = 0, second_sum = 0;
		while (getline(file, line)) {
			int ind = 0;
			shared_ptr<MathOper<op_value_type>> oper = parse_line(line, ind);
			ind = 0;
			shared_ptr<MathOper<op_value_type>> oper_second = parse_line_advanced(line, ind);
			first_sum += oper->calculate();
			second_sum += oper_second->calculate();
		}

		return { first_sum, second_sum };
	}
}