#pragma once

#include "Game.h"

using namespace std;

// true = white
// false = black

Game::Game() {
	squares = new SquareArray<Piece*>();
	blackPieces = new LinkedList<Piece*>();
	whitePieces = new LinkedList<Piece*>();

	promote = false;

	turn = true;

	startingPosition();
}

Game::~Game() {
	delete squares;
	delete blackPieces;
	delete whitePieces;
}

LinkedList<Piece*>* Game::getWhitePieces() {
	return whitePieces;
}

LinkedList<Piece*>* Game::getBlackPieces() {
	return blackPieces;
}

SquareArray<Piece*>* Game::getSquares() {
	return squares;
}

void Game::setWhitePieces(LinkedList<Piece*>* pieces) {
	this->whitePieces = pieces;
}

void Game::setBlackPieces(LinkedList<Piece*>* pieces) {
	this->blackPieces = pieces;
}

void Game::setSquares(SquareArray<Piece*>* squares) {
	this->squares = squares;
}

void Game::removePiece(Piece* piece) {
	Tuple* position = piece->getPosition();

	squares->set(nullptr, position->getPositionX(), position->getPositionY());

	if(piece->getSide()) {
		whitePieces->deleteValue(piece);
	}
	else {
		blackPieces->deleteValue(piece);
	}
}

void Game::addPiece(Piece* piece) {
	Tuple* position = piece->getPosition();

	squares->set(piece, position->getPositionX(), position->getPositionY());

	if(piece->getSide() == true) {
		whitePieces->add(piece);
	}
	else {
		blackPieces->add(piece);
	}
}

void Game::movePiece(Piece* piece, Tuple* position) {

	if(piece->getType() == "King") {

		((King*)piece)->setMoved(true);

		Tuple temp = Tuple(2, 0);

		if(position->equals(&temp) && whiteLongCastle) {
			movePiece(squares->get(0, 0), new Tuple(3, 0));
		}

		temp = Tuple(6, 0);

		if(position->equals(&temp) && whiteShortCastle) {
			movePiece(squares->get(0, 0), new Tuple(5, 0));
		}

		temp = Tuple(2, 7);

		if(position->equals(&temp) && blackLongCastle) {
			movePiece(squares->get(0, 0), new Tuple(3, 7));
		}

		temp = Tuple(6, 7);

		if(position->equals(&temp) && blackShortCastle) {
			movePiece(squares->get(0, 0), new Tuple(5, 7));
		}
	}

	if(piece->getType() == "Pawn") {
		((Pawn*)piece)->setMoved(true);

		if(piece->getPosition()->getPositionY() == position->getPositionY() - 2 || piece->getPosition()->getPositionY() == position->getPositionY() + 2) {
			((Pawn*)piece)->setLastTurnDouble(true);
		}

		if(piece->getPosition()->getPositionX() != position->getPositionX() && squares->get(position->getPositionX(), position->getPositionY()) == nullptr) {
			if(piece->getSide()) {
				removePiece(squares->get(position->getPositionX(), position->getPositionY() - 1));
			}
			else {
				removePiece(squares->get(position->getPositionX(), position->getPositionY() + 1));
			}
		}

		if(position->getPositionY() == 0 || position->getPositionY() == 7) {
			promote = true;
			promoteDest = new Tuple(position->getPositionX(), position->getPositionY());
		}
	}

	if(piece->getType() == "Rook") {
		((Rook*)piece)->setMoved(true);
	}


	Tuple* oldPosition = piece->getPosition();

	squares->set(nullptr, oldPosition->getPositionX(), oldPosition->getPositionY());

	if(squares->get(position->getPositionX(), position->getPositionY()) != nullptr) {
		Piece* queen = piece;
		Piece* pawn = squares->get(position->getPositionX(), position->getPositionY());
		removePiece(squares->get(position->getPositionX(), position->getPositionY()));
	}

	squares->set(piece, position->getPositionX(), position->getPositionY());

	piece->setPosition(position);
}

bool Game::compute() {
	Iterator<Piece*>* iterator;

	bool end = true;

	if(turn) {
		iterator = whitePieces->getIterator();
	}
	else {
		iterator = blackPieces->getIterator();
	}

	Piece* curr = iterator->getNext();

	while(curr != nullptr) {
		if(curr->getType() == "Pawn" && ((Pawn*)curr)->compute() != -1) {
			end = false;
		}

		if(curr->getType() == "Bishop" && ((Bishop*)curr)->compute() != -1) {
			end = false;
		}

		if(curr->getType() == "Rook" && ((Rook*)curr)->compute() != -1) {
			end = false;
		}

		if(curr->getType() == "Knight" && ((Knight*)curr)->compute() != -1) {
			end = false;
		}

		if(curr->getType() == "Queen" && ((Queen*)curr)->compute() != -1) {
			end = false;
		}

		if(curr->getType() == "King" && ((King*)curr)->compute() != -1) {
			end = false;
		}

		curr = iterator->getNext();
	}

	if(turn) {
		whiteLongCastle = Castle::checkLongCastle(squares, turn);
		whiteShortCastle = Castle::checkShortCastle(squares, turn);
	}
	else {
		blackLongCastle = Castle::checkLongCastle(squares, turn);
		blackShortCastle = Castle::checkShortCastle(squares, turn);
	}

	return end;
}

void Game::startingPosition() {

	whiteKing = new King(squares, new Tuple(4, 0), true);
	blackKing = new King(squares, new Tuple(4, 7), false);

	addPiece(whiteKing);
	addPiece(blackKing);

	for(int i = 0; i < 2; i++) {

		Piece* king = blackKing;
		bool side = false;
		int y = 7;

		if(i == 0) {
			side = true;
			y -= 7;
			king = whiteKing;
		}

		Queen* queen = new Queen(king, squares, new Tuple(3, y), side);
		addPiece(queen);

		for(int j = 0; j < 8; j += 7) {
			Rook* rook = new Rook(king, squares, new Tuple(j, y), side);
			addPiece(rook);
		}

		for(int j = 1; j < 7; j += 5) {
			Knight* knight = new Knight(king, squares, new Tuple(j, y), side);
			addPiece(knight);
		}

		for(int j = 2; j < 6; j += 3) {
			Bishop* bishop = new Bishop(king, squares, new Tuple(j, y), side);
			addPiece(bishop);
		}

		if(y == 0) {
			y++;
		}
		else {
			y--;
		}

		for(int j = 0; j < 8; j++) {
			Pawn* pawn = new Pawn(king, squares, new Tuple(j, y), side);
			addPiece(pawn);
		}
	}
}

void Game::debug() {}

void Game::setTurn(bool turn) {
	this->turn = turn;
}

bool Game::getTurn() {
	return turn;
}

void Game::changeTurn() {
	if(turn) {
		turn = false;
		return;
	}
	turn = true;
}

bool Game::getPromote() {
	return promote;
}

Piece* Game::getWhiteKing() {
	return whiteKing;
}

Piece* Game::getBlackKing() {
	return blackKing;
}

Tuple* Game::getPromoteDest() {
	return promoteDest;
}

void Game::setPromote(bool promote) {
	this->promote = promote;
}