#pragma once

#include "Piece.h"

class Rook : public Piece {

private:
	bool moved;

public:
	Rook(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side);

	int compute();

	bool getMoved();
	void setMoved(bool moved);
};