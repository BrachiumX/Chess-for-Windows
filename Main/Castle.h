#pragma once

#include "King.h"
#include "Rook.h"
#include "Tuple.h"

class Castle {

public:

	static bool checkShortCastle(SquareArray<Piece*>* squares, bool side);
	static bool checkLongCastle(SquareArray<Piece*>* squares, bool side);

};