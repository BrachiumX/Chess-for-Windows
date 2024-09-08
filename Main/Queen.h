#pragma once

#include "Piece.h"

class Queen : public Piece {

public:

	Queen(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side);

	int compute();
};