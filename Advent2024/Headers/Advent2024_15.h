#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_15 {
	void SimulateMovement(std::vector<std::string>& board, int& positionX, int& positionY, char direction) {
		if (direction == '<') {
			if (board[positionY][positionX - 1] == '.') {
				positionX--;
			}
			else if (board[positionY][positionX - 1] == 'O'){
				for (int i = positionX - 2; i > 0; i--) {
					if (board[positionY][i] == '#')break;
					if (board[positionY][i] == '.') {
						board[positionY][positionX - 1] = '.';
						board[positionY][i] = 'O';
						positionX--;
						break;
					}
				}
			}
		}
		else if (direction == '>') {
			if (board[positionY][positionX + 1] == '.') {
				positionX++;
			}
			else if (board[positionY][positionX + 1] == 'O') {
				for (int i = positionX + 2; i < board[positionY].length(); i++) {
					if (board[positionY][i] == '#')break;
					if (board[positionY][i] == '.') {
						board[positionY][positionX + 1] = '.';
						board[positionY][i] = 'O';
						positionX++;
						break;
					}
				}
			}
		}
		else if (direction == '^') {
			if (board[positionY - 1][positionX] == '.') {
				positionY--;
			}
			else if (board[positionY - 1][positionX] == 'O') {
				for (int i = positionY - 2; i > 0; i--) {
					if (board[i][positionX] == '#')break;
					if (board[i][positionX] == '.') {
						board[positionY - 1][positionX] = '.';
						board[i][positionX] = 'O';
						positionY--;
						break;
					}
				}
			}
		}
		else { // if (direction == 'v') {
			if (board[positionY + 1][positionX] == '.') {
				positionY++;
			}
			else if (board[positionY + 1][positionX] == 'O') {
				for (int i = positionY + 2; i < board.size(); i++) {
					if (board[i][positionX] == '#')break;
					if (board[i][positionX] == '.') {
						board[positionY + 1][positionX] = '.';
						board[i][positionX] = 'O';
						positionY++;
						break;
					}
				}
			}
		}
	}

	void SimulateMovement2(std::vector<std::string>& board, int& positionX, int& positionY, char direction) {
		if (direction == '<') {
			if (board[positionY][positionX - 1] == '.') {
				positionX--;
			}
			else if (board[positionY][positionX - 1] == '#') {
				return;
			}
			else {
				for (int i = positionX - 3; i > 0; i-=2) {
					if (board[positionY][i] == '#')break;
					if (board[positionY][i] == '.') {
						for (int j = i; j < positionX; j++) {
							board[positionY][j] = board[positionY][j + 1];
						}
						positionX--;
						break;
					}
				}
			}
		}
		else if (direction == '>') {
			if (board[positionY][positionX + 1] == '.') {
				positionX++;
			}
			else if (board[positionY][positionX + 1] == '#') {
				return;
			}
			else {
				for (int i = positionX + 3; i < board[positionY].length(); i+=2) {
					if (board[positionY][i] == '#')break;
					if (board[positionY][i] == '.') {
						for (int j = i; j > positionX; j--) {
							board[positionY][j] = board[positionY][j - 1];
						}
						positionX++;
						break;
					}
				}
			}
		}
		else if (direction == '^') {
			if (board[positionY - 1][positionX] == '.') {
				positionY--;
			}
			else if (board[positionY - 1][positionX] == '#') {
				return;
			}
			else {
				std::unordered_set<int> toPush;
				std::unordered_set<int> toCheckNow;
				if (board[positionY - 1][positionX] == '[') {
					toPush.insert((positionY - 1) * 100 + positionX);
					toCheckNow.insert((positionY - 1) * 100 + positionX);
				}
				else {
					toPush.insert((positionY - 1) * 100 + positionX - 1);
					toCheckNow.insert((positionY - 1) * 100 + positionX - 1);
				}
				while (!toCheckNow.empty()) {
					std::unordered_set<int> toCheckLater;
					for (auto& box : toCheckNow) {
						int y = box / 100;
						int x = box % 100;
						if (board[y - 1][x] == '#')return;
						else if (board[y - 1][x] == '[') {
							toPush.insert((y - 1) * 100 + x);
							toCheckLater.insert((y - 1) * 100 + x);
							continue;
						}
						else if (board[y - 1][x] == ']') {
							toPush.insert((y - 1) * 100 + x - 1);
							toCheckLater.insert((y - 1) * 100 + x - 1);
						}
						if (board[y - 1][x+1] == '#')return;
						else if (board[y - 1][x + 1] == '[') {
							toPush.insert((y - 1) * 100 + x + 1);
							toCheckLater.insert((y - 1) * 100 + x + 1);
						}
					}
					toCheckNow = toCheckLater;
				}
				// push all "toPush" boxes starting with the last element
				for (auto& box : toPush) {
					int y = box / 100;
					int x = box % 100;
					board[y][x] = '.';
					board[y][x + 1] = '.';
				}
				for (auto& box : toPush) {
					int y = box / 100;
					int x = box % 100;
					board[y - 1][x] = '[';
					board[y - 1][x + 1] = ']';
				}
				positionY--;
			}
		}
		else { // if (direction == 'v') {
			if (board[positionY + 1][positionX] == '.') {
				positionY++;
			}
			else if (board[positionY + 1][positionX] == '#') {
				return;
			}
			else {
				std::unordered_set<int> toPush;
				std::unordered_set<int> toCheckNow;
				if (board[positionY + 1][positionX] == '[') {
					toPush.insert((positionY + 1) * 100 + positionX);
					toCheckNow.insert((positionY + 1) * 100 + positionX);
				}
				else {
					toPush.insert((positionY + 1) * 100 + positionX - 1);
					toCheckNow.insert((positionY + 1) * 100 + positionX - 1);
				}
				while (!toCheckNow.empty()) {
					std::unordered_set<int> toCheckLater;
					for (auto& box : toCheckNow) {
						int y = box / 100;
						int x = box % 100;
						if (board[y + 1][x] == '#')return;
						else if (board[y + 1][x] == '[') {
							toPush.insert((y + 1) * 100 + x);
							toCheckLater.insert((y + 1) * 100 + x);
							continue;
						}
						else if (board[y + 1][x] == ']') {
							toPush.insert((y + 1) * 100 + x - 1);
							toCheckLater.insert((y + 1) * 100 + x - 1);
						}
						if (board[y + 1][x + 1] == '#')return;
						else if (board[y + 1][x + 1] == '[') {
							toPush.insert((y + 1) * 100 + x + 1);
							toCheckLater.insert((y + 1) * 100 + x + 1);
						}
					}
					toCheckNow = toCheckLater;
				}
				// push all "toPush" boxes starting with the last element
				for (auto& box : toPush) {
					int y = box / 100;
					int x = box % 100;
					board[y][x] = '.';
					board[y][x + 1] = '.';
				}
				for (auto& box : toPush) {
					int y = box / 100;
					int x = box % 100;
					board[y + 1][x] = '[';
					board[y + 1][x + 1] = ']';
				}
				positionY++;
			}
		}
	}


}

void Solve2024_15() {

	int positionX, positionY;
	int positionX2, positionY2;
	std::vector<std::string> board;

	// read input
	std::fstream file("Input/Input_15.txt");
	std::string buffor;
	while (!file.eof()) {
		std::getline(file, buffor);
		if (buffor == "")break;
		board.push_back(buffor);
	}

	// find @
	for (int i = 0; i < board.size(); i++) {
		int index = board[i].find('@');
		if (index != -1) {
			positionX = index;
			positionY = i;
			positionX2 = index * 2;
			positionY2 = i;

			board[i][index] = '.';
			break;
		}
	}

	// prepare board for part 2
	std::vector<std::string> board2;
	for (int i = 0; i < board.size(); i++) {
		buffor = "";
		for (int j = 0; j < board[i].length(); j++) {
			if(board[i][j] == '#') buffor += "##";
			else if(board[i][j] == '.') buffor += "..";
			else if(board[i][j] == 'O') buffor += "[]";
		}
		board2.push_back(buffor);
	}

	// simulate movement
	while (file >> buffor) {
		for (int i = 0; i < buffor.length(); i++) {
			Advent2024_15::SimulateMovement(board, positionX, positionY, buffor[i]);
			Advent2024_15::SimulateMovement2(board2, positionX2, positionY2, buffor[i]);
		}
	}
	file.close();

	// calculate answer
	int answer = 0;
	int answer2 = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].length(); j++) {
			if (board[i][j] == 'O') {
				answer += 100 * i + j;
			}
		}
	}
	for (int i = 0; i < board2.size(); i++) {
		for (int j = 0; j < board2[i].length(); j++) {
			if (board2[i][j] == '[') {
				answer2 += 100 * i + j;
				j++;
			}
		}
	}

	std::cout << "Advent2024_15_1: " << answer << "\n";
	std::cout << "Advent2024_15_2: " << answer2 << "\n";

}

