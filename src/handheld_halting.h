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

#include <functional>
#include <map>
#include <memory>

enum OperationType {
	ACC,
	JMP,
	NOP,
};

struct Operation {
	OperationType op_type;
	int value;
};

template<typename T>
class ProgramHolder {
public:

	/*using OperationsType = std::map < OperationType, std::function<void(std::shared_ptr< ProgramHolder<T>>, T)>>;*/
	using pointer_type = ProgramHolder<T>*;
	using OperationsType = std::map < OperationType, std::function<void(pointer_type, T)>>;
	using ProgramContainer = std::vector<Operation>;


	ProgramHolder(OperationsType operations, std::vector<Operation> program) : operations{ operations },
		program{ program }, program_pointer{ 0 }, accumulator{ 0 } {}

	void step() {
		Operation op = program[program_pointer];
		operations[op.op_type](this, op.value);
	}


	T program_pointer;
	OperationsType operations;
	ProgramContainer program;
	T accumulator;
};

template<typename T>
void acc_oper(typename ProgramHolder<T>::pointer_type prog_holder, T value) {
	prog_holder->accumulator += value;
	prog_holder->program_pointer += 1;
}

template<typename T>
void jmp_oper(typename ProgramHolder<T>::pointer_type prog_holder, T value) {
	prog_holder->program_pointer += value;
}

template<typename T>
void nop_oper(typename ProgramHolder<T>::pointer_type prog_holder, T value) {
	prog_holder->program_pointer += 1;
}

namespace day8 {
	using namespace std;
	using op_value_type = int;

	tuple<op_value_type, op_value_type> get_program_info(istream& file) {
		string line;

		ProgramHolder<op_value_type>::OperationsType operations = {
			{OperationType::ACC, acc_oper<op_value_type>},
			{OperationType::JMP, jmp_oper<op_value_type>},
			{OperationType::NOP, nop_oper<op_value_type>},
		};
		
		ProgramHolder<op_value_type>::ProgramContainer program;
		vector<int> program_lines_executed;

		while (getline(file, line)) {
			istringstream iss(line);
			string op, value;
			iss >> op;
			program_lines_executed.push_back(0);
			if (op.compare("acc") == 0) {
				iss >> value;
				program.push_back({ OperationType::ACC, stoi(value) });
			}
			if (op.compare("jmp") == 0) {
				iss >> value;
				program.push_back({ OperationType::JMP, stoi(value) });
			}
			if (op.compare("nop") == 0) {
				program.push_back({ OperationType::NOP, 0});
			}
		}

		ProgramHolder<op_value_type> prog_holder(operations, program);

		while (program_lines_executed[prog_holder.program_pointer] == 0) {
			program_lines_executed[prog_holder.program_pointer]++;
			prog_holder.step();
		}


		bool test_prog = false;
		int second_prog_acc = 0;
		int prev_change = 0;
		for (int i = 0; i < program.size(); ++i) {
			ProgramHolder<op_value_type>::ProgramContainer program_copy;
			copy(program.begin(), program.end(), back_inserter(program_copy));
			test_prog = false;
			bool ok_prog = false;
			if (program[i].op_type == OperationType::NOP) {
				test_prog = true;
				program_copy[i] = { OperationType::JMP, program[i].value };
				prev_change = i;
			}
			else if (program[i].op_type == OperationType::JMP) {
				test_prog = true;
				program_copy[i] = { OperationType::NOP, program[i].value };
				prev_change = i;
			}

			ProgramHolder<op_value_type> curr_prog_holder(operations, program_copy);
			vector<int> curr_linse_executed(program_copy.size(), 0);
			while (test_prog) {
				if (curr_prog_holder.program_pointer >= program_copy.size()) {
					ok_prog = true;
					break;
				}
				if (curr_linse_executed[curr_prog_holder.program_pointer] != 0) {
					break;
				}
				curr_linse_executed[curr_prog_holder.program_pointer]++;
				curr_prog_holder.step();
			}

			if (ok_prog) {
				second_prog_acc = curr_prog_holder.accumulator;
				break;
			}
		}

		return { prog_holder.accumulator, second_prog_acc };
	}
}
