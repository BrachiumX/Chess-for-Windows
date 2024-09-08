#include <string>

#include "Tuple.h"

#pragma once


Tuple::Tuple(int positionX, int positionY) {
	this->positionX = positionX;
	this->positionY = positionY;
}

void Tuple::setPositionX(int positionX) {
	this->positionX = positionX;
}

void Tuple::setPositionY(int positionY) {
	this->positionY = positionY;
}

int Tuple::getPositionX() {
	return positionX;
}

int Tuple::getPositionY() {
	return positionY;
}

std::string Tuple::toString() {
	return std::to_string(positionX) + " " + std::to_string(positionY);
}

bool Tuple::equals(Tuple* other) {
	return this->positionX == other->positionX && this->positionY == other->positionY;
}