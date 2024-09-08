#include <string>

#pragma once

class Tuple {
private:
	int positionX;
	int positionY;

public:
	Tuple(int positionX, int positionY);
	void setPositionX(int positionX);
	void setPositionY(int positionX);
	int getPositionX();
	int getPositionY();
	std::string toString();
	bool equals(Tuple* other);
};