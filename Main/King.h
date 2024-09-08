#pragma once

#include "Piece.h"

class King : public Piece {

private:
	bool moved;

public:
	King(SquareArray<Piece*>* squares, Tuple* position, bool side);

	bool isCheckAfterMove(int positionX, int positionY);

	int compute();

	bool getMoved();

	void setMoved(bool moved);
};