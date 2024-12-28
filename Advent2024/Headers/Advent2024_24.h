#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>

namespace Advent2024_24 {
	enum class oper {
		OR = 1,
		AND = 2,
		XOR = 3
	};

	struct Rule {
		std::string part1, part2, answer;
		oper operation;

		Rule(std::string part1, std::string part2, std::string answer, std::string oper) : part1(part1), part2(part2), answer(answer) {
			if (oper == "OR") operation = oper::OR;
			else if (oper == "AND") operation = oper::AND;
			else operation = oper::XOR;
		}

		Rule(){}
	};

	bool SolveEquation(Rule& rule, std::unordered_map<std::string, int>& knownBits) {
		if (rule.operation == oper::OR) {
			if (knownBits.contains(rule.part1) && knownBits.contains(rule.part2)) {
				if (knownBits[rule.part1] == 0 && knownBits[rule.part2] == 0) {
					knownBits[rule.answer] = 0;
					return true;
				}
				else {
					knownBits[rule.answer] = 1;
					return true;
				}
			}
			if (knownBits.contains(rule.part1)) {
				if (knownBits[rule.part1] == 1) {
					knownBits[rule.answer] = 1;
					return true;
				}
			}
			if (knownBits.contains(rule.part2)) {
				if (knownBits[rule.part2] == 1) {
					knownBits[rule.answer] = 1;
					return true;
				}
			}
			return false;
		}
		else if (rule.operation == oper::AND) {
			if (knownBits.contains(rule.part1) && knownBits.contains(rule.part2)) {
				if (knownBits[rule.part1] == 1 && knownBits[rule.part2] == 1) {
					knownBits[rule.answer] = 1;
					return true;
				}
				else {
					knownBits[rule.answer] = 0;
					return true;
				}
			}
			if (knownBits.contains(rule.part1)) {
				if (knownBits[rule.part1] == 0) {
					knownBits[rule.answer] = 0;
					return true;
				}
			}
			if (knownBits.contains(rule.part2)) {
				if (knownBits[rule.part2] == 0) {
					knownBits[rule.answer] = 0;
					return true;
				}
			}
			return false;
		}
		else {
			if (knownBits.contains(rule.part1) && knownBits.contains(rule.part2)) {
				if (knownBits[rule.part1] != knownBits[rule.part2]) {
					knownBits[rule.answer] = 1;
					return true;
				}
				else {
					knownBits[rule.answer] = 0;
					return true;
				}
			}
			return false;
		}
	}
}

void Solve2024_24() {

	std::unordered_map<std::string, int> knownBits;
	std::unordered_map<std::string, Advent2024_24::Rule> rules;

	std::string buffor;
	std::fstream file("Input/Input_24.txt");
	std::getline(file, buffor);
	while (buffor != "") {
		std::string name = buffor.substr(0, 3);
		int value = std::stoi(buffor.substr(5, 1));
		knownBits[name] = value;
		std::getline(file, buffor);
	}
	while (file >> buffor) {
		std::string part1 = buffor;
		std::string operation;
		file >> operation;
		std::string part2;
		file >> part2;
		std::string answer;
		file >> answer >> answer;
		Advent2024_24::Rule rule(part1, part2, answer, operation);
		rules[answer] = rule;
	}
	file.close();

	while (!rules.empty()) {
		std::vector<std::string> toRemoveBits;
		for (auto& rule : rules) {
			if (Advent2024_24::SolveEquation(rule.second, knownBits)) {
				toRemoveBits.push_back(rule.first);
			}
		}
		for (auto& remove : toRemoveBits) {
			rules.erase(remove);
		}
	}

	long long answer = 0;
	long long mult = 1;
	for (int i = 0; i <= 99; i++) {
		std::string tmp;
		if(i > 9)tmp = "z" + std::to_string(i);
		else tmp = "z0" + std::to_string(i);
		if (!knownBits.contains(tmp))break;
		answer += knownBits[tmp] * mult;
		mult <<= 1;
	}
	std::cout << "Advent2024_24_1: " << answer << "\n";


	std::cout << "Advent2024_24_2: ";

}

