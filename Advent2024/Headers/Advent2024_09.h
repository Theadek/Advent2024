#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_09 {
	struct Node {
	public:
		int id;
		int amount;
		int emptyAfter;
		Node(int id, int amount, int emptyAfter) {
			this->id = id;
			this->amount = amount;
			this->emptyAfter = emptyAfter;
		}
	};
}

void Solve2024_09() {

	std::fstream file("Input/Input_09.txt");
	std::string buffor;
	file >> buffor;
	file.close();

	std::vector<Advent2024_09::Node> nodes;


	for (int i = 0; i < buffor.length() / 2 + 1; i++) {

		if (i == buffor.length() /2) {
			Advent2024_09::Node node(i, buffor[i * 2] - '0', 0);
			nodes.push_back(node);
		}
		else {
			Advent2024_09::Node node(i, buffor[i * 2] - '0', buffor[i * 2 + 1] - '0');
			nodes.push_back(node);
		}
	}

	int emptyIndex = 0;
	while (true) {
		bool overflow = false;
		while (nodes[emptyIndex].emptyAfter == 0) {
			emptyIndex++;
			if (emptyIndex >= nodes.size()) {
				overflow = true;
				break;
			}
		}
		if (overflow)break;
		if (nodes[emptyIndex].emptyAfter >= nodes[nodes.size() - 1].amount) {
			Advent2024_09::Node node(nodes[nodes.size() - 1].id, nodes[nodes.size() - 1].amount, nodes[emptyIndex].emptyAfter - nodes[nodes.size() - 1].amount);
			nodes.insert(nodes.begin() + emptyIndex + 1, node);
			nodes.erase(nodes.end() - 1);
			nodes[emptyIndex].emptyAfter = 0;
		}
		else {
			Advent2024_09::Node node(nodes[nodes.size() - 1].id, nodes[emptyIndex].emptyAfter, 0);
			nodes.insert(nodes.begin() + emptyIndex + 1, node);
			nodes[nodes.size() - 1].amount -= nodes[emptyIndex].emptyAfter;
			nodes[emptyIndex].emptyAfter = 0;
		}
	}

	long long sum = 0;
	long long index = 0;
	for (int i = 0; i < nodes.size(); i++) {
		for (long long j = 0; j < nodes[i].amount; j++) {
			sum += (index + j) * (long long)nodes[i].id;
		}
		index += nodes[i].amount;
	}

	std::cout << "Advent2024_09_1: " << sum << "\n";

	//---part 2---

	nodes.clear();

	for (int i = 0; i < buffor.length() / 2 + 1; i++) {

		if (i == buffor.length() / 2) {
			Advent2024_09::Node node(i, buffor[i * 2] - '0', 0);
			nodes.push_back(node);
		}
		else {
			Advent2024_09::Node node(i, buffor[i * 2] - '0', buffor[i * 2 + 1] - '0');
			nodes.push_back(node);
		}
	}

	int currentId = nodes[nodes.size() - 1].id;
	for (int i = nodes.size()-1; i > 0; i--) {
		if (nodes[i].id != currentId) continue;
		for (int j = 0; j < i; j++) {
			if (nodes[j].emptyAfter >= nodes[i].amount) {
				Advent2024_09::Node node(nodes[i].id, nodes[i].amount, nodes[j].emptyAfter - nodes[i].amount);
				nodes[j].emptyAfter = 0;
				nodes.insert(nodes.begin() + j + 1, node);
				i++;
				nodes[i - 1].emptyAfter += nodes[i].amount + nodes[i].emptyAfter;
				nodes.erase(nodes.begin() + i);
				break;
			}
		}
		currentId--;


	}

	sum = 0;
	index = 0;
	for (int i = 0; i < nodes.size(); i++) {
		for (long long j = 0; j < nodes[i].amount; j++) {
			sum += (index + j) * (long long)nodes[i].id;
		}
		index += (long long)nodes[i].amount + (long long)nodes[i].emptyAfter;
	}

	std::cout << "Advent2024_09_2: " << sum << "\n";
}

