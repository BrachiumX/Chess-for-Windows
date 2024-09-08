#pragma once

#include "Piece.h"

class Movement {

public:
	static int straightMovement(Piece* piece);
	static int diagonalMovement(Piece* piece);
};