#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_03 {

}

void Solve2024_03() {
	int sum = 0;
	std::fstream file("Input/Input_03.txt");
	std::string buffor;
	while (!file.eof()) {
		int index = 0;
		std::getline(file, buffor);
		while (buffor.length() > 0) {
			//find mul(
			index = buffor.find("mul(");
			if (index == -1)break;
			buffor = buffor.substr(index + 4, buffor.length() - index - 4);
			//find ,
			index = buffor.find(',');
			if (index == -1)break;
			std::string number = buffor.substr(0, index);
			//check if first number is valid and save it
			bool valid = true;
			for (int i = 0; i < number.length(); i++) {
				if (number[i] < '0' || number[i] > '9') {
					valid = false;
					break;
				}
			}
			if (!valid)continue;
			int firstNumber = std::stoi(number);
			buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			//find )
			index = buffor.find(')');
			if (index == -1)break;
			number = buffor.substr(0, index);
			//check if second number is valid and save it
			valid = true;
			for (int i = 0; i < number.length(); i++) {
				if (number[i] < '0' || number[i] > '9') {
					valid = false;
					break;
				}
			}
			if (!valid)continue;
			int secondNumber = std::stoi(number);
			buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			sum += firstNumber * secondNumber;
		}
	}
	file.close();

	std::cout << "Advent2024_03_1: " << sum << "\n";

	bool doMul = true;
	sum = 0;
	//---part 2---
	file.open("Input/Input_03.txt");
	while (!file.eof()) {
		int index = 0;
		std::getline(file, buffor);
		while (buffor.length() > 0) {
			int findMul = buffor.find("mul(");
			int findDo = buffor.find("do()");
			int findDont = buffor.find("don't()");
			if (findMul == -1 && findDo == -1 && findDont == -1)break;
			if (findMul == -1) findMul = 999999999;
			if (findDo == -1) findDo = 999999999;
			if (findDont == -1) findDont = 999999999;
			if (findDo < findMul || findDont < findMul) {
				if (findDo < findDont) {
					doMul = true;
					buffor = buffor.substr(findDo + 4, buffor.length() - findDo - 4);
				}
				else {
					doMul = false;
					buffor = buffor.substr(findDont + 7, buffor.length() - findDont - 7);
				}
				continue;
			}
			else if (!doMul) {
				buffor = buffor.substr(findMul + 4, buffor.length() - findMul - 4);
				continue;
			}
			//find mul(
			if (findMul == -1)break;
			buffor = buffor.substr(findMul + 4, buffor.length() - findMul - 4);
			//find ,
			index = buffor.find(',');
			if (index == -1)break;
			std::string number = buffor.substr(0, index);
			//check if first number is valid and save it
			bool valid = true;
			for (int i = 0; i < number.length(); i++) {
				if (number[i] < '0' || number[i] > '9') {
					valid = false;
					break;
				}
			}
			if (!valid)continue;
			int firstNumber = std::stoi(number);
			buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			//find )
			index = buffor.find(')');
			if (index == -1)break;
			number = buffor.substr(0, index);
			//check if second number is valid and save it
			valid = true;
			for (int i = 0; i < number.length(); i++) {
				if (number[i] < '0' || number[i] > '9') {
					valid = false;
					break;
				}
			}
			if (!valid)continue;
			int secondNumber = std::stoi(number);
			buffor = buffor.substr(index + 1, buffor.length() - index - 1);
			sum += firstNumber * secondNumber;
		}
	}
	file.close();

	std::cout << "Advent2024_03_2: " << sum << "\n";
}

