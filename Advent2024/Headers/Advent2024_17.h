#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_17 {

}

void Solve2024_17() {



	long long A, B, C;
	std::string buffor;
	std::vector<int> ins;
	std::fstream file("Input/Input_17.txt");
	file >> buffor >> buffor >> buffor;
	A = std::stoll(buffor);
	file >> buffor >> buffor >> buffor;
	B = std::stoll(buffor);
	file >> buffor >> buffor >> buffor;
	C = std::stoll(buffor);
	file >> buffor >> buffor;
	for (int i = 0; i < buffor.length(); i += 2) {
		int op = std::stoi(buffor.substr(i, 1));
		ins.push_back(op);
	}

	file.close();
	std::vector<int> output;
	int insPointer = 0;
	long long combo;

	//DEBUG print instructions
	/*for (int i = 0; i < ins.size(); i += 2) {
		switch (ins[i]) {
		case 0:
			std::cout << "A = A >> combo\n";
			break;
		case 1:
			std::cout << "B = B XOR literal\n";
			break;
		case 2:
			std::cout << "B = combo % 8\n";
			break;
		case 3:
			std::cout << "Jump if A != 0\n";
			break;
		case 4:
			std::cout << "B = B XOR C\n";
			break;
		case 5:
			std::cout << "output combo % 8\n";
			break;
		case 6:
			std::cout << "B = A >> combo\n";
			break;
		case 7:
			std::cout << "C = A >> combo\n";
			break;
		}
	}*/


	while (insPointer < ins.size()) {
		switch (ins[insPointer]) {
		case 0:
			combo = ins[insPointer + 1];
			if (combo == 4)combo = A;
			else if (combo == 5)combo = B;
			else if (combo == 6)combo = C;
			A = A >> combo;
			insPointer += 2;
			break;
		case 1:
			B = B ^ ins[insPointer + 1];
			insPointer += 2;
			break;
		case 2:
			combo = ins[insPointer + 1];
			if (combo == 4)combo = A;
			else if (combo == 5)combo = B;
			else if (combo == 6)combo = C;
			B = combo % 8;
			insPointer += 2;
			break;
		case 3:
			if (A == 0) {
				insPointer += 2; break;
			}
			else {
				insPointer = ins[insPointer + 1]; break;
			}
		case 4:
			B = B ^ C;
			insPointer += 2;
			break;
		case 5:
			combo = ins[insPointer + 1];
			if (combo == 4)combo = A;
			else if (combo == 5)combo = B;
			else if (combo == 6)combo = C;
			output.push_back(combo%8);
			insPointer += 2;
			break;
		case 6:
			combo = ins[insPointer + 1];
			if (combo == 4)combo = A;
			else if (combo == 5)combo = B;
			else if (combo == 6)combo = C;
			B = A >> combo;
			insPointer += 2;
			break;
		case 7:
			combo = ins[insPointer + 1];
			if (combo == 4)combo = A;
			else if (combo == 5)combo = B;
			else if (combo == 6)combo = C;
			C = A >> combo;
			insPointer += 2;
			break;
		}
	}

	std::cout << "Advent2024_17_1: ";
	std::cout << output[0];
	for (int i = 1; i < output.size(); i++) {
		std::cout << "," << output[i];
	}
	std::cout << "\n";

	//--part 2--
	std::vector<long long> candidates{ 0 };
	for (int i = ins.size()-1; i >= 0; i--) {
		std::vector<long long> nextCandidates;
		for (auto& candidate : candidates) {
			for (int x = 0; x < 8; x++) {
				insPointer = 0;
				A = candidate + x;
				B = 0;
				C = 0;
				while (insPointer < ins.size()) {
					switch (ins[insPointer]) {
					case 0:
						combo = ins[insPointer + 1];
						if (combo == 4)combo = A;
						else if (combo == 5)combo = B;
						else if (combo == 6)combo = C;
						A = A >> combo;
						insPointer += 2;
						break;
					case 1:
						B = B ^ ins[insPointer + 1];
						insPointer += 2;
						break;
					case 2:
						combo = ins[insPointer + 1];
						if (combo == 4)combo = A;
						else if (combo == 5)combo = B;
						else if (combo == 6)combo = C;
						B = combo % 8;
						insPointer += 2;
						break;
					case 3:
						insPointer += 100;
						break;
					case 4:
						B = B ^ C;
						insPointer += 2;
						break;
					case 5:
						combo = ins[insPointer + 1];
						if (combo == 4)combo = A;
						else if (combo == 5)combo = B;
						else if (combo == 6)combo = C;
						if (combo % 8 == ins[i]) {
							nextCandidates.push_back((long long)(candidate + x) * 8);
						}
						insPointer = 100;
						break;
					case 6:
						combo = ins[insPointer + 1];
						if (combo == 4)combo = A;
						else if (combo == 5)combo = B;
						else if (combo == 6)combo = C;
						B = A >> combo;
						insPointer += 2;
						break;
					case 7:
						combo = ins[insPointer + 1];
						if (combo == 4)combo = A;
						else if (combo == 5)combo = B;
						else if (combo == 6)combo = C;
						C = A >> combo;
						insPointer += 2;
						break;
					}
				}
			}
		}
		candidates = nextCandidates;
	}

	std::cout << "Advent2024_17_2: " << candidates[0]/8 << "\n";
}

