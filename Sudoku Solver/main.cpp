#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace sf;

Color black(44, 58, 71);
Color orange(249, 127, 81);
Color red(255, 82, 82);
Color yellow(255, 177, 66);

Font font;

bool isSafe(int mat[][9], int i, int j, int number, int n) {
	for (int k = 0; k < n; k++) {
		if (mat[k][j] == number || mat[i][k] == number) {
			return false;
		}
	}

	// check for subgrid
	int sx = (i / 3) * 3;
	int sy = (j / 3) * 3;

	for (int x = sx; x < sx + 3; x++) {
		for (int y = sy; y < sy + 3; y++) {
			if (mat[x][y] == number)
				return false;
		}
	}

	return true;
}

void printBoard(int mat[][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			printf("%i ", mat[i][j]);
		printf("\n");
	}
}

bool sodokuSolver(RenderWindow& window, int mat[][9], int i, int j, int n) {
	// base case
	if (i == n) {
		// print solution
		return true;
	}

	// Recursive case
	if (j == n) {
		return sodokuSolver(window, mat, i + 1, 0, n);
	}

	// Skip the prefilled cell
	if (mat[i][j] != 0) {
		return sodokuSolver(window, mat, i, j + 1, n);
	}

	// Trying out all possible solutions
	for (int number = 1; number <= 9; number++) {
		// Whether it is safe to put the number or not

		if (isSafe(mat, i, j, number, n)) {
			mat[i][j] = number;

			Text number;
			number.setFont(font);
			number.setCharacterSize(60);
			number.setString(to_string(mat[i][j]));
			number.setOrigin(number.getLocalBounds().width / 2, number.getLocalBounds().height / 2);
			number.setFillColor(yellow);

			number.setPosition(i * 100 + 45, j * 100 + 45);

			bool solveSubProblem = sodokuSolver(window, mat, i, j + 1, n);

			if (solveSubProblem) {
				return true;
			}
		}
	}

	// if no option works
	mat[i][j] = 0;
	return false;
}

void drawGrid(RenderWindow& window, int boxLength, int nLines, int mat[][9]) {
	for (int i = 1; i < nLines; i++) {
		RectangleShape lineX;
		RectangleShape lineY;

		if (i % 3 == 0) {
			lineX.setSize(Vector2f(5, 900));
			lineY.setSize(Vector2f(900, 5));
		}
			
		else {
			lineX.setSize(Vector2f(1, 900));
			lineY.setSize(Vector2f(900, 1));
		}

		lineX.setPosition(Vector2f(i * boxLength, 0));
		lineX.setFillColor(yellow);

		lineY.setPosition(Vector2f(0, i * boxLength));
		lineY.setFillColor(yellow);

		window.draw(lineX);
		window.draw(lineY);
	}

	RectangleShape extra;
	extra.setSize(Vector2f(5, 900));
	extra.setPosition(Vector2f(900, 0));
	extra.setFillColor(yellow);
	window.draw(extra);

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			Text number;
			number.setFont(font);
			number.setString(to_string(mat[i][j]));
			number.setOrigin(number.getLocalBounds().width / 2, number.getLocalBounds().height / 2);
			number.setPosition(Vector2f(i * boxLength + 40, j * boxLength + 40));
			number.setCharacterSize(50);

			window.draw(number);
		}
	}

}

int main() {
	int n = 9;
	RenderWindow window(VideoMode(1300, 900), "SFML works!");
	if (!font.loadFromFile("PlatNomor-WyVnn.ttf"))
		printf("Font could not load\n");

	int mat[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear(black);
		// Draw here 
		drawGrid(window, 100, 9, mat);

		if (!sodokuSolver(window, mat, 0, 0, n))
			printf("No solution exists\n");

		window.display();
	}

	return 0;
}
