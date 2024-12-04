#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>

namespace Advent2024_02 {
	bool CheckSafe(int valueA, int valueB) {
		if (std::abs(valueA - valueB) < 4) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Solve2024_02() {

	int safe = 0;
	bool increase;

	std::string buffor;
	std::fstream file("Input/Input_02.txt");
	while (!file.eof()) {

		std::getline(file, buffor);
		std::vector<int> line;
		while (buffor.length() > 0) {
			int index = buffor.find(' ');
			if (index == -1) {
				line.push_back(std::stoi(buffor));
				break;
			}
			else {
				line.push_back(std::stoi(buffor.substr(0, index)));
				buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			}
		}
		if (line[0] < line[1]) {
			increase = true;
		}
		else if (line[0] > line[1]) {
			increase = false;
		}
		else {
			continue;
		}
		if (!Advent2024_02::CheckSafe(line[0], line[1])) {
			continue;
		}
		bool isSafe = true;
		for (int i = 1; i < line.size() - 1; i++) {
			if ((line[i] > line[i + 1] && increase) ||
				(line[i] < line[i + 1] && !increase) ||
				(line[i] == line[i + 1]) ||
				(!Advent2024_02::CheckSafe(line[i], line[i + 1]))) {
				isSafe = false;
				break;
			}
		}
		if (isSafe) safe++;
	}
	file.close();
	std::cout << "Advent2024_02_1: " << safe << "\n";

	//---part 2---
	safe = 0;
	file.open("Input/Input_02.txt");
	while (!file.eof()) {
		std::getline(file, buffor);
		std::vector<int> line;
		while (buffor.length() > 0) {
			int index = buffor.find(' ');
			if (index == -1) {
				line.push_back(std::stoi(buffor));
				break;
			}
			else {
				line.push_back(std::stoi(buffor.substr(0, index)));
				buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			}
		}
		int isGoingUp = 0;
		int isGoingDown = 0;
		for (int i = 0; i < 3; i++) {
			if (line[i] < line[i + 1]) {
				isGoingUp++;
			}
			else if (line[i] > line[i + 1]) {
				isGoingDown++;
			}
		}
		if (isGoingUp >= 2) {
			increase = true;
		}
		else if (isGoingDown >= 2) {
			increase = false;
		}
		else {
			// too much bad
			continue;
		}
		bool isSafe = true;

		for (int ban = 0; ban < line.size(); ban++) {
			isSafe = true;
			for (int i = 0; i < line.size() - 1; i++) {
				if (i == ban)continue;
				if (i + 1 == ban) {
					if (i + 2 >= line.size()) continue;
					if ((line[i] > line[i + 2] && increase) ||
						(line[i] < line[i + 2] && !increase) ||
						(line[i] == line[i + 2]) ||
						(!Advent2024_02::CheckSafe(line[i], line[i + 2]))) {
						isSafe = false;
						break;
					}
				}
				else if ((line[i] > line[i + 1] && increase) ||
					(line[i] < line[i + 1] && !increase) ||
					(line[i] == line[i + 1]) ||
					(!Advent2024_02::CheckSafe(line[i], line[i + 1]))) {
					isSafe = false;
					break;
				}
			}
			if (isSafe) {
				break;
			}
		}
		if (isSafe) safe++;

	}

	file.close();

	std::cout << "Advent2024_02_2: " << safe << "\n";
	return;

}