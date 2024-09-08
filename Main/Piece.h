#include "Tuple.h"
#include "LinkedList.h"
#include "SquareArray.h"

#include <string>

#pragma once

using namespace std;

class Piece {

public:
	SquareArray<Piece*>* squares;
	Tuple* position;
	string type;
	LinkedList<Tuple*>* movables;
	bool side;
	Piece* king;

	~Piece();
	void setSide(bool side);
	void setPosition(Tuple* position);
	void setKing(Piece* king);
	Tuple* getPosition();
	string getType();
	Piece* getKing();
	bool getSide();
	int compute();
	LinkedList<Tuple*>* getMovables();
	bool isCheck();
	SquareArray<Piece*>* getSquares();
	void setSquares(SquareArray<Piece*>* squares);
	bool isCheckAfterMove(int positionX, int positionY);
	bool isCheckAfterRemove();
};