#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_05 {

}

void Solve2024_05() {

	std::fstream file("Input/Input_05.txt");
	std::vector<std::pair<int, int>> rules;
	std::vector<std::vector<int>> data;

	// process input
	std::string buffor = "";
	std::getline(file, buffor);
	do {
		rules.emplace_back(std::stoi(buffor.substr(0, 2)), std::stoi(buffor.substr(3, 2)));
		std::getline(file, buffor);
	} while (buffor != "");

	while (file >> buffor) {
		std::vector<int> line;
		int index = 0;
		while (index != -1) {
			index = buffor.find(',');
			if (index != -1) {
				line.push_back(std::stoi(buffor.substr(0, index)));
				buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			}
			else {
				line.push_back(std::stoi(buffor));
			}
		}
		data.push_back(line);
	}
	file.close();

	//---part 1---
	int answer = 0;
	int answer2 = 0;
	for (int line = 0; line < data.size(); line++) {
		bool isGood = true;
		for (int rule = 0; rule < rules.size(); rule++) {
			int culprit = 0;
			for (int i = 0; i < data[line].size(); i++) {
				if (data[line][i] == rules[rule].first) break;
				if (data[line][i] == rules[rule].second) {
					isGood = false;
					culprit = i + 1;
					break;
				}
			}
			if (isGood) {
				continue;
			}
			else {
				//check if first number is somewhere next
				isGood = true;
				for (; culprit < data[line].size(); culprit++) {
					if (data[line][culprit] == rules[rule].first) {
						isGood = false;
						break;
					}
				}
				if (!isGood)break;
			}
		}
		if (isGood) {
			answer += data[line][data[line].size() / 2];
		}
		else {
			//---part 2---
			//sort them correctly and get answer
			for (int i = 0; i < data[line].size() - 1; i++) {
				for (int j = 0; j < data[line].size() - 1; j++) {
					for (int rule = 0; rule < rules.size(); rule++) {
						if (data[line][j + 1] == rules[rule].first &&
							data[line][j] == rules[rule].second) {
							int tmp = data[line][j + 1];
							data[line][j + 1] = data[line][j];
							data[line][j] = tmp;
							break;
						}
					}
				}
			}
			answer2 += data[line][data[line].size() / 2];
		}
	}

	std::cout << "Advent2024_05_1: " << answer << "\n";
	std::cout << "Advent2024_05_2: " << answer2 << "\n";
}

