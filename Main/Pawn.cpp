#include <string>

#include "Pawn.h"

#pragma once

Pawn::Pawn(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->king = king;
	this->squares = squares;
	this->side = side;
	this->position = position;
	moved = false;
	lastTurnDouble = false;
	type = "Pawn";
	movables = nullptr;
}

int Pawn::compute() {

	lastTurnDouble = false;

	int result = -1;

	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>();

	int yMove = -1;

	if(side) {
		yMove = 1;
	}

	int x = position->getPositionX();
	int y = position->getPositionY();

	bool check = isCheckAfterRemove();
	bool poscheck;

	if(!squares->out(y + yMove)) {

		if(squares->get(x, y + yMove) == nullptr) {

			if(!check) {
				poscheck = false;
			}
			else {
				poscheck = isCheckAfterMove(x, y + yMove);
			}

			if(!poscheck) {
				movables->add(new Tuple(x, y + yMove));
				result++;
			}

			if(!check) {
				poscheck = false;
			}
			else {
				poscheck = isCheckAfterMove(x, y + 2 * yMove);
			}

			if(!poscheck && !squares->out(y + 2 * yMove) && !moved && squares->get(x, y + 2 * yMove) == nullptr) {
				movables->add(new Tuple(x, y + 2 * yMove));
				result++;
			}
		}
	}

	Piece* temp;

	for(int i = -1; i < 2; i += 2) {

		if(squares->out(x + i)) {
			continue;
		}

		if(!check) {
			poscheck = false;
		}
		else {
			poscheck = isCheckAfterMove(x, y + yMove);
		}

		if(poscheck) {
			continue;
		}

		temp = squares->get(x + i, y + yMove);

		if(temp != nullptr && temp->getSide() != side) {
			movables->add(new Tuple(x + i, y + yMove));

			result++;
		}
	}

	for(int i = -1; i < 2; i += 2) {

		if(squares->out(x + i) || squares->out(y + yMove)) {
			continue;
		}

		temp = squares->get(x + i, y);

		if(!check) {
			poscheck = false;
		}
		else {
			poscheck = isCheckAfterMove(x + i, y + yMove);
		}

		if(poscheck) {
			continue;
		}

		if(temp != nullptr && temp->getSide() != side && temp->getType() == "Pawn") {
			Pawn* otherpawn = (Pawn*)temp;

			if(otherpawn->getLastTurnDouble()) {
				movables->add(new Tuple(x + i, y + yMove));

				result++;
			}
		}
	}
	return result;
}

void Pawn::setMoved(bool moved) {
	this->moved = moved;
}

void Pawn::setLastTurnDouble(bool lastTurnDouble) {
	this->lastTurnDouble = lastTurnDouble;
}

bool Pawn::getMoved() {
	return moved;
}

bool Pawn::getLastTurnDouble() {
	return lastTurnDouble;
}
