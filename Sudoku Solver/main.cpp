#include<bits/stdc++.h>

using namespace std;

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

bool sodokuSolver(int mat[][9], int i, int j, int n) {
	// base case
	if (i == n) {
		// print solution
		printBoard(mat);
		return true;
	}

	// Recursive case
	if (j == n) {
		return sodokuSolver(mat, i + 1, 0, n);
	}

	// Skip the prefilled cell
	if (mat[i][j] != 0) {
		return sodokuSolver(mat, i, j + 1, n);
	}

	// Trying out all possible solutions
	for (int number = 1; number <= 9; number++) {
		// Whether it is safe to put the number or not

		if (isSafe(mat, i, j, number, n)) {
			mat[i][j] = number;
			bool solveSubProblem = sodokuSolver(mat, i, j + 1, n);

			if (solveSubProblem) {
				return true;
			}
		}
	}

	// if no option works
	mat[i][j] = 0;
	return false;
}

int main() {
	int n = 9;

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

	//if (!sodokuSolver(mat, 0, 0, n))
	//	printf("No solution exists\n");
}
