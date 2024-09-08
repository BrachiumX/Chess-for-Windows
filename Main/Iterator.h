#pragma once

#include "LinkedListNode.h"

template <class T>
class Iterator {

private:
	LinkedListNode<T>* curr;

public:
	Iterator(LinkedListNode<T>* head) {
		curr = head;
	}

	T getNext() {
		LinkedListNode<T>* temp = curr;

		if(temp == nullptr) {
			delete this;
			return nullptr;
		}

		curr = curr->getNext();
		return temp->getValue();
	}
};
