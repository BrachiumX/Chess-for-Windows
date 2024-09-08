#pragma once

#include "Knight.h"

Knight::Knight(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side) {
	this->king = king;
	this->squares = squares;
	this->position = position;
	this->side = side;
	this->type = "Knight";
}

int Knight::compute() {

	if(movables != nullptr) {
		delete movables;
	}

	movables = new LinkedList<Tuple*>;

	int result = -1;
	bool check = isCheckAfterRemove();
	bool poscheck = false;

	int x = position->getPositionX();
	int y = position->getPositionY();

	for(int v = 0; v < 2; v++) {
		for(int i = -2; i < 3; i += 4) {
			for(int j = -1; j < 2; j += 2) {

				int nX = x;
				int nY = y;

				if(v == 0) {
					nX += i;
					nY += j;
				}
				else {
					nX += j;
					nY += i;
				}

				if(!check) {
					poscheck = false;
				}
				else {
					poscheck = isCheckAfterMove(nX, nY);
				}

				if(poscheck || squares->out(nX, nY)) {
					continue;
				}

				Piece* temp = squares->get(nX, nY);

				if(temp == nullptr || temp->getSide() != side) {
					movables->add(new Tuple(nX, nY));
					result++;
				}
			}
		}
	}

	return result;
}