#include "Piece.h"

#pragma once

class Pawn : public Piece {
private:
	bool moved;
	bool lastTurnDouble;

public:
	Pawn(Piece* king, SquareArray<Piece*>* squares, Tuple* position, bool side);

	int compute();

	void setMoved(bool moved);
	void setLastTurnDouble(bool lastTurnDouble);

	bool getMoved();
	bool getLastTurnDouble();
};