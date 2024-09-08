#pragma once

#pragma once

#include "Piece.h"

class Bishop : public Piece {

public:

	Bishop(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side);

	int compute();
};