#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>

using namespace std;

int main() {
	// Change console charset to UTF-8
	system("chcp 65001 > nul");

	ifstream sourceFile("source.asm");
	string sourceLine;

	struct instruction {
		string opcode, arg = "";
	};

	vector<instruction> sourceData;

	// Read line by line
	while (getline(sourceFile, sourceLine)) {
		string tmpLine = "";

		// Remove spaces
		sourceLine.erase(remove(sourceLine.begin(), sourceLine.end(), ' '), sourceLine.end());
		sourceLine.erase(remove(sourceLine.begin(), sourceLine.end(), '\t'), sourceLine.end());

		// Read line by chars
		for (int i = 0; i < sourceLine.length(); i++) {
			// Ignore comments
			if (sourceLine[i] != ';') {
				tmpLine += sourceLine[i];
			} else {
				break;
			}
		}

		// Ignore empty lines (\n)
		if (tmpLine != "") {
			// Ignore instructions without args
			if (tmpLine == "IN" || tmpLine == "OUT") {
				sourceData.push_back({opcode: tmpLine});
			} else {
				sourceData.push_back({opcode: tmpLine.substr(0, 3), arg: tmpLine.substr(3, tmpLine.length())});
			}
		}
	}

	// CPU Registers
	struct CPU {
		int pc = 0;
		int acc = 0;

		int memory[255] = {};
	} CPU;

	// Emulate post-processed instructions
	while (CPU.pc < sourceData.size()) {
		auto curInst = sourceData[CPU.pc];

		cout << "====================\n";

		cout << "OPCODE:\t" << curInst.opcode << endl;
		cout << "ARG:\t" << curInst.arg << endl;

		// Input
		if (curInst.opcode == "IN") {
			cout << "IN:\t";
			cin >> CPU.acc;
		}
		// Output accumulator
		if (curInst.opcode == "OUT") {
			cout << "OUT:\t" << CPU.acc << endl;
		}

		// Load memory to accumulator
		if (curInst.opcode == "LDA") {
			CPU.acc = CPU.memory[stoi(curInst.arg, nullptr, 16)];
		}
		// Load value to accumulator
		if (curInst.opcode == "LDI") {
			CPU.acc = stoi(curInst.arg, nullptr, 10);
		}
		// Store accumulator to memory address
		if (curInst.opcode == "STA") {
			CPU.memory[stoi(curInst.arg, nullptr, 16)] = CPU.acc;
		}

		// Add accumulator + memory
		if (curInst.opcode == "ADD") {
			CPU.acc += CPU.memory[stoi(curInst.arg, nullptr, 16)];
		}
		// Sub accumulator - memory
		if (curInst.opcode == "SUB") {
			CPU.acc -= CPU.memory[stoi(curInst.arg, nullptr, 16)];
		}

		CPU.pc++;

		// Jump without condition
		if (curInst.opcode == "JMP") {
			CPU.pc = stoi(curInst.arg, nullptr, 16);
		}
		// Jump if accumulator == 0
		if (curInst.opcode == "JEZ") {
			if (CPU.acc == 0) {
				CPU.pc = stoi(curInst.arg, nullptr, 16);
			}
		}
		// Jump if accumulator > 0
		if (curInst.opcode == "JGZ") {
			if (CPU.acc > 0) {
				CPU.pc = stoi(curInst.arg, nullptr, 16);
			}
		}

		cout << "ACC:\t" << CPU.acc << endl;
		printf("PC:\t0x%.2X\n", CPU.pc);

		cout << "====================\n\n";

		// Halt
		if (curInst.opcode == "HLT") {
			break;
		}

		cin.get();
	}
}