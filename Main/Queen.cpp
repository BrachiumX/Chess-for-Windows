#pragma once

#include "Queen.h"
#include "Movement.h"

Queen::Queen(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->king = king;
	this->squares = squares;
	this->position = position;
	this->side = side;
	this->type = "Queen";
}

int Queen::compute() {
	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>();

	return Movement::diagonalMovement(this) + Movement::straightMovement(this) + 1;
}