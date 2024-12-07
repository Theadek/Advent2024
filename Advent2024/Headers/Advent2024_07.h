#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_07 {
	bool CheckCalibration(std::vector<long long>& numbers, long long& sum, long long calculation, int index) {
		if (index == numbers.size()) {
			if (sum == calculation)return true;
			else return false;
		}
		if (CheckCalibration(numbers, sum, calculation + numbers[index], index + 1)) return true;
		if (CheckCalibration(numbers, sum, calculation * numbers[index], index + 1)) return true;
		return false;
	}

	bool CheckCalibrationAdvanced(std::vector<long long>& numbers, long long& sum, long long calculation, int index) {
		if (index == numbers.size()) {
			if (sum == calculation)return true;
			else return false;
		}
		if (CheckCalibrationAdvanced(numbers, sum, calculation + numbers[index], index + 1)) return true;
		if (CheckCalibrationAdvanced(numbers, sum, calculation * numbers[index], index + 1)) return true;
		std::string concatenation = std::to_string(calculation) + std::to_string(numbers[index]);
		if (CheckCalibrationAdvanced(numbers, sum, std::stoll(concatenation), index + 1)) return true;
		return false;
	}
}

void Solve2024_07() {

	std::fstream file("Input/Input_07.txt");
	std::string buffor;
	long long answer = 0;
	long long answer2 = 0;
	while (!file.eof()) {
		std::getline(file, buffor);
		int index = buffor.find(':');
		long long sum = std::stoll(buffor.substr(0, index));
		buffor = buffor.substr(index + 2, buffor.length() - index - 2);
		index = buffor.find(' ');
		std::vector<long long> numbers;
		while (index != -1) {
			numbers.push_back(std::stoll(buffor.substr(0, index)));
			buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			index = buffor.find(' ');
		}
		numbers.push_back(std::stoll(buffor));
		if (Advent2024_07::CheckCalibration(numbers, sum, numbers[0], 1)) answer += sum;
		if (Advent2024_07::CheckCalibrationAdvanced(numbers, sum, numbers[0], 1)) answer2 += sum;
	}
	file.close();

	std::cout << "Advent2024_07_1: " << answer << "\n";

	std::cout << "Advent2024_07_2: " << answer2 << "\n";
}

