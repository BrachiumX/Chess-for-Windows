#pragma once 

#include "Movement.h"

int Movement::straightMovement(Piece* piece) {

	int result = -1;

	Tuple* position = piece->getPosition();
	SquareArray<Piece*>* squares = piece->getSquares();

	int x = position->getPositionX();
	int y = position->getPositionY();

	bool check = piece->isCheckAfterRemove();
	bool poscheck = false;

	for(int v = -1; v < 2; v += 2) {
		for(int n = 0; n < 2; n++) {

			if(n == 0 && squares->out(x + v)) {
				continue;
			}

			if(n == 1 && squares->out(y + v)) {
				continue;
			}

			for(int i = 1; i < 8; i++) {

				int nX = x;
				int nY = y;

				if(n == 0) {
					nX += i * v;
				}
				else {
					nY += i * v;
				}

				if(!check) {
					poscheck = false;
				}
				else {
					poscheck = piece->isCheckAfterMove(nX, nY);
				}

				if(poscheck) {

					if(squares->out(nX, nY) || squares->get(nX, nY) != nullptr) {
						break;
					}
					continue;
				}

				Piece* temp = squares->get(nX, nY);

				if(squares->out(nX, nY)) {
					break;
				}
				if(temp != nullptr && temp->getSide() == piece->getSide()) {
					break;
				}
				piece->movables->add(new Tuple(nX, nY));
				result++;

				if(temp != nullptr) {
					break;
				}
			}
		}
	}

	return result;
}

int Movement::diagonalMovement(Piece* piece) {

	int result = -1;

	Tuple* position = piece->getPosition();
	SquareArray<Piece*>* squares = piece->getSquares();

	int x = position->getPositionX();
	int y = position->getPositionY();

	bool check = piece->isCheckAfterRemove();
	bool poscheck = false;

	for(int i = -1; i < 2; i += 2) {
		for(int j = -1; j < 2; j += 2) {

			if(squares->out(x + i, y + j)) {
				continue;
			}

			for(int v = 1; v < 8; v++) {

				int nX = x + v * i;
				int nY = y + v * j;

				if(!check) {
					poscheck = false;
				}
				else {
					poscheck = piece->isCheckAfterMove(nX, nY);
				}

				if(poscheck) {

					if(squares->out(nX, nY) || squares->get(nX, nY) != nullptr) {
						break;
					}

					continue;
				}

				Piece* temp = squares->get(nX, nY);

				if(squares->out(nX, nY)) {
					break;
				}
				if(temp != nullptr && temp->getSide() == piece->getSide()) {
					break;
				}
				piece->movables->add(new Tuple(nX, nY));
				result++;

				if(temp != nullptr) {
					break;
				}
			}
		}
	}

	return result;
}
