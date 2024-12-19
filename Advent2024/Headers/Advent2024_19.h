#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>

namespace Advent2024_19 {

}

void Solve2024_19() {

	std::vector<std::string> towels;
	std::fstream file("Input/Input_19.txt");
	std::string buffor;
	while (file >> buffor) {
		if (buffor.find(',') == -1) {
			towels.push_back(buffor);
			break;
		}
		else {
			towels.push_back(buffor.substr(0, buffor.length() - 1));
		}
	}
	int correctPatterns = 0;
	unsigned long long possibleCombinations = 0;

	while (file >> buffor) {
		std::unordered_set<std::string> attempts;
		attempts.insert("");
		bool correct = false;
		while (!attempts.empty()) {
			std::unordered_set<std::string> nextAttempts;
			for (auto& attempt : attempts) {
				if (buffor.length() == attempt.length()) {
					correct = true;
					break;
				}
				for (auto& towel : towels) {
					if (attempt.length() + towel.length() > buffor.length())continue;
					bool fit = true;
					for (int i = 0; i < towel.length(); i++) {
						if (towel[i] != buffor[attempt.length() + i]) {
							fit = false;
							break;
						}
					}
					if (fit) {
						nextAttempts.insert(attempt + towel);
					}
				}
			}
			if (correct)break;
			attempts = nextAttempts;
		}

		if (correct) {
			correctPatterns++;
		}
		else {
			continue;
		}

		//---part 2---
		attempts.clear();
		attempts.insert("");
		std::unordered_map<std::string, long long> attemptsCombo;
		attemptsCombo[""] = 1;
		while (!attempts.empty()) {
			std::unordered_set<std::string> nextAttempts;
			std::unordered_map<std::string, long long> nextCombo;
			for (auto& attempt : attempts) {
				if (buffor.length() == attempt.length()) {
					possibleCombinations += attemptsCombo[attempt];
					continue;
				}
				for (auto& towel : towels) {
					if (attempt.length() + towel.length() > buffor.length())continue;
					bool fit = true;
					for (int i = 0; i < towel.length(); i++) {
						if (towel[i] != buffor[attempt.length() + i]) {
							fit = false;
							break;
						}
					}
					if (fit) {
						nextAttempts.insert(attempt + towel);
						if (nextCombo.contains(attempt + towel)) {
							nextCombo[attempt + towel] += attemptsCombo[attempt];
						}
						else {
							nextCombo[attempt + towel] = attemptsCombo[attempt];
						}
					}
				}
			}
			attempts = nextAttempts;
			attemptsCombo = nextCombo;
		}
	}

	file.close();

	std::cout << "Advent2024_19_1: " << correctPatterns << "\n";
	std::cout << "Advent2024_19_2: " << possibleCombinations << "\n";
}

