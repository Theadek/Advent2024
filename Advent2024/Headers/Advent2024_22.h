#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2024_22 {
	struct HashNode {
		int p1, p2, p3, p4, value;
		HashNode(int pp1, int pp2, int pp3, int pp4, int value) {
			p1 = pp1;
			p2 = pp2;
			p3 = pp3;
			p4 = pp4;
			this->value = value;
		}
		HashNode(HashNode& hashNode, int pp4, int value) {
			p1 = hashNode.p2;
			p2 = hashNode.p3;
			p3 = hashNode.p4;
			p4 = pp4;
			this->value = value;
		}
		HashNode(const HashNode& other) {
			p1 = other.p1;
			p2 = other.p2;
			p3 = other.p3;
			p4 = other.p4;
			value = other.value;
		}
		HashNode& operator=(const HashNode& other) {
			p1 = other.p1;
			p2 = other.p2;
			p3 = other.p3;
			p4 = other.p4;
			value = other.value;
			return *this;
		}
		size_t operator()(const HashNode& nodeToHash) const noexcept {
			size_t hash = (nodeToHash.p1 + 10) * 1000000 + (nodeToHash.p2 + 10) * 10000 + (nodeToHash.p3 + 10) * 100 + (nodeToHash.p4 + 10);
			return hash;
		}

		bool operator==(const HashNode& other) const{
			return p1 == other.p1 && p2 == other.p2 && p3 == other.p3 && p4 == other.p4;
		}
	};

	struct HashNode_CMP {
		inline bool operator() (HashNode a, HashNode b) const {
			if (a.p1 != b.p1) return a.p1 < b.p1;
			if (a.p2 != b.p2) return a.p2 < b.p2;
			if (a.p3 != b.p3) return a.p3 < b.p3;
			return a.p4 < b.p4;
		}
	};

	class HashNodeHash {
	public:
		size_t operator()(const HashNode& nodeToHash) const noexcept {
			size_t hash = (nodeToHash.p1 + 10) * 1000000 + (nodeToHash.p2 + 10) * 10000 + (nodeToHash.p3 + 10) * 100 + (nodeToHash.p4 + 10);
			return hash;
		}
	};

	ULONGLONG SecretMonkey(ULONGLONG secret) {
		secret = secret ^ (secret * 64);
		secret = secret % 16777216;

		secret = secret ^ (secret / 32);
		secret = secret % 16777216;

		secret = secret ^ (secret * 2048);
		secret = secret % 16777216;
		return secret;
	}

}

void Solve2024_22() {

	ULONGLONG secret;
	ULONGLONG sum = 0;
	std::string buffor;
	std::fstream file("Input/Input_22.txt");
	while (file >> buffor) {
		secret = std::stoll(buffor);
		for (int i = 0; i < 2000; i++) {
			ULONGLONG tmp = Advent2024_22::SecretMonkey(secret);
			secret = tmp;
		}
		sum += secret;
	}
	file.close();
	std::cout << "Advent2024_22_1: " << sum << "\n";

	//---part 2---

	std::vector<std::unordered_set<Advent2024_22::HashNode, Advent2024_22::HashNodeHash>> monkeyRemember;
	std::unordered_set<Advent2024_22::HashNode, Advent2024_22::HashNodeHash> monkeyExist;
	file.open("Input/Input_22.txt");
	while (file >> buffor) {
		std::unordered_set<Advent2024_22::HashNode, Advent2024_22::HashNodeHash> monkeyLine;
		//std::unordered_map<Advent2024_22::HashNode, int> monkeyMap;
		int last4Changes[4];
		secret = std::stoll(buffor);
		for (int i = 0; i < 4; i++) {
			ULONGLONG tmp = Advent2024_22::SecretMonkey(secret);
			last4Changes[i] = (int(tmp % 10) - int(secret % 10));
			secret = tmp;
		}
		Advent2024_22::HashNode previousHashNode(last4Changes[0], last4Changes[1], last4Changes[2], last4Changes[3], int(secret % 10));
		monkeyLine.insert(previousHashNode);
		monkeyExist.insert(previousHashNode);
		for (int i = 0; i < 2000 - 4; i++) {
			ULONGLONG tmp = Advent2024_22::SecretMonkey(secret);
			Advent2024_22::HashNode hashNode(previousHashNode, (int(tmp % 10) - int(secret % 10)), int(tmp % 10));
			previousHashNode = hashNode;
			monkeyLine.insert(previousHashNode);
			monkeyExist.insert(previousHashNode);
			secret = tmp;
		}
		monkeyRemember.push_back(monkeyLine);
	}
	file.close();


	int currentwinner = 0;
	for (auto& node : monkeyExist) {
		int tmpSum = 0;
		for (auto& shop : monkeyRemember) {
			if (auto test = shop.find(node); test != shop.end()) {
				tmpSum += (*test).value;
			}
		}
		currentwinner = std::max(currentwinner, tmpSum);
	}

	std::cout << "Advent2024_22_2: " << currentwinner << "\n";
}

