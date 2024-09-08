#pragma once

#include "Piece.h"
#include "LinkedList.h"
#include "Tuple.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Castle.h"

using namespace std;

class Game {

private:
	LinkedList<Piece*>* whitePieces;
	LinkedList<Piece*>* blackPieces;
	SquareArray<Piece*>* squares;
	bool turn;
	bool whiteShortCastle;
	bool whiteLongCastle;
	bool blackShortCastle;
	bool blackLongCastle;
	bool promote;

	Tuple* promoteDest;

	Piece* whiteKing;
	Piece* blackKing;

public:
	Game();
	~Game();

	LinkedList<Piece*>* getWhitePieces();
	LinkedList<Piece*>* getBlackPieces();
	SquareArray<Piece*>* getSquares();

	void setWhitePieces(LinkedList<Piece*>* pieces);
	void setBlackPieces(LinkedList<Piece*>* pieces);
	void setSquares(SquareArray<Piece*>* squares);

	void removePiece(Piece* piece);
	void addPiece(Piece* piece);

	void movePiece(Piece* piece, Tuple* position);

	void startingPosition();

	bool compute();

	void debug();

	bool getTurn();
	void setTurn(bool turn);
	void changeTurn();

	bool getPromote();

	Piece* getWhiteKing();
	Piece* getBlackKing();

	Tuple* getPromoteDest();

	void setPromote(bool promote);
};
