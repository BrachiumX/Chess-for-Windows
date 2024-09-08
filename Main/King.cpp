#include <string>

#include "King.h"

#pragma once

King::King(SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->squares = squares;
	this->position = position;
	this->side = side;
	type = "King";
	moved = false;
	movables = nullptr;
}

int King::compute() {
	int result = -1;

	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>();

	int x = position->getPositionX();
	int y = position->getPositionY();

	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {

			int nX = x + i;
			int nY = y + j;

			if(i == 0 && j == 0) {
				continue;
			}

			if(!squares->out(nX, nY)) {

				Piece* temp = squares->get(nX, nY);

				if(temp != nullptr && temp->getSide() == side) {
					continue;
				}

				bool check = isCheckAfterMove(nX, nY);

				if(!check) {
					movables->add(new Tuple(nX, nY));
					result++;
				}
			}
		}
	}

	return result;
}

void King::setMoved(bool moved) {
	this->moved = moved;
}

bool King::getMoved() {
	return moved;
}

bool King::isCheckAfterMove(int positionX, int positionY) {
	squares->moveTemp(this->position->getPositionX(), this->position->getPositionY(), positionX, positionY);

	int tempX = this->position->getPositionX();
	int tempY = this->position->getPositionY();

	this->position->setPositionX(positionX);
	this->position->setPositionY(positionY);

	bool result = isCheck();

	this->position->setPositionX(tempX);
	this->position->setPositionY(tempY);

	squares->resetTemp();

	return result;
}