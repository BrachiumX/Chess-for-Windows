#include "Piece.h"

#pragma once

Piece::~Piece() {
	delete position;
	delete movables;
}

void Piece::setPosition(Tuple* position) {
	delete this->position;
	this->position = position;
}

Tuple* Piece::getPosition() {
	return position;
}

string Piece::getType() {
	return type;
}

int Piece::compute() {
	return -1;
}

LinkedList<Tuple*>* Piece::getMovables() {
	return movables;
}

void Piece::setSide(bool side) {
	this->side = side;
}

bool Piece::getSide() {
	return side;
}

bool Piece::isCheck() {
	if(this->getKing() != nullptr) {
		return this->getKing()->isCheck();
	}

	else {
		int opposedPawnMove = -1;

		if(side) {
			opposedPawnMove = 1;
		}

		int x = position->getPositionX();
		int y = position->getPositionY();

		if(!squares->out(y + opposedPawnMove)) {

			Piece* temp;

			for(int i = -1; i < 2; i += 2) {
				temp = squares->get(x + i, y + opposedPawnMove);

				if(!squares->out(x + i) && temp != nullptr && temp->getSide() != side && temp->getType() == "Pawn") {
					return true;
				}
			}
		}

		for(int v = -1; v < 2; v += 2) {
			for(int n = 0; n < 2; n++) {
				for(int i = 1; i < 8; i++) {
					int nX = x;
					int nY = y;

					if(n == 0) {
						nX += i * v;
					}
					else {
						nY += i * v;
					}

					if(squares->out(nX, nY)) {
						break;
					}

					Piece* temp = squares->get(nX, nY);


					if(temp != nullptr) {

						if(temp->getSide() == side) {
							break;
						}
						else if(temp->getType() == "Rook" || temp->getType() == "Queen") {
							return true;
						}
					}
				}
			}
		}

		for(int i = -1; i < 2; i += 2) {
			for(int j = -1; j < 2; j += 2) {
				for(int v = 1; v < 8; v++) {
					int nX = x + v * i;
					int nY = y + v * j;

					if(squares->out(nX, nY)) {
						break;
					}

					Piece* temp = squares->get(nX, nY);

					if(temp != nullptr) {

						if(temp->getSide() == side) {
							break;
						}
						else if(temp->getType() == "Bishop" || temp->getType() == "Queen") {
							return true;
						}
					}
				}
			}
		}

		for(int i = -1; i < 2; i++) {
			for(int j = -2; j < 2; j++) {

				if(i == 0 && j == 0) {
					continue;
				}

				int nX = x + i;
				int nY = y + j;

				if(squares->out(nX, nY)) {
					continue;
				}

				Piece* temp = squares->get(nX, nY);

				if(temp != nullptr) {

					if(temp->getType() == "King") {
						return true;
					}
				}
			}
		}

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

					if(squares->out(nX, nY)) {
						continue;
					}

					Piece* temp = squares->get(nX, nY);

					if(temp != nullptr && temp->getSide() != side && temp->getType() == "Knight") {
						return true;
					}
				}
			}
		}

		return false;
	}
}

bool Piece::isCheckAfterMove(int positionX, int positionY) {
	squares->moveTemp(this->position->getPositionX(), this->position->getPositionY(), positionX, positionY);
	bool result = isCheck();
	squares->resetTemp();
	return result;
}

bool Piece::isCheckAfterRemove() {
	squares->set(nullptr, this->position->getPositionX(), this->position->getPositionY());
	bool result = isCheck();
	squares->set(this, this->position->getPositionX(), this->position->getPositionY());
	return result;
}

Piece* Piece::getKing() {
	return king;
}

void Piece::setKing(Piece* king) {
	this->king = king;
}

SquareArray<Piece*>* Piece::getSquares() {
	return squares;
}

void Piece::setSquares(SquareArray<Piece*>* squares) {
	this->squares = squares;
}
