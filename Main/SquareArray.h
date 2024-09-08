#pragma once

template <class T>
class SquareArray {

private:
	T array[8][8];
	T stored;
	T toBeMoved;
	int oldPositionX;
	int oldPositionY;
	int newPositionX;
	int newPositionY;

public:
	SquareArray() {
		memset(array, 0, sizeof(array));
	}

	void set(T value, int positionX, int positionY) {
		if(!out(positionX, positionY)) {
			array[positionX][positionY] = value;
		}
	}

	T get(int positionX, int positionY) {
		if(out(positionX, positionY)) {
			return nullptr;
		}

		return array[positionX][positionY];
	}

	bool out(int positionX, int positionY) {
		return positionX > 7 || positionX < 0 || positionY > 7 || positionY < 0;
	}

	bool out(int position) {
		return position > 7 || position < 0;
	}

	void moveTemp(int oldPositionX, int oldPositionY, int newPositionX, int newPositionY) {
		stored = get(newPositionX, newPositionY);
		toBeMoved = get(oldPositionX, oldPositionY);

		this->oldPositionX = oldPositionX;
		this->oldPositionY = oldPositionY;
		this->newPositionX = newPositionX;
		this->newPositionY = newPositionY;

		set(toBeMoved, newPositionX, newPositionY);
		set(nullptr, oldPositionX, oldPositionY);
	}

	void resetTemp() {
		set(stored, newPositionX, newPositionY);
		set(toBeMoved, oldPositionX, oldPositionY);

		stored = nullptr;
		toBeMoved = nullptr;
	}
};