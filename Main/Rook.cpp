#pragma once

#include "Rook.h"
#include "Movement.h"

Rook::Rook(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->king = king;
	this->squares = squares;
	this->position = position;
	this->side = side;
	this->moved = false;
	this->movables = nullptr;
	this->type = "Rook";
}

int Rook::compute() {
	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>();

	return Movement::straightMovement(this);
}

void Rook::setMoved(bool moved) {
	this->moved = moved;
}

bool Rook::getMoved() {
	return moved;
}