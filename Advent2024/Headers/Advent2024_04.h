#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2024_04 {

}

void Solve2024_04() {

	std::fstream file("Input/Input_04.txt");
	std::vector<std::string> ceres;
	std::string buffor;
	while (file >> buffor) {
		ceres.push_back(buffor);
	}
	file.close();
	int x = ceres[0].length();
	int y = ceres.size();
	int xmasCount = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x - 3; j++) {
			// ->
			if (ceres[i][j]		== 'X' &&
				ceres[i][j + 1] == 'M' &&
				ceres[i][j + 2] == 'A' &&
				ceres[i][j + 3] == 'S')
				xmasCount++;
			// <-
			if (ceres[i][j]		== 'S' &&
				ceres[i][j + 1] == 'A' &&
				ceres[i][j + 2] == 'M' &&
				ceres[i][j + 3] == 'X')
				xmasCount++;
		}
	}
	for (int j = 0; j < x ; j++) {
		for (int i = 0; i < y - 3; i++) {
			// \/
			if (ceres[i][j]		== 'X' &&
				ceres[i + 1][j] == 'M' &&
				ceres[i + 2][j] == 'A' &&
				ceres[i + 3][j] == 'S')
				xmasCount++;
			// /\ //
			if (ceres[i][j]		== 'S' &&
				ceres[i + 1][j] == 'A' &&
				ceres[i + 2][j] == 'M' &&
				ceres[i + 3][j] == 'X')
				xmasCount++;
		}
	}
	for (int i = 0; i < y - 3; i++) {
		for (int j = 0; j < x - 3; j++) {
			// _\|
			if (ceres[i][j]			== 'X' &&
				ceres[i + 1][j + 1] == 'M' &&
				ceres[i + 2][j + 2] == 'A' &&
				ceres[i + 3][j + 3] == 'S')
				xmasCount++;
			// |\ //
			if (ceres[i][j]			== 'S' &&
				ceres[i + 1][j + 1] == 'A' &&
				ceres[i + 2][j + 2] == 'M' &&
				ceres[i + 3][j + 3] == 'X')
				xmasCount++;
		}
	}
	for (int i = 0; i < y - 3; i++) {
		for (int j = 0; j < x - 3; j++) {
			// _\|
			if (ceres[i][j + 3]		== 'X' &&
				ceres[i + 1][j + 2] == 'M' &&
				ceres[i + 2][j + 1] == 'A' &&
				ceres[i + 3][j]		== 'S')
				xmasCount++;
			// |\ //
			if (ceres[i][j + 3]		== 'S' &&
				ceres[i + 1][j + 2] == 'A' &&
				ceres[i + 2][j + 1] == 'M' &&
				ceres[i + 3][j]		== 'X')
				xmasCount++;
		}
	}
	std::cout << "Advent2024_04_1: " << xmasCount << "\n";
	//---part 2---
	xmasCount = 0;

	for (int i = 1; i < y - 1; i++) {
		for (int j = 1; j < x - 1; j++) {
			if (ceres[i][j] != 'A')continue;
			if (((ceres[i - 1][j - 1] == 'M' && ceres[i + 1][j + 1] == 'S') ||
				(ceres[i - 1][j - 1] == 'S' && ceres[i + 1][j + 1] == 'M')) &&
				((ceres[i + 1][j - 1] == 'M' && ceres[i - 1][j + 1] == 'S') ||
					(ceres[i + 1][j - 1] == 'S' && ceres[i - 1][j + 1] == 'M')))
				xmasCount++;
		}
	}

	std::cout << "Advent2024_04_2: " << xmasCount << "\n";
}

