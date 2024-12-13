#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<limits.h>

namespace Advent2024_13 {
	struct Machine {
		long long x1, y1, x2, y2, priceX, priceY;
		Machine(long long xx1, long long yy1, long long xx2, long long yy2, long long priceXX, long long priceYY) {
			x1 = xx1;
			y1 = yy1;
			x2 = xx2;
			y2 = yy2;
			priceX = priceXX;
			priceY = priceYY;
		}
	};
}

void Solve2024_13() {

	std::vector<Advent2024_13::Machine> machines;

	std::fstream file("Input/Input_13.txt");
	std::string buffor;
	while (file >> buffor) {
		file >> buffor >> buffor;
		long long x = std::stoll(buffor.substr(2, buffor.length() - 3));
		file >> buffor;
		long long y = std::stoll(buffor.substr(2, buffor.length() - 2));
		file >> buffor >> buffor >> buffor;
		long long x2 = std::stoll(buffor.substr(2, buffor.length() - 3));
		file >> buffor;
		long long y2 = std::stoll(buffor.substr(2, buffor.length() - 2));
		file >> buffor >> buffor;
		long long priceX = std::stoll(buffor.substr(2, buffor.length() - 3));
		file >> buffor;
		long long priceY = std::stoll(buffor.substr(2, buffor.length() - 2));

		machines.emplace_back(x, y, x2, y2, priceX, priceY);
	}
	file.close();

	long long answer1 = 0;
	for (auto& machine : machines) {
		long long max1 = std::min(machine.priceX / machine.x1, machine.priceY / machine.y1);
		long long max2 = std::min(machine.priceX / machine.x2, machine.priceY / machine.y2);
		int minTokens = 500;
		for (int i = 1; i <= max1; i++) {
			for (int j = 1; j <= max2; j++) {
				if (i * machine.x1 + j * machine.x2 == machine.priceX &&
					i * machine.y1 + j * machine.y2 == machine.priceY) {
					minTokens = std::min(minTokens, i * 3 + j);
					break;
				}
				else if (i * machine.x1 + j * machine.x2 > machine.priceX ||
						 i * machine.y1 + j * machine.y2 > machine.priceY) {
					 break;
				}
			}
		}
		if (minTokens != 500)answer1 += minTokens;
	}
	std::cout << "Advent2024_13_1: " << answer1 << "\n";

	//---part 2---
	for (auto& machine : machines) {
		machine.priceX += 10000000000000;
		machine.priceY += 10000000000000;
	}


	answer1 = 0;
	for (auto& machine : machines) {
		double b = machine.priceY * machine.x1 - machine.priceX * machine.y1;
		double b2 = machine.y2 * machine.x1 - machine.y1 * machine.x2;
		if (b2 == 0)
			continue;
		b /= b2;
		if (b != (double)(long long)b) continue;
		double a = (double)(machine.priceX - machine.x2 * b) / (double)(machine.x1);
		if (a != (double)(long long)a) continue;
		answer1 += 3 * (long long)a + (long long)b;
	}
	std::cout << "Advent2024_13_1: " << answer1 << "\n";

}

