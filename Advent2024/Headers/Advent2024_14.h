#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"CImg/CImg.h"
#include<chrono>
#include<thread>

namespace Advent2024_14 {

}

void Solve2024_14() {

	std::vector<std::pair<int, int>> startingPosition;
	std::vector<std::pair<int, int>> velocity;
	const int HEIGHT = 103; //103
	const int WIDTH = 101; //101
	std::fstream file("Input/Input_14.txt");
	std::string buffor;
	while (file >> buffor) {
		int index = buffor.find(',');
		int x = std::stoi(buffor.substr(2, index - 2));
		int y = std::stoi(buffor.substr(index + 1, buffor.length() - index - 1));
		startingPosition.emplace_back(x, y);
		file >> buffor;
		index = buffor.find(',');
		x = std::stoi(buffor.substr(2, index - 2));
		y = std::stoi(buffor.substr(index + 1, buffor.length() - index - 1));
		velocity.emplace_back(x, y);
	}
	file.close();

	std::vector<std::pair<int, int>> lastPosition;
	for (int i = 0; i < startingPosition.size(); i++) {
		int x = ((startingPosition[i].first + (velocity[i].first * 100)) % WIDTH + WIDTH) % WIDTH;
		int y = ((startingPosition[i].second + (velocity[i].second * 100)) % HEIGHT + HEIGHT) % HEIGHT;
		lastPosition.emplace_back(x, y);
	}
	int quadrant[4] = { 0,0,0,0 };
	for (int i = 0; i < lastPosition.size(); i++) {
		if (lastPosition[i].first < WIDTH / 2 && lastPosition[i].second < HEIGHT / 2) quadrant[0]++;
		if (lastPosition[i].first > WIDTH / 2 && lastPosition[i].second < HEIGHT / 2) quadrant[1]++;
		if (lastPosition[i].first < WIDTH / 2 && lastPosition[i].second > HEIGHT / 2) quadrant[2]++;
		if (lastPosition[i].first > WIDTH / 2 && lastPosition[i].second > HEIGHT / 2) quadrant[3]++;
	}
	int answer = 1;
	for (int i = 0; i < 4; i++) {
		answer *= quadrant[i];
	}
	std::cout << "Advent2024_14_1: " << answer << "\n";
	//---part 2---

	// First find offset first time seeing Horizontal and Vertical EasterEggs
	// Then find repetition rate and find the overlaping one

	/*const unsigned char white[] = { 255,255,255 };

	cimg_library::CImgDisplay disp(1000, 1000, 0, 3, true, false);
	for (int NOseconds = 0; NOseconds <= 1000; NOseconds++) {
		cimg_library::CImg<unsigned char> image(WIDTH, HEIGHT, 1, 3, 0);
		for (int i = 0; i < startingPosition.size(); i++) {
			int x = ((startingPosition[i].first + (velocity[i].first * NOseconds)) % WIDTH + WIDTH) % WIDTH;
			int y = ((startingPosition[i].second + (velocity[i].second * NOseconds)) % HEIGHT + HEIGHT) % HEIGHT;
			image.draw_point(x, y, white, 1);
		}

		disp.display(image);

		int A = 23;
		int B = 80;
		while (true) {
			if (A == B) {
				std::cout << A << "\n";
				break;
			}
			if (A < B)A += 103;
			else B += 101;
		}
	}*/


}

