#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<limits.h>

namespace Advent2024_16 {
	struct Node {
		INT32 n, e, s, w;
		Node(INT32 nn, INT32 ee, INT32 ss, INT32 ww) {
			n = nn;
			e = ee;
			s = ss;
			w = ww;
		}
	};
}

void Solve2024_16() {
	std::vector<std::string> board;
	std::fstream file("Input/Input_16.txt");
	std::string buffor;
	while (file >> buffor) board.push_back(buffor);
	file.close();

	std::vector<std::vector<Advent2024_16::Node>> values;
	std::vector<Advent2024_16::Node> value;
	Advent2024_16::Node node(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX);
	for (int i = 0; i < board[0].length(); i++) {
		value.emplace_back(node);
	}
	for (int i = 0; i < board.size(); i++) {
		values.push_back(value);
	}

	std::pair<int, int> exit;
	std::unordered_set<int> toCheck;
	for (int i = 0; i < board.size(); i++) {
		int index = board[i].find('S');
		if (index != -1) {
			toCheck.insert(i * 1000 + index);
			values[i][index] = Advent2024_16::Node(1000,0,1000,2000);
		}
		index = board[i].find('E');
		if (index != -1) exit = { i,index };
	}

	while (!toCheck.empty()) {
		std::unordered_set<int> toCheckNext;
		for (auto& area : toCheck) {
			int y = area / 1000;
			int x = area % 1000;
			// move east
			if (board[y][x + 1] != '#') {
				if (values[y][x].e + 1 < values[y][x + 1].e) {
					values[y][x + 1].e = values[y][x].e + 1;
					if (exit.first != y || exit.second != x + 1) {
						values[y][x + 1].n = std::min(values[y][x + 1].n, values[y][x + 1].e + 1000);
						values[y][x + 1].s = std::min(values[y][x + 1].s, values[y][x + 1].e + 1000);
						values[y][x + 1].w = std::min(values[y][x + 1].w, values[y][x + 1].e + 2000);
						toCheckNext.insert(y * 1000 + x + 1);
					}
				}
			}
			// move west
			if (board[y][x - 1] != '#') {
				if (values[y][x].w + 1 < values[y][x - 1].w) {
					values[y][x - 1].w = values[y][x].w + 1;
					if (exit.first != y || exit.second != x - 1) {
						values[y][x - 1].n = std::min(values[y][x - 1].n, values[y][x - 1].w + 1000);
						values[y][x - 1].s = std::min(values[y][x - 1].s, values[y][x - 1].w + 1000);
						values[y][x - 1].e = std::min(values[y][x - 1].e, values[y][x - 1].w + 2000);
						toCheckNext.insert(y * 1000 + x - 1);
					}
				}
			}
			// move south
			if (board[y + 1][x] != '#') {
				if (values[y][x].s + 1 < values[y + 1][x].s) {
					values[y + 1][x].s = values[y][x].s + 1;
					if (exit.first != y + 1 || exit.second != x) {
						values[y + 1][x].n = std::min(values[y + 1][x].n, values[y + 1][x].s + 2000);
						values[y + 1][x].e = std::min(values[y + 1][x].e, values[y + 1][x].s + 1000);
						values[y + 1][x].w = std::min(values[y + 1][x].w, values[y + 1][x].s + 1000);
						toCheckNext.insert((y + 1) * 1000 + x);
					}
				}
			}
			// move north
			if (board[y - 1][x] != '#') {
				if (values[y][x].n + 1 < values[y - 1][x].n) {
					values[y - 1][x].n = values[y][x].n + 1;
					if (exit.first != y - 1 || exit.second != x) {
						values[y - 1][x].s = std::min(values[y - 1][x].s, values[y - 1][x].n + 2000);
						values[y - 1][x].e = std::min(values[y - 1][x].e, values[y - 1][x].n + 1000);
						values[y - 1][x].w = std::min(values[y - 1][x].w, values[y - 1][x].n + 1000);
						toCheckNext.insert((y - 1) * 1000 + x);
					}
				}
			}

		}
		toCheck = toCheckNext;
	}

	INT32 answer = INT32_MAX;
	answer = std::min(answer, values[exit.first][exit.second].e);
	answer = std::min(answer, values[exit.first][exit.second].n);
	answer = std::min(answer, values[exit.first][exit.second].s);
	answer = std::min(answer, values[exit.first][exit.second].w);
	std::cout << "Advent2024_16_1: " << answer << "\n";


	//---part 2---

	// direction
	// > 0
	// v 1
	// < 2
	// ^ 3

	std::unordered_map<int, int> toCheckDirections;
	toCheck.clear();
	std::unordered_set<int> visited;
	visited.insert(exit.first * 1000 + exit.second);
	Advent2024_16::Node tmpNode = values[exit.first][exit.second];
	int pathValue = std::min(std::min(tmpNode.e, tmpNode.w), std::min(tmpNode.n, tmpNode.s));
	if (tmpNode.e == pathValue)
	{
		toCheck.insert(exit.first * 1000 + exit.second - 1);
		visited.insert(exit.first * 1000 + exit.second - 1);
		toCheckDirections.emplace(exit.first * 1000 + exit.second - 1, 0);
	}
	if (tmpNode.w == pathValue) {
		toCheck.insert(exit.first * 1000 + exit.second + 1);
		visited.insert(exit.first * 1000 + exit.second + 1);
		toCheckDirections.emplace(exit.first * 1000 + exit.second + 1, 2);
	}
	if (tmpNode.n == pathValue) {
		toCheck.insert(exit.first * 1000 + exit.second + 1000);
		visited.insert(exit.first * 1000 + exit.second + 1000);
		toCheckDirections.emplace(exit.first * 1000 + exit.second + 1000, 3);
	}
	if (tmpNode.s == pathValue) {
		toCheck.insert(exit.first * 1000 + exit.second - 1000);
		visited.insert(exit.first * 1000 + exit.second - 1000);
		toCheckDirections.emplace(exit.first * 1000 + exit.second - 1000, 1);
	}

	while (!toCheck.empty()) {
		std::unordered_set<int> toCheckNext;
		for (auto& area : toCheck) {
			int y = area / 1000;
			int x = area % 1000;
			pathValue = std::min(std::min(values[y][x].e, values[y][x].w), std::min(values[y][x].n, values[y][x].s));
			if (board[y][x] == 'S')break;
			int direction = toCheckDirections[area];

			if (pathValue == values[y][x].e) {
				if (direction == 3 && pathValue + 1000 <= values[y][x].n || direction == 1 && pathValue + 1000 <= values[y][x].s || direction == 0) {
					visited.insert(y * 1000 + x - 1);
					toCheckNext.insert(y * 1000 + x - 1);
					toCheckDirections.emplace(y * 1000 + x - 1, 0);
				}
				if (direction == 0) continue;
				else {
					if (direction == 3 && board[y+1][x] != '#' && values[y + 1][x].n + 1 == values[y][x].n) { // north
						visited.insert((y + 1) * 1000 + x);
						toCheckNext.insert((y + 1) * 1000 + x);
						toCheckDirections.emplace((y + 1) * 1000 + x, 3);
					}
					else if (direction == 1 && board[y - 1][x] != '#' && values[y - 1][x].s + 1 == values[y][x].s) { // south
						visited.insert((y - 1) * 1000 + x);
						toCheckNext.insert((y - 1) * 1000 + x);
						toCheckDirections.emplace((y - 1) * 1000 + x, 1);
					}
				}
			}
			else if (pathValue == values[y][x].s) {
				if (direction == 0 && pathValue + 1000 <= values[y][x].e || direction == 2 && pathValue + 1000 <= values[y][x].w || direction == 1) {
					visited.insert((y - 1) * 1000 + x);
					toCheckNext.insert((y - 1) * 1000 + x);
					toCheckDirections.emplace((y - 1) * 1000 + x, 1);
				}
				if (direction == 1) continue;
				else {
					if (direction == 0 && board[y][x - 1] != '#' && values[y][x - 1].e + 1 == values[y][x].e) { // east
						visited.insert(y * 1000 + x - 1);
						toCheckNext.insert(y * 1000 + x - 1);
						toCheckDirections.emplace(y * 1000 + x - 1, 0);
					}
					else if (direction == 2 && board[y][x + 1] != '#' && values[y][x + 1].w + 1 == values[y][x].w) { // west
						visited.insert(y * 1000 + x + 1);
						toCheckNext.insert(y * 1000 + x + 1);
						toCheckDirections.emplace(y * 1000 + x + 1, 2);
					}
				}
			}
			else if (pathValue == values[y][x].w) {
				if (direction == 3 && pathValue + 1000 <= values[y][x].n || direction == 1 && pathValue + 1000 <= values[y][x].s || direction == 2) {
					visited.insert(y * 1000 + x + 1);
					toCheckNext.insert(y * 1000 + x + 1);
					toCheckDirections.emplace(y * 1000 + x + 1, 2);
				}
				if (direction == 2) continue;
				else {
					if (direction == 3 && board[y + 1][x] != '#' && values[y + 1][x].n + 1 == values[y][x].n) { // north
						visited.insert((y + 1) * 1000 + x);
						toCheckNext.insert((y + 1) * 1000 + x);
						toCheckDirections.emplace((y + 1) * 1000 + x, 3);
					}
					else if (direction == 1 && board[y - 1][x] != '#' && values[y - 1][x].s + 1 == values[y][x].s) { // south
						visited.insert((y - 1) * 1000 + x);
						toCheckNext.insert((y - 1) * 1000 + x);
						toCheckDirections.emplace((y - 1) * 1000 + x, 1);
					}
				}
			}
			else if (pathValue == values[y][x].n) {
				if (direction == 0 && pathValue + 1000 <= values[y][x].e || direction == 2 && pathValue + 1000 <= values[y][x].w || direction == 3) {
					visited.insert((y + 1) * 1000 + x);
					toCheckNext.insert((y + 1) * 1000 + x);
					toCheckDirections.emplace((y + 1) * 1000 + x, 3);
				}
				if (direction == 3) continue;
				else {
					if (direction == 0 && board[y][x - 1] != '#' && values[y][x - 1].e + 1 == values[y][x].e) { // east
						visited.insert(y * 1000 + x - 1);
						toCheckNext.insert(y * 1000 + x - 1);
						toCheckDirections.emplace(y * 1000 + x - 1, 0);
					}
					else if (direction == 2 && board[y][x + 1] != '#' && values[y][x + 1].w + 1 == values[y][x].w) { // west
						visited.insert(y * 1000 + x + 1);
						toCheckNext.insert(y * 1000 + x + 1);
						toCheckDirections.emplace(y * 1000 + x + 1, 2);
					}
				}
			}

		}
		toCheck = toCheckNext;
	}
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].length(); j++) {
			if (visited.contains(i * 1000 + j))std::cout << "O";
			else std::cout << board[i][j];
		}
		std::cout << "\n";
	}

	std::cout << "Advent2024_16_2: " << visited.size() << "\n";
}

