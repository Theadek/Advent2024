#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>

namespace Advent2024_23 {
	struct Node {
		std::string name;
		std::unordered_set<Node*> connections; //or vector

		Node() {

		}
		Node(std::string name){
			this->name = name;
		}
	};
}

void Solve2024_23() {
	std::unordered_map<std::string, Advent2024_23::Node*> nodes;
	std::string buffor;
	std::fstream file("Input/Input_23.txt");
	while (file >> buffor) {
		std::string tmp = buffor.substr(0, 2);
		if (!nodes.contains(tmp)) {
			Advent2024_23::Node* node = new Advent2024_23::Node(tmp);
			nodes[tmp] = node;
		}
		buffor = buffor.substr(3, 2);
		if (!nodes.contains(buffor)) {
			Advent2024_23::Node* node = new Advent2024_23::Node(buffor);
			nodes[buffor] = node;
		}
		Advent2024_23::Node* tmpNode1 = nodes[tmp];
		Advent2024_23::Node* tmpNode2 = nodes[buffor];
		tmpNode1->connections.insert(tmpNode2);
		tmpNode2->connections.insert(tmpNode1);
	}
	file.close();

	std::unordered_set<std::string> LAN;
	for (auto& node : nodes) {
		if (node.first[0] != 't')continue;
		for (auto& conn : node.second->connections) {
			for (auto& conn2 : conn->connections) {
				if (node.second->connections.contains(conn2)) {
					std::vector<std::string> party{ node.first, conn->name, conn2->name };
					std::sort(party.begin(), party.end());
					std::string partyName = party[0] + party[1] + party[2];
					LAN.insert(partyName);
				}
			}
		}
	}
	std::cout << "Advent2024_23_1: " << LAN.size() << "\n";

	//---part 2---
	for (auto& node : nodes) {
		if (node.first[0] == 't')continue;
		for (auto& conn : node.second->connections) {
			for (auto& conn2 : conn->connections) {
				if (node.second->connections.contains(conn2)) {
					std::vector<std::string> party{ node.first, conn->name, conn2->name };
					std::sort(party.begin(), party.end());
					std::string partyName = party[0] + party[1] + party[2];
					LAN.insert(partyName);
				}
			}
		}
	}
	while (true) {
		std::unordered_set<std::string> nextLAN;
		for (auto& l : LAN) {
			std::vector<Advent2024_23::Node*> vLan;
			for (int i = 0; i < l.length(); i += 2) {
				Advent2024_23::Node* node = nodes[l.substr(i, 2)];
				vLan.push_back(node);
			}
			for (auto& n : nodes) {
				bool good = true;
				for (auto& m : vLan) {
					if (!m->connections.contains(n.second)) {
						good = false;
						break;
					}
				}
				if (good) {
					std::vector<std::string> newLAN;
					for (auto& a : vLan) newLAN.push_back(a->name);
					newLAN.push_back(n.first);
					std::sort(newLAN.begin(), newLAN.end());
					std::string newStr = "";
					for (auto& a : newLAN) newStr += a;
					nextLAN.insert(newStr);
				}
			}
		}
		if (nextLAN.empty())break;
		else LAN = nextLAN;
		std::cout << LAN.size() << "\n";
	}




	std::cout << "Advent2024_23_2: ";
	for (auto& a : LAN) {
		std::cout << a.substr(0, 2);
		for (int i = 2; i < a.length(); i += 2) {
			std::cout << "," << a.substr(i, 2);
		}
		std::cout << "\n";
	}


	for (auto& node : nodes) {
		delete node.second;
	}
}

