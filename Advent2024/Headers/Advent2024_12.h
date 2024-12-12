#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_12 {
	struct sortByX {
		inline bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) {
			if (a.first == b.first) return a.second < b.second;
			else return a.first < b.first;
		}
	};
	struct sortByY {
		inline bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) {
			if (a.second == b.second) return a.first < b.first;
			else return a.second < b.second;
		}
	};

	int CalculatePrice(std::vector<std::string>& board, std::vector < std::pair<int, int>>& area, std::vector<std::pair<int, int>>& outsides) {
		char sign = board[area[0].first][area[0].second];
		int fences = 0;
		for (int i = 0; i < area.size(); i++) {
			int x = area[i].first;
			int y = area[i].second;
			int startFences = fences;
			if (x > 0) {
				if (board[x - 1][y] != sign) {
					fences++;
				}
			}
			else fences++;
			if (x < board.size() - 1) {
				if (board[x + 1][y] != sign) {
					fences++;
				}
			}
			else fences++;
			if (y > 0) {
				if (board[x][y - 1] != sign) {
					fences++;
				}
			}
			else fences++;
			if (y < board[0].length() - 1) {
				if (board[x][y + 1] != sign) {
					fences++;
				}
			}
			else fences++;

			if (fences != startFences) {
				outsides.emplace_back(x, y);
			}
		}
		return fences * area.size();
	}

	int CalculatePrice2(std::vector<std::string>& board, std::vector<std::pair<int, int>>& outsides, int size) {
		char sign = board[outsides[0].first][outsides[0].second];
		int sides = 0;
		// sort outsides by X
		std::sort(outsides.begin(), outsides.end(), sortByX());
		// calculate top sides
		bool startedSide = false;
		for (int i = 0; i < outsides.size(); i++) {
			if (!startedSide) {
				if (outsides[i].first != 0) {
					if (board[outsides[i].first - 1][outsides[i].second] == sign) continue;
				}
				startedSide = true;
			}
			else {
				if (outsides[i-1].first == outsides[i].first && outsides[i-1].second + 1 == outsides[i].second) {
					if (outsides[i].first != 0) {
						if (board[outsides[i].first - 1][outsides[i].second] != sign) continue;
					}
					else {
						continue;
					}
				}
				startedSide = false;
				sides++;
				i--;
			}
		}
		if (startedSide) {
			sides++;
			startedSide = false;
		}
		// calculate bottom sides
		for (int i = 0; i < outsides.size(); i++) {
			if (!startedSide) {
				if (outsides[i].first != board.size() - 1) {
					if (board[outsides[i].first + 1][outsides[i].second] == sign) continue;
				}
				startedSide = true;
			}
			else {
				if (outsides[i - 1].first == outsides[i].first && outsides[i - 1].second + 1 == outsides[i].second) {
					if (outsides[i].first != board.size() - 1) {
						if (board[outsides[i].first + 1][outsides[i].second] != sign) continue;
					}
					else {
						continue;
					}
				}
				startedSide = false;
				sides++;
				i--;
			}
		}
		if (startedSide) {
			sides++;
			startedSide = false;
		}
		// sort outsides by Y
		std::sort(outsides.begin(), outsides.end(), sortByY());
		// calculate left sides
		for (int i = 0; i < outsides.size(); i++) {
			if (!startedSide) {
				if (outsides[i].second != 0) {
					if (board[outsides[i].first][outsides[i].second - 1] == sign) continue;
				}
				startedSide = true;
			}
			else {
				if (outsides[i - 1].first + 1 == outsides[i].first && outsides[i - 1].second == outsides[i].second) {
					if (outsides[i].second != 0) {
						if (board[outsides[i].first][outsides[i].second - 1] != sign) continue;
					}
					else {
						continue;
					}
				}
				startedSide = false;
				sides++;
				i--;
			}
		}
		if (startedSide) {
			sides++;
			startedSide = false;
		}
		// calculate right sides
		for (int i = 0; i < outsides.size(); i++) {
			if (!startedSide) {
				if (outsides[i].second != board[0].length() - 1) {
					if (board[outsides[i].first][outsides[i].second + 1] == sign) continue;
				}
				startedSide = true;
			}
			else {
				if (outsides[i - 1].first + 1 == outsides[i].first && outsides[i - 1].second == outsides[i].second) {
					if (outsides[i].second != board[0].length() - 1) {
						if (board[outsides[i].first][outsides[i].second + 1] != sign) continue;
					}
					else {
						continue;
					}
				}
				startedSide = false;
				sides++;
				i--;
			}
		}
		if (startedSide) sides++;

		return sides * size;
	}
}

void Solve2024_12() {

	std::vector<std::string> board;
	std::fstream file("Input/Input_12.txt");
	std::string buffor;
	while (file >> buffor) {
		board.push_back(buffor);
	}
	file.close();

	std::vector<std::vector<std::pair<int, int>>> areas;
	std::unordered_set<int> visited;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (visited.contains(i * 10000 + j)) continue;


			std::unordered_set<int>* toCheck = new std::unordered_set<int>;
			toCheck->insert(i * 10000 + j);
			char sign = board[i][j];
			visited.insert(i * 10000 + j);
			std::vector<std::pair<int, int>> area;
			area.emplace_back(i, j);
			while (toCheck->size() != 0) {
				std::unordered_set<int>* tmp = new std::unordered_set<int>;
				for (const auto& place : *toCheck) {
					int x = place / 10000;
					int y = place % 10000;

					if (x > 0) {
						if (!visited.contains((x - 1) * 10000 + y)) {
							if (board[x - 1][y] == sign) {
								tmp->insert((x - 1) * 10000 + y);
								visited.insert((x - 1) * 10000 + y);
								area.emplace_back(x - 1, y);
							}
						}
					}
					if (x < board.size() - 1) {
						if (!visited.contains((x + 1) * 10000 + y)) {
							if (board[x + 1][y] == sign) {
								tmp->insert((x + 1) * 10000 + y);
								visited.insert((x + 1) * 10000 + y);
								area.emplace_back(x + 1, y);
							}
						}
					}
					if (y > 0) {
						if (!visited.contains(x * 10000 + y - 1)) {
							if (board[x][y - 1] == sign) {
								tmp->insert(x * 10000 + y - 1);
								visited.insert(x * 10000 + y - 1);
								area.emplace_back(x, y - 1);
							}
						}
					}
					if (y < board[0].length() - 1) {
						if (!visited.contains(x * 10000 + y + 1)) {
							if (board[x][y + 1] == sign) {
								tmp->insert(x * 10000 + y + 1);
								visited.insert(x * 10000 + y + 1);
								area.emplace_back(x, y + 1);
							}
						}
					}
				}
				delete toCheck;
				toCheck = tmp;
			}
			areas.push_back(area);
			delete toCheck;
		}
	}

	int answer = 0;
	int answer2 = 0;
	for (int i = 0; i < areas.size(); i++) {
		std::vector<std::pair<int, int>> outsides;
		answer += Advent2024_12::CalculatePrice(board, areas[i], outsides);
		answer2 += Advent2024_12::CalculatePrice2(board, outsides, areas[i].size());
	}
	std::cout << "Advent2024_12_1: " << answer << "\n";
	std::cout << "Advent2024_12_2: " << answer2 << "\n";

}

