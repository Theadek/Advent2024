#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

namespace Advent2024_11 {
	struct Node {
	public:
		long long value;
		Node* next;
		long long amount;
		Node() {
			value = 0;
			next = nullptr;
			amount = 1;
		}
		Node(long long v) {
			value = v;
			next = nullptr;
			amount = 1;
		}
		Node(long long v, Node* n) {
			value = v;
			next = n;
			amount = 1;
		}
		Node(long long v, Node* n, long long a) {
			value = v;
			next = n;
			amount = a;
		}

	};
	class NodeList {
	public:
		Node* first;
		Node* last;
		NodeList() {
			first = nullptr;
			last = nullptr;
		}

		void Merge() {
			std::map<long long, Node*> occurence;
			Node* ptr = first;
			Node* previous = nullptr;

			auto occ = occurence.find(ptr->value);
			while (ptr != nullptr) {
				auto occ = occurence.find(ptr->value);
				if (occ != occurence.end()) {
					occ->second->amount += ptr->amount;
					previous->next = ptr->next;
					delete ptr;
					ptr = previous->next;
				}
				else {
					std::pair<long long, Node*> newPair;
					newPair.first = ptr->value;
					newPair.second = ptr;
					occurence.insert(newPair);
					previous = ptr;
					ptr = ptr->next;
				}
			}
		}
	};
}

void Solve2024_11() {
	Advent2024_11::NodeList list;

	std::fstream file("Input/Input_11.txt");
	std::string buffor;
	while (file >> buffor) {
		Advent2024_11::Node* node = new Advent2024_11::Node(std::stoll(buffor));
		if (list.first == nullptr) {
			list.first = list.last = node;
		}
		else {
			list.last->next = node;
			list.last = node;
		}
	}
	file.close();

	for (int blink = 0; blink < 25; blink++) {
		Advent2024_11::Node* ptr = list.first;
		while (ptr != nullptr) {
			std::string str = std::to_string(ptr->value);
			if (ptr->value == 0) {
				ptr->value = 1;
				ptr = ptr->next;
			}
			else if (str.length() % 2 == 0) {
				Advent2024_11::Node* secondNode = new Advent2024_11::Node(std::stoll(str.substr(str.length()/2,str.length()/2)), ptr->next, ptr->amount);
				ptr->value = std::stoll(str.substr(0, str.length() / 2));
				ptr->next = secondNode;
				ptr = secondNode->next;
			}
			else {
				ptr->value *= 2024;
				ptr = ptr->next;
			}

		}
		list.Merge();
	}

	long long answer = 0;
	Advent2024_11::Node* ptr = list.first;
	while (ptr != nullptr) {
		answer += ptr->amount;
		ptr = ptr->next;
	}


	std::cout << "Advent2024_11_1: " << answer << "\n";

	for (int blink = 25; blink < 75; blink++) {
		Advent2024_11::Node* ptr = list.first;
		while (ptr != nullptr) {
			std::string str = std::to_string(ptr->value);
			if (ptr->value == 0) {
				ptr->value = 1;
				ptr = ptr->next;
			}
			else if (str.length() % 2 == 0) {
				Advent2024_11::Node* secondNode = new Advent2024_11::Node(std::stoll(str.substr(str.length() / 2, str.length() / 2)), ptr->next, ptr->amount);
				ptr->value = std::stoll(str.substr(0, str.length() / 2));
				ptr->next = secondNode;
				ptr = secondNode->next;
			}
			else {
				ptr->value *= 2024;
				ptr = ptr->next;
			}

		}
		list.Merge();
	}

	ptr = list.first;
	answer = 0;
	while (ptr != nullptr) {
		answer += ptr->amount;
		ptr = ptr->next;
	}

	std::cout << "Advent2024_11_2: " << answer << "\n";

	// cleaning
	ptr = list.first;
	while (ptr != nullptr) {
		Advent2024_11::Node* next = ptr->next;
		delete ptr;
		ptr = next;
	}

}

