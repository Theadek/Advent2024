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
	void SwapRules(Rule& rule1, Rule& rule2, std::unordered_map<std::string, Advent2024_24::Rule>& rules) {
		//std::swap(rules[rule1.answer].answer, rules[rule2.answer].answer);
		std::swap(rule1.answer, rule2.answer);
		std::swap(rule1, rule2);
		//rules[rule1.answer] = rule1;
		//rules[rule2.answer] = rule2;
	}

	std::string OperToString(oper operation) {
		switch (operation) {
		case oper::OR:
			return "OR";
		case oper::AND:
			return "AND";
		case oper::XOR:
			return "XOR";
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

	std::unordered_map<std::string, Advent2024_24::Rule> savedRules = rules;
	std::unordered_map<std::string, int> savedKnownBits = knownBits;

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
	//---part 2---
	//TODO calculate expected z00 -> z??
	std::vector<int> expectedZ;
	int remember = 0;
	for (int i = 0; i <= 99; i++) {
		std::string tmpX;
		std::string tmpY;
		if (i > 9) {
			tmpX = "x" + std::to_string(i);
			tmpY = "y" + std::to_string(i);
		}
		else {
			tmpX = "x0" + std::to_string(i);
			tmpY = "y0" + std::to_string(i);
		}
		if (!knownBits.contains(tmpX)) {
			if (remember == 1)expectedZ.push_back(1);
			break;
		}
		int z = knownBits[tmpX] + knownBits[tmpY] + remember;
		if (z >= 2) {
			remember = 1;
			z -= 2;
			expectedZ.push_back(z);
		}
		else {
			remember = 0;
			expectedZ.push_back(z);
		}
	}

	rules = savedRules;
	knownBits = savedKnownBits;
	Advent2024_24::SwapRules(rules["qnw"], rules["qff"], rules);
	Advent2024_24::SwapRules(rules["z16"], rules["pbv"], rules);
	Advent2024_24::SwapRules(rules["z23"], rules["qqp"], rules);
	Advent2024_24::SwapRules(rules["z36"], rules["fbq"], rules);


	for (int i = 2; i <= 44; i++) {
		std::string tmpX;
		if (i > 9) {
			tmpX = "z" + std::to_string(i);
		}
		else {
			tmpX = "z0" + std::to_string(i);
		}
		std::cout << tmpX << ": " << rules[tmpX].part1 << " " << Advent2024_24::OperToString(rules[tmpX].operation) << " " << rules[tmpX].part2 << "\t";

		if (rules[tmpX].part1[0] != 'x' && rules[tmpX].part1[0] != 'y') {
			if (Advent2024_24::OperToString(rules[rules[tmpX].part1].operation) == "XOR") {
				std::cout << rules[tmpX].part1 << " = " << rules[rules[tmpX].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[tmpX].part1].operation) << " " << rules[rules[tmpX].part1].part2 << "\t";
				std::cout << rules[tmpX].part2 << " = " << rules[rules[tmpX].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[tmpX].part2].operation) << " " << rules[rules[tmpX].part2].part2 << "\t";
			}
			else {
				std::cout << rules[tmpX].part2 << " = " << rules[rules[tmpX].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[tmpX].part2].operation) << " " << rules[rules[tmpX].part2].part2 << "\t";
				std::cout << rules[tmpX].part1 << " = " << rules[rules[tmpX].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[tmpX].part1].operation) << " " << rules[rules[tmpX].part1].part2 << "\t";
			}
		}
		else {
			std::cout << "\n";
			continue;
		}

		if (rules[rules[tmpX].part1].part1[0] != 'x' && rules[rules[tmpX].part1].part1[0] != 'y') {
			if (rules[rules[rules[tmpX].part1].part1].part1[0] == 'x' || rules[rules[rules[tmpX].part1].part1].part1[0] == 'y') {
				std::cout << rules[rules[tmpX].part1].part1 << " = " << rules[rules[rules[tmpX].part1].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part1].part1].operation) << " " << rules[rules[rules[tmpX].part1].part1].part2 << "\t";
				std::cout << rules[rules[tmpX].part1].part2 << " = " << rules[rules[rules[tmpX].part1].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part1].part2].operation) << " " << rules[rules[rules[tmpX].part1].part2].part2 << "\t";
			}
			else {
				std::cout << rules[rules[tmpX].part1].part2 << " = " << rules[rules[rules[tmpX].part1].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part1].part2].operation) << " " << rules[rules[rules[tmpX].part1].part2].part2 << "\t";
				std::cout << rules[rules[tmpX].part1].part1 << " = " << rules[rules[rules[tmpX].part1].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part1].part1].operation) << " " << rules[rules[rules[tmpX].part1].part1].part2 << "\t";
			}
		}
		if (rules[rules[tmpX].part2].part1[0] != 'x' && rules[rules[tmpX].part2].part1[0] != 'y') {
			if (rules[rules[rules[tmpX].part2].part1].part1[0] == 'x' || rules[rules[rules[tmpX].part2].part1].part1[0] == 'y') {
				std::cout << rules[rules[tmpX].part2].part1 << " = " << rules[rules[rules[tmpX].part2].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part2].part1].operation) << " " << rules[rules[rules[tmpX].part2].part1].part2 << "\t";
				std::cout << rules[rules[tmpX].part2].part2 << " = " << rules[rules[rules[tmpX].part2].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part2].part2].operation) << " " << rules[rules[rules[tmpX].part2].part2].part2 << "\t";
			}
			else {
				std::cout << rules[rules[tmpX].part2].part2 << " = " << rules[rules[rules[tmpX].part2].part2].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part2].part2].operation) << " " << rules[rules[rules[tmpX].part2].part2].part2 << "\t";
				std::cout << rules[rules[tmpX].part2].part1 << " = " << rules[rules[rules[tmpX].part2].part1].part1 << " " << Advent2024_24::OperToString(rules[rules[rules[tmpX].part2].part1].operation) << " " << rules[rules[rules[tmpX].part2].part1].part2 << "\t";
			}
		}
		std::cout << "\n";
	}

	std::cout << "\n\n";


	while (!rules.empty()) {
		std::vector<std::string> toRemoveBits;
		for (auto& rule : rules) {
			if (Advent2024_24::SolveEquation(rule.second, knownBits)) {
				toRemoveBits.push_back(rule.first);
			}
		}
		if (toRemoveBits.empty()) {
			break;
		}
		for (auto& remove : toRemoveBits) {
			rules.erase(remove);
		}
	}


	//debug
	std::cout << "  ";
	for (int i = 44; i >= 0; i--) {
		std::string tmpX;
		if (i > 9) {
			tmpX = "x" + std::to_string(i);

		}
		else {
			tmpX = "x0" + std::to_string(i);
		}
		std::cout << knownBits[tmpX];
	}
	std::cout << "\n +";
	for (int i = 44; i >= 0; i--) {
		std::string tmpX;
		if (i > 9) {
			tmpX = "y" + std::to_string(i);
		}
		else {
			tmpX = "y0" + std::to_string(i);
		}
		std::cout << knownBits[tmpX];
	}
	std::cout << "\n=";
	for (int i = 45; i >= 0; i--) {
		std::string tmpX;
		if (i > 9) {
			tmpX = "z" + std::to_string(i);
		}
		else {
			tmpX = "z0" + std::to_string(i);
		}
		std::cout << knownBits[tmpX];
	}
	std::cout << "\n!";
	for (int i = 45; i >= 0; i--) {
		std::cout << expectedZ[i];
	}
	std::cout << "\n\n";

	//debug end


	std::vector<std::string> changes;
	changes.push_back("qnw");
	changes.push_back("qff");
	changes.push_back("z16");
	changes.push_back("pbv");
	changes.push_back("z23");
	changes.push_back("qqp");
	changes.push_back("z36");
	changes.push_back("fbq");
	std::sort(changes.begin(), changes.end());
	std::cout << "Advent2024_24_2: " << changes[0];
	for (int i = 1; i < 8; i++) {
		std::cout << "," << changes[i];
	}
	std::cout << "\n";
	/*
	for (auto& v1 : savedRules) {
		for (auto& v2 : savedRules) {
			if (v1.first == v2.first)continue;
			for (auto& v3 : savedRules) {
				if (v1.first == v3.first || v2.first == v3.first)continue;
				for (auto& v4 : savedRules) {
					if (v1.first == v4.first || v2.first == v4.first || v3.first == v4.first)continue;
					for (auto& v5 : savedRules) {
						if (v1.first == v5.first || v2.first == v5.first || v3.first == v5.first || v4.first == v5.first)continue;
						for (auto& v6 : savedRules) {
							if (v1.first == v6.first || v2.first == v6.first || v3.first == v6.first || v4.first == v6.first || v5.first == v6.first)continue;
							for (auto& v7 : savedRules) {
								if (v1.first == v7.first || v2.first == v7.first || v3.first == v7.first || v4.first == v7.first || v5.first == v7.first || v6.first == v7.first)continue;
								for (auto& v8 : savedRules) {
									if (v1.first == v8.first || v2.first == v8.first || v3.first == v8.first || v4.first == v8.first || v5.first == v8.first || v6.first == v8.first || v7.first == v8.first)continue;
									rules = savedRules;
									knownBits = savedKnownBits;
									Advent2024_24::SwapRules(v1.second, v2.second, rules);
									Advent2024_24::SwapRules(v3.second, v4.second, rules);
									Advent2024_24::SwapRules(v5.second, v6.second, rules);
									Advent2024_24::SwapRules(v7.second, v8.second, rules);
									bool good = true;
									while (!rules.empty()) {
										std::vector<std::string> toRemoveBits;
										for (auto& rule : rules) {
											if (Advent2024_24::SolveEquation(rule.second, knownBits)) {
												toRemoveBits.push_back(rule.first);
											}
										}
										if (toRemoveBits.empty()) {
											good = false;
											break;
										}
										for (auto& remove : toRemoveBits) {
											rules.erase(remove);
										}
									}
									if (good) {
										//todo check for correct z?? values
										for (int i = 0; i <= 45; i++) {
											std::string tmp;
											if (i > 9)tmp = "z" + std::to_string(i);
											else tmp = "z0" + std::to_string(i);
											if (!knownBits.contains(tmp)) {
												good = false;
												break;
											}
											if (expectedZ[i] != knownBits[tmp]) {
												good = false;
												break;
											}
										}
										if (good) {
											//debug
											for (int i = 45; i >= 0; i--) {
												std::string tmpX;
												if (i > 9) {
													tmpX = "z" + std::to_string(i);
												}
												else {
													tmpX = "z0" + std::to_string(i);
												}
												std::cout << knownBits[tmpX];
											}
											std::cout << "\t";
											//debug end
											std::vector<std::string> answer2{v1.first,v2.first,v3.first,v4.first,v5.first,v6.first,v7.first,v8.first};
											std::sort(answer2.begin(), answer2.end());
											//std::cout << "Advent2024_24_2: ";
											for (auto& ans : answer2) {
												std::cout << ans << ",";
											}
											std::cout << "\n";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	*/



}

