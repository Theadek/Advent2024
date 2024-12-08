#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_08 {
	int GetBoardIndex(char character) {
		if (character >= '0' && character <= '9') {
			return character - '0';
		}
		else if (character >= 'a' && character <= 'z') {
			return character - 'a' + 10;
		}
		else if (character >= 'A' && character <= 'Z') {
			return character - 'A' + 35;
		}
		else {
			return -1;
		}
	}
}


void Solve2024_08() {

	std::fstream file("Input/Input_08.txt");
	std::vector <std::vector<std::pair<int, int>>> board(60);
	std::string buffor;
	int row = 0;
	while (!file.eof()) {
		std::getline(file, buffor);
		for (int i = 0; i < buffor.length(); i++) {
			if (buffor[i] == '.')continue;
			int characterSlot = Advent2024_08::GetBoardIndex(buffor[i]);
			board[characterSlot].emplace_back(i, row);
		}
		row++;
	}
	int column = buffor.length();
	file.close();

	std::unordered_set<int> antinodes;
	for (int slot = 0; slot < 60; slot++) {
		if (board[slot].size() == 0)continue;
		for (int i = 0; i < board[slot].size() - 1; i++) {
			for (int j = i + 1; j < board[slot].size(); j++) {
				int newx = board[slot][j].first + board[slot][j].first - board[slot][i].first;
				int newy = board[slot][j].second + board[slot][j].second - board[slot][i].second;
				if (newx >= 0 && newx < column && newy >= 0 && newy < row) {
					antinodes.insert(newx * 1000 + newy);
				}
				newx = board[slot][i].first + board[slot][i].first - board[slot][j].first;
				newy = board[slot][i].second + board[slot][i].second - board[slot][j].second;
				if (newx >= 0 && newx < column && newy >= 0 && newy < row) {
					antinodes.emplace(newx * 1000 + newy);
				}
			}
		}
	}
	std::cout << "Advent2024_08_1: " << antinodes.size() << "\n";

	//---part 2---
	antinodes.clear();
	for (int slot = 0; slot < 60; slot++) {
		if (board[slot].size() == 0)continue;
		if (board[slot].size() >= 2) {
			for (int i = 0; i < board[slot].size(); i++) {
				antinodes.insert(board[slot][i].first * 1000 + board[slot][i].second);
			}
		}
		for (int i = 0; i < board[slot].size() - 1; i++) {
			for (int j = i + 1; j < board[slot].size(); j++) {
				for (int x = 1;;x++) {
					int newx = board[slot][j].first + (board[slot][j].first - board[slot][i].first) * x;
					int newy = board[slot][j].second + (board[slot][j].second - board[slot][i].second) * x;
					if (newx >= 0 && newx < column && newy >= 0 && newy < row) {
						antinodes.insert(newx * 1000 + newy);
					}
					else {
						break;
					}
				}
				for (int x = 1;; x++) {
					int newx = board[slot][i].first + (board[slot][i].first - board[slot][j].first) * x;
					int newy = board[slot][i].second + (board[slot][i].second - board[slot][j].second) * x;
					if (newx >= 0 && newx < column && newy >= 0 && newy < row) {
						antinodes.insert(newx * 1000 + newy);
					}
					else {
						break;
					}
				}
			}
		}
	}
	std::cout << "Advent2024_08_2: " << antinodes.size() << "\n";
}

