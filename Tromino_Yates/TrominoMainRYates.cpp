// CSCI 4270 Tromino Problem
// Assignment 3
// Robyn Yates
// 2/13/2018


#include <iostream>
#include "tromino.h"
#include <ctime>

using namespace std;

void solve(int startX, int startY, int x, int y, int n, Tromino& tromino);

int main() {

	int n, x, y; // n = board size, x = x coord. of missing square, y = y coord. of missing square

	cout << "Enter n to determine board size: ";
	cin >> n;

	cout << "Enter the x coordinate of the missing square: ";
	cin >> x;

	cout << "Enter the y coordinate of the missing square: ";
	cin >> y;

	Tromino tromino(n, x, y);


	cout << tromino << endl;

	//clock_t startTime;
	//startTime = clock();

	solve(0, 0, x, y, tromino.size(), tromino);

	//cout << (clock() - startTime) / (double)CLOCKS_PER_SEC << endl;

	cout << tromino << endl;

	system("pause");
	return 0;
}


void solve(int startX, int startY, int x, int y, int size, Tromino& tromino)
{
	int half = floor(size / 2);
	int middleX = startX + half;
	int middleY = startY + half;

	if (size == 1)
		return;
	else
	{
		if (x < middleX && y < middleY) // Quadrant 2
		{
			tromino.place(middleX, middleY, middleX, middleY - 1, middleX - 1, middleY);
			solve(startX, startY, x, y, half, tromino);		// Call to fill quad 2
			solve(startX + half, startY, middleX, middleY - 1, half, tromino);	// Call to get to quad 1
			solve(startX, startY + half, middleX - 1, middleY, half, tromino);	// Call to get to quad 3
			solve(startX + half, startY + half, middleX, middleY, half, tromino); // Recursive call to quadrant 4
		}
		else if (x >= middleX && y < middleY) // Quadrant 1
		{
			tromino.place(middleX - 1, middleY - 1, middleX - 1, middleY, middleX, middleY);
			solve(startX + half, startY, x, y, half, tromino); // Recursive call for current quadrant 1
			solve(startX, startY, middleX - 1, middleY - 1, half, tromino); // Recursive call for quad 2
			solve(startX, startY + half, middleX - 1, middleY, half, tromino); // Recursive call for quadrant 3
			solve(startX + half, startY + half, middleX, middleY, half, tromino); // Recursive call for quadrant 4

		}
		else if (x < middleX && y >= middleY) // Quadrant 3
		{
			tromino.place(middleX - 1, middleY - 1, middleX, middleY, middleX, middleY - 1);
			solve(startX, startY + half, x, y, half, tromino); // Recursive call for current quad 3
			solve(startX + half, startY, middleX, middleY - 1, half, tromino); // Recursive call for current quadrant 1
			solve(startX, startY, middleX - 1, middleY - 1, half, tromino); // Recursive call for quad 2
			solve(startX + half, startY + half, middleX, middleY, half, tromino); // Recursive call to quadrant 4

		}
		else		// Quadrant 4
		{
			tromino.place(middleX - 1, middleY - 1, middleX, middleY - 1, middleX - 1, middleY);
			solve(startX + half, startY + half, x, y, half, tromino); // Recursive call for current quad 4
			solve(startX + half, startY, middleX, middleY - 1, half, tromino); // Recursive call for current quadrant 1
			solve(startX, startY, middleX - 1, middleY - 1, half, tromino); // Recursive call for quad 2
			solve(startX, startY + half, middleX - 1, middleY, half, tromino);	// Recursive call for quad 3
		}
	}
}