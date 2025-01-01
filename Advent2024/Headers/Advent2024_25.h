#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_25 {

}

void Solve2024_25() {

	// locks ###
	// keys  ...
	std::vector<std::vector<int>> locks;
	std::vector<std::vector<int>> keys;

	std::string buffor;
	std::fstream file("Input/Input_25.txt");
	while (!file.eof()) {
		std::getline(file, buffor);
		if (buffor[0] == '#') {
			std::vector<int> tab{ 10,10,10,10,10 };
			for (int i = 0; i < 6; i++) {
				std::getline(file, buffor);
				for (int j = 0; j < 5; j++) {
					if (buffor[j] == '.')tab[j] = std::min(tab[j], i);
				}
			}
			locks.push_back(tab);
		}
		else {
			std::vector<int> tab { -1,-1,-1,-1,-1 };
			for (int i = 5; i >=0; i--) {
				std::getline(file, buffor);
				for (int j = 0; j < 5; j++) {
					if (buffor[j] == '#')tab[j] = std::max(tab[j], i);
				}
			}
			keys.push_back(tab);
		}
		std::getline(file, buffor);
	}
	file.close();

	int answer = 0;

	for (auto& lock : locks) {
		for (auto& key : keys) {
			if (lock[0] + key[0] <= 5 &&
				lock[1] + key[1] <= 5 &&
				lock[2] + key[2] <= 5 &&
				lock[3] + key[3] <= 5 &&
				lock[4] + key[4] <= 5) answer ++ ;
		}
	}

	std::cout << "Advent2024_25_1: " << answer << "\n";
	std::cout << "Advent2024_25_2:";
}

