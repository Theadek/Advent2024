#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2024_06 {
	// direction
	// up, right, down, left
}

void Solve2024_06() {

	std::string buffor;
	std::vector<std::string> board;
	std::fstream file("Input/Input_06.txt");
	while (file >> buffor) {
		board.push_back(buffor);
	}
	file.close();

	std::vector<std::vector<bool>> visited;
	for (int i = 0; i < board.size(); i++) {
		std::vector<bool> tmp;
		for (int j = 0; j < board[i].length(); j++) {
			tmp.push_back(false);
		}
		visited.push_back(tmp);
	}

	// find starting position
	int positionX, positionY, rotation = 0;
	for (int i = 0; i < board.size(); i++) {
		int index = board[i].find('^');
		if (index != -1) {
			positionX = index;
			positionY = i;
			break;
		}
	}
	// mark starting position as visited
	int startX = positionX;
	int startY = positionY;
	visited[positionY][positionX] = true;

	// walk path
	while (true) {
		// determinate guard rotation
		int directionX = 0, directionY = 0;
		if (rotation == 0) directionY = - 1;
		else if (rotation == 1) directionX = 1;
		else if (rotation == 2) directionY = 1;
		else directionX = -1;

		// check if guard walk away
		if (positionX + directionX < 0 || positionX + directionX >= board[0].length())  break;
		if (positionY + directionY < 0 || positionY + directionY >= board.size())		break;

		// check for obstacle
		if (board[positionY + directionY][positionX + directionX] == '#') {
			rotation = (rotation + 1) % 4;
			continue;
		}
		else {
			// walk forward
			positionX += directionX;
			positionY += directionY;
			visited[positionY][positionX] = true;
		}
	}

	// calculated number of visited spaces
	int numberOfVisitedSpaces = 0;
	for (int i = 0; i < visited.size(); i++) {
		for (int j = 0; j < visited[i].size(); j++) {
			if (visited[i][j])numberOfVisitedSpaces++;
		}
	}
	std::cout << "Advent2024_06_1: " << numberOfVisitedSpaces << "\n";

	//---part 2---

	// allocate new table
	int*** visitedDirections = new int** [board.size()];
	for (int i = 0; i < board.size(); i++) {
		visitedDirections[i] = new int* [board[i].size()];
		for (int j = 0; j < board[i].size(); j++) {
			visitedDirections[i][j] = new int[4];
			for (int k = 0; k < 4; k++) {
				visitedDirections[i][j][k] = false;
			}
		}
	}

	// reset starting position and rotation
	positionX = startX;
	positionY = startY;
	rotation = 0;

	// number of possible spaces for obstacles to place
	int numberOfObstacles = 0;

	// walk path
	while (true) {
		// determinate guard rotation
		int directionX = 0, directionY = 0;
		if (rotation == 0) directionY = -1;
		else if (rotation == 1) directionX = 1;
		else if (rotation == 2) directionY = 1;
		else directionX = -1;

		// add position to data table
		visitedDirections[positionY][positionX][rotation] = 1;

		// check if guard walk away
		if (positionX + directionX < 0 || positionX + directionX >= board[0].length())  break;
		if (positionY + directionY < 0 || positionY + directionY >= board.size())		break;

		// can't place obstacle where it was previously visited or where obstacle already is
		if (visitedDirections[positionY + directionY][positionX + directionX][0] == 0&&
			visitedDirections[positionY + directionY][positionX + directionX][1] == 0&&
			visitedDirections[positionY + directionY][positionX + directionX][2] == 0&&
			visitedDirections[positionY + directionY][positionX + directionX][3] == 0&&
			board[positionY + directionY][positionX + directionX] != '#') {
			// check for loop
			board[positionY + directionY][positionX + directionX] = '#';
			int newRotation = (rotation + 1) % 4;
			int newDirectionX = 0, newDirectionY = 0;
			int newPositionX = positionX, newPositionY = positionY;

			while(true) {
				newDirectionX = 0, newDirectionY = 0;
				if (newRotation == 0) newDirectionY = -1;
				else if (newRotation == 1) newDirectionX = 1;
				else if (newRotation == 2) newDirectionY = 1;
				else newDirectionX = -1;

				if (newPositionX + newDirectionX < 0 || newPositionX + newDirectionX >= board[0].length())  break;
				if (newPositionY + newDirectionY < 0 || newPositionY + newDirectionY >= board.size())		break;

				// check for obstacle
				if (board[newPositionY + newDirectionY][newPositionX + newDirectionX] == '#') {
					newRotation = (newRotation + 1) % 4;
					continue;
				}
				else {
					// walk forward
					newPositionX += newDirectionX;
					newPositionY += newDirectionY;
					if (visitedDirections[newPositionY][newPositionX][newRotation] > 0) {
						numberOfObstacles++;
						break;
					}
					else {
						visitedDirections[newPositionY][newPositionX][newRotation] = 2;
					}
				}

			}
			// clean after predictions
			board[positionY + directionY][positionX + directionX] = '.';
			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					for (int k = 0; k < 4; k++) {
						if (visitedDirections[i][j][k] == 2) visitedDirections[i][j][k] = 1;
					}
				}
			}
		}


		// check for obstacle
		if (board[positionY + directionY][positionX + directionX] == '#') {
			rotation = (rotation + 1) % 4;
		}
		else {
			// walk forward
			positionX += directionX;
			positionY += directionY;
		}
	}






	std::cout << "Advent2024_06_2: " << numberOfObstacles << "\n";


	// free table
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			delete visitedDirections[i][j];
		}
		delete visitedDirections[i];
	}
	delete visitedDirections;
}

