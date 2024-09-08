#pragma once

#include "Piece.h"

class Knight : public Piece {

public:
	Knight(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side);

	int compute();
};