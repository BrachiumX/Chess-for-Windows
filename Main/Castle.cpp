#pragma once

#include "Castle.h"

bool Castle::checkLongCastle(SquareArray<Piece*>* squares, bool side) {

	int y = 7;

	if(side) {
		y -= 7;
	}

	Piece* tempking = squares->get(4, y);
	Piece* temprook = squares->get(0, y);

	if(tempking == nullptr || temprook == nullptr || tempking->getType() != "King" || temprook->getType() != "Rook") {
		return false;
	}

	King* king = (King*)tempking;
	Rook* rook = (Rook*)temprook;

	if(king->getMoved() || rook->getMoved()) {
		return false;
	}

	for(int i = 1; i < 4; i++) {

		if(squares->get(i, y) != nullptr) {
			return false;
		}
	}

	if(!king->isCheck() && !king->isCheckAfterMove(3, y) && !king->isCheckAfterMove(2, y)) {
		king->getMovables()->add(new Tuple(2, y));
		return true;
	}

	return false;
}

bool Castle::checkShortCastle(SquareArray<Piece*>* squares, bool side) {

	int y = 7;

	if(side) {
		y -= 7;
	}

	Piece* tempking = squares->get(4, y);
	Piece* temprook = squares->get(7, y);

	if(tempking == nullptr || temprook == nullptr || tempking->getType() != "King" || temprook->getType() != "Rook") {
		return false;
	}

	King* king = (King*)tempking;
	Rook* rook = (Rook*)temprook;

	if(king->getMoved() || rook->getMoved()) {
		return false;
	}

	for(int i = 5; i < 7; i++) {

		if(squares->get(i, y) != nullptr) {
			return false;
		}
	}

	if(!king->isCheck() && !king->isCheckAfterMove(5, y) && !king->isCheckAfterMove(6, y)) {
		king->getMovables()->add(new Tuple(6, y));
		return true;
	}

	return false;
}
