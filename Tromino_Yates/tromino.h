#ifndef TROMINO_H
#define TROMINO_H

#include <stdexcept>
#include <fstream>

class Tromino {
private:
	int* mBoard;
	int mSize;
	int mNextPlacement;
	void clear();
	void copy(const Tromino&);
	void checkForXandYOutOfBoardRange(int, int) const;
	int max(int, int, int) const;
	int min(int, int, int) const;
	void place(int, int, int);

public:
	// Specifies N, X, and Y to the initial setup.
	Tromino(int, int, int);

	// Deconstructor
	~Tromino();

	// Copy Constructor
	Tromino(const Tromino&);

	// Operator= method
	Tromino& operator=(const Tromino&);

	// Gets the value of a square on the chessboard.
	// -1 means that a square is unused
	// 0 means that it's the initial missing square
	// Any positive number means that this is used by a tromino
	int get(int, int) const;

	// Place a tromino using these three coordinates for the tile
	// The parameters are, in order, x1, y1, x2, y2, x3, y3.
	// If there are any complications with placing a tile, an
	// error will be thrown.
	void place(int, int, int, int, int, int);

	// Returns the height of the chessboard
	inline int size() const { return mSize; }

	// Used for printing a representation of the board.
	friend std::ostream& operator<<(std::ostream& os, const Tromino& tromino);
};

#endif
