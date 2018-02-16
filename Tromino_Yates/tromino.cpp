#include "tromino.h"

void Tromino::clear() {
	delete[] mBoard;
}

void Tromino::copy(const Tromino& toCopy) {
	mSize = toCopy.mSize;
	mNextPlacement = toCopy.mNextPlacement;
	mBoard = new int[mSize * mSize];

	for (int i = 0; i < mSize * mSize; i++) {
		mBoard[i] = toCopy.mBoard[i];
	}
}

void Tromino::checkForXandYOutOfBoardRange(int x, int y) const {
	if (x < 0 || x >= mSize) {
		throw std::invalid_argument("x is outside the board range");
	}

	if (y < 0 || y >= mSize) {
		throw std::invalid_argument("y is outside the board range");
	}
}

int Tromino::max(int a, int b, int c) const {
	int largest = a;
	if (b > largest) {
		largest = b;
	}

	if (c > largest) {
		largest = c;
	}

	return largest;
}

int Tromino::min(int a, int b, int c) const {
	int smallest = a;
	if (b < smallest) {
		smallest = b;
	}

	if (c < smallest) {
		smallest = c;
	}

	return smallest;
}

void Tromino::place(int x, int y, int value) {
	mBoard[y * mSize + x] = value;
}

Tromino::Tromino(int n, int x, int y) {
	if (n < 1) {
		throw std::invalid_argument("n cannot be less than 1");
	}

	// First, we compute 2 to the power of n
	mSize = 1;
	mSize <<= n;

	checkForXandYOutOfBoardRange(x, y);

	// Second, we declare the mBoard.
	mBoard = new int[mSize * mSize];

	// Third, we initialize the board
	for (int i = 0; i < mSize * mSize; i++) {
		mBoard[i] = -1;
	}

	// Fourth, we block out the position (x,y)
	place(x, y, 0);
	mNextPlacement = 1;
}

Tromino::~Tromino() {
	clear();
}

Tromino::Tromino(const Tromino& toCopy) {
	copy(toCopy);
}

Tromino& Tromino::operator=(const Tromino& rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

int Tromino::get(int x, int y) const {
	checkForXandYOutOfBoardRange(x, y);
	return mBoard[y * mSize + x];
}

void Tromino::place(int x1, int y1, int x2, int y2, int x3, int y3) {
	checkForXandYOutOfBoardRange(x1, y1);
	checkForXandYOutOfBoardRange(x2, y2);
	checkForXandYOutOfBoardRange(x3, y3);

	int maxX = max(x1, x2, x3);
	int minX = min(x1, x2, x3);
	int maxY = max(y1, y2, y3);
	int minY = min(y1, y2, y3);

	if (maxX - minX != 1) {
		throw std::invalid_argument("Difference in x coordinates of Tromino must be 1 unit.");
	}

	if (maxY - minY != 1) {
		throw std::invalid_argument("Difference in y coordinates of Tromino must be 1 unit.");
	}

	if (get(x1, y1) != -1) {
		throw std::invalid_argument("First coordinate in place that is already filled.");
	}

	if (get(x2, y2) != -1) {
		throw std::invalid_argument("Second coordinate in place that is already filled.");
	}

	if (get(x3, y3) != -1) {
		throw std::invalid_argument("Third coordinate in place that is already filled.");
	}

	place(x1, y1, mNextPlacement);
	place(x2, y2, mNextPlacement);
	place(x3, y3, mNextPlacement);
	mNextPlacement++;
}

std::ostream& operator<<(std::ostream& os, const Tromino& tromino) {
	for (int i = 0; i < tromino.size(); i++) {
		for (int j = 0; j < tromino.size(); j++) {

			int value = tromino.get(j, i);

			if (value == -1) {
				os << " " << '@';
			}
			else if (value == 0) {
				os << " " << '~';
			}
			else {
				value %= 26;
				os << " " << (char)(value + 'A');
			}
		}
		os << '\n';
	}
	return os;		
}
