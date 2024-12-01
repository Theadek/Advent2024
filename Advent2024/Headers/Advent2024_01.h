#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>

namespace Advent2024_01 {

}

void Solve2024_01() {

	std::fstream file("Input/Input_01.txt");
	std::string bufforA, bufforB;
	std::vector<int> listA, listB;
	while (file >> bufforA >> bufforB) {
		listA.push_back(std::stoi(bufforA));
		listB.push_back(std::stoi(bufforB));
	}
	file.close();
	int sum = 0;
	std::sort(listA.begin(), listA.end());
	std::sort(listB.begin(), listB.end());
	for (int i = 0; i < listA.size(); i++) {
		sum += std::abs(listA[i] - listB[i]);
	}

	std::cout << "Advent2024_01_1:" << sum << "\n";

	unsigned long long similarity = 0;
	int count = 0;
	int j = 0;
	for (int i = 0; i < listA.size(); i++) {
		if (i != 0) {
			if (listA[i] == listA[i - 1]) {
				similarity += (unsigned long long)count * (unsigned long long)listA[i];
				continue;
			}
		}
		count = 0;
		for (; j < listB.size();) {
			if (listA[i] < listB[j]) {
				similarity += (unsigned long long)count * (unsigned long long)listA[i];
				break;
			}
			else if (listA[i] == listB[j]) {
				count++;
				j++;
				continue;
			}
			else{ //listA[i] > listB[j]
				j++;
				continue;
			}
		}
	}


	std::cout << "Advent2024_01_2:" << similarity << "\n";
}

