#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<limits>

namespace Advent2024_20 {

}

void Solve2024_20() {

	std::vector<std::string> board;
	std::vector<std::vector<INT32>> values;
	std::fstream file("Input/Input_20.txt");
	std::string buffor;
	int x=-1, y=0;
	while (file >> buffor) {
		board.push_back(buffor);
		int index = buffor.find('S');
		if (index != -1)x = index;
		if (x == -1)y++;
		std::vector<INT32> value(buffor.length(), INT32_MAX);
		values.push_back(value);
	}
	file.close();
	values[y][x] = 0;
	// create value table
	while (board[y][x] != 'E') {
		if (board[y - 1][x] != '#') {
			if (values[y - 1][x] > values[y][x]) {
				values[y - 1][x] = values[y][x] + 1;
				y--;
				continue;
			}
		}
		if (board[y + 1][x] != '#') {
			if (values[y + 1][x] > values[y][x]) {
				values[y + 1][x] = values[y][x] + 1;
				y++;
				continue;
			}
		}
		if (board[y][x - 1] != '#') {
			if (values[y][x - 1] > values[y][x]) {
				values[y][x - 1] = values[y][x] + 1;
				x--;
				continue;
			}
		}
		if (board[y][x + 1] != '#') {
			if (values[y][x + 1] > values[y][x]) {
				values[y][x + 1] = values[y][x] + 1;
				x++;
				continue;
			}
		}
	}
	//walk through maze
	int NOoverhundred = 0;
	for (int i = 1; i < board.size() - 1; i++) {
		for (int j = 1; j < board[0].length() - 1; j++) {
			if (board[i][j] == '#')continue;
			if (i > 1) {
				if (board[i - 2][j] != '#') {
					if (values[i - 2][j] - values[i][j] - 2 >= 100) {
						//std::cout << values[i - 2][j] - values[i][j] - 2 << "\t";
						NOoverhundred++;
					}
				}
			}
			if (i < board.size() - 2) {
				if (board[i + 2][j] != '#') {
					if (values[i + 2][j] - values[i][j] - 2 >= 100) {
						//std::cout << values[i + 2][j] - values[i][j] - 2 << "\t";
						NOoverhundred++;
					}
				}
			}
			if (j > 1) {
				if (board[i][j - 2] != '#') {
					if (values[i][j - 2] - values[i][j] - 2 >= 100) {
						//std::cout << values[i][j - 2] - values[i][j] - 2 << "\t";
						NOoverhundred++;
					}
				}
			}
			if (j < board[0].length() - 2) {
				if (board[i][j + 2] != '#') {
					if (values[i][j + 2] - values[i][j] - 2 >= 100) {
						//std::cout << values[i][j + 2] - values[i][j] - 2 << "\t";
						NOoverhundred++;
					}
				}
			}

		}
	}
	std::cout << "Advent2024_20_1: " << NOoverhundred << "\n";

	//---part 2---
	NOoverhundred = 0;
	for (int i = 1; i < board.size() - 1; i++) {
		for (int j = 1; j < board[0].length() - 1; j++) {
			if (board[i][j] == '#')continue;
			for (int offsetY = -20; offsetY <= 20; offsetY++) {
				for (int offsetX = -20 + std::abs(offsetY); offsetX <= 20 - std::abs(offsetY); offsetX++) {
					if (i + offsetY > 0 && i + offsetY < board.size() && j + offsetX > 0 && j + offsetX < board[0].length()) {
						if (board[i + offsetY][j + offsetX] == '#')continue;
						if (values[i + offsetY][j + offsetX] - values[i][j] - (std::abs(offsetY) + std::abs(offsetX)) >= 100) {
							NOoverhundred++;
						}
					}
				}
			}
		}
	}

	std::cout << "Advent2024_20_2: " << NOoverhundred << "\n";
}

