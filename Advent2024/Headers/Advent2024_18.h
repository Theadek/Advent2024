#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_18 {

}

void Solve2024_18() {
	const int BOARD_SIZE = 71;


	bool board[BOARD_SIZE][BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			board[i][j] = false;

	std::fstream file("Input/Input_18.txt");
	std::string buffor;
	for (int i = 0; i < 1024; i++) {
		file >> buffor;
		int index = buffor.find(',');
		int x = std::stoi(buffor.substr(0, index));
		int y = std::stoi(buffor.substr(index+1, buffor.length()-index-1));
		board[y][x] = true;
	}


	std::unordered_set<int> visited;
	std::unordered_set<int> steps;
	visited.insert(0);
	steps.insert(0);
	int NOsteps = 0;
	while (true) {
		std::unordered_set<int> nextSteps;
		bool found = false;
		for (auto& step : steps) {
			int x = step / 1000;
			int y = step % 1000;
			if (x == BOARD_SIZE-1 && y == BOARD_SIZE-1) {
				found = true;
				break;
			}
			if (x - 1 >= 0) {
				if (!visited.contains((x - 1) * 1000 + y) && !board[y][x - 1]) {
					visited.insert((x - 1) * 1000 + y);
					nextSteps.insert((x - 1) * 1000 + y);
				}
			}
			if (x + 1 < BOARD_SIZE) {
				if (!visited.contains((x + 1) * 1000 + y) && !board[y][x + 1]) {
					visited.insert((x + 1) * 1000 + y);
					nextSteps.insert((x + 1) * 1000 + y);
				}
			}
			if (y - 1 >= 0) {
				if (!visited.contains(x * 1000 + y - 1) && !board[y - 1][x]) {
					visited.insert(x * 1000 + y - 1);
					nextSteps.insert(x* 1000 + y - 1);
				}
			}
			if (y + 1 < BOARD_SIZE) {
				if (!visited.contains(x * 1000 + y + 1) && !board[y + 1][x]) {
					visited.insert(x * 1000 + y + 1);
					nextSteps.insert(x * 1000 + y + 1);
				}
			}
		}
		if (found)break;
		steps = nextSteps;
		NOsteps++;
	}
	std::cout << "Advent2024_18_1: " << NOsteps << "\n";

	//---part 2---
	while (file >> buffor) {
		int index = buffor.find(',');
		int x = std::stoi(buffor.substr(0, index));
		int y = std::stoi(buffor.substr(index + 1, buffor.length() - index - 1));
		board[y][x] = true;

		visited.clear();
		steps.clear();
		visited.insert(0);
		steps.insert(0);
		bool found = false;

		while (!found) {
			std::unordered_set<int> nextSteps;
			for (auto& step : steps) {
				x = step / 1000;
				y = step % 1000;
				if (x == BOARD_SIZE-1 && y == BOARD_SIZE-1) {
					found = true;
					break;
				}
				if (x - 1 >= 0) {
					if (!visited.contains((x - 1) * 1000 + y) && !board[y][x - 1]) {
						visited.insert((x - 1) * 1000 + y);
						nextSteps.insert((x - 1) * 1000 + y);
					}
				}
				if (x + 1 < BOARD_SIZE) {
					if (!visited.contains((x + 1) * 1000 + y) && !board[y][x + 1]) {
						visited.insert((x + 1) * 1000 + y);
						nextSteps.insert((x + 1) * 1000 + y);
					}
				}
				if (y - 1 >= 0) {
					if (!visited.contains(x * 1000 + y - 1) && !board[y - 1][x]) {
						visited.insert(x * 1000 + y - 1);
						nextSteps.insert(x * 1000 + y - 1);
					}
				}
				if (y + 1 < BOARD_SIZE) {
					if (!visited.contains(x * 1000 + y + 1) && !board[y + 1][x]) {
						visited.insert(x * 1000 + y + 1);
						nextSteps.insert(x * 1000 + y + 1);
					}
				}
			}
			steps = nextSteps;
			if (steps.empty()) {
				break;
			}
		}
		if (!found)break;
	}
	file.close();

	//draw board;
	/*for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j]) std::cout << "#";
			else if (visited.contains(j * 1000 + i)) {
				std::cout << "O";
			}
			else {
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}*/


	std::cout << "Advent2024_18_2: " << buffor << "\n";
}

