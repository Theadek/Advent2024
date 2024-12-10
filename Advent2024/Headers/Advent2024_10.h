#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_10 {

}

void Solve2024_10() {

	std::fstream file("Input/Input_10.txt");
	std::vector<std::string> board;
	std::string buffor;
	while (file >> buffor) {
		board.push_back(buffor);
	}
	file.close();

	int answer1 = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].length(); j++) {
			if (board[i][j] != '0')continue;
			std::unordered_set<int> steps;
			steps.insert(1000 * i + j);
			for (int k = 1; k <= 9; k++) {
				std::unordered_set<int> nextSteps;
				for (const auto& step : steps) {
					int x = step / 1000;
					int y = step % 1000;
					if (x - 1 >= 0) {
						if (board[x - 1][y] - '0' == k) {
							nextSteps.insert((x - 1) * 1000 + y);
						}
					}
					if (x + 1 < board.size()) {
						if (board[x + 1][y] - '0' == k) {
							nextSteps.insert((x + 1) * 1000 + y);
						}
					}
					if (y - 1 >= 0) {
						if (board[x][y - 1] - '0' == k) {
							nextSteps.insert(x * 1000 + y - 1);
						}
					}
					if (y + 1 < board[i].length()) {
						if (board[x][y + 1] - '0' == k) {
							nextSteps.insert(x * 1000 + y + 1);
						}
					}
				}
				steps = nextSteps;
			}
			answer1 += steps.size();
		}
	}
	std::cout << "Advent2024_10_1: " << answer1 << "\n";


	//---part 2---
	int answer2 = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].length(); j++) {
			if (board[i][j] != '0')continue;
			std::vector<int> steps;
			steps.push_back(1000 * i + j);
			for (int k = 1; k <= 9; k++) {
				std::vector<int> nextSteps;
				for (const auto& step : steps) {
					int x = step / 1000;
					int y = step % 1000;
					if (x - 1 >= 0) {
						if (board[x - 1][y] - '0' == k) {
							nextSteps.push_back((x - 1) * 1000 + y);
						}
					}
					if (x + 1 < board.size()) {
						if (board[x + 1][y] - '0' == k) {
							nextSteps.push_back((x + 1) * 1000 + y);
						}
					}
					if (y - 1 >= 0) {
						if (board[x][y - 1] - '0' == k) {
							nextSteps.push_back(x * 1000 + y - 1);
						}
					}
					if (y + 1 < board[i].length()) {
						if (board[x][y + 1] - '0' == k) {
							nextSteps.push_back(x * 1000 + y + 1);
						}
					}
				}
				steps = nextSteps;
			}
			answer2 += steps.size();
		}
	}
	std::cout << "Advent2024_10_2: " << answer2 << "\n";

}

