#pragma once

#include "Bishop.h"
#include "Movement.h"

Bishop::Bishop(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->king = king;
	this->squares = squares;
	this->position = position;
	this->side = side;
	this->type = "Bishop";
}

int Bishop::compute() {
	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>();

	return Movement::diagonalMovement(this);
}