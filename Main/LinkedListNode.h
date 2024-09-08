#pragma once

#include <iostream>

using namespace std;

template <class T>
class LinkedListNode {
private:
	LinkedListNode<T>* prev;
	LinkedListNode<T>* next;

	T value;

public:
	LinkedListNode(T value) {
		this->value = value;
		this->prev = nullptr;
		this->next = nullptr;
	}
	LinkedListNode(T value, LinkedListNode<T>* node) {
		this->value = value;
		this->prev = node;
		this->next = prev->getNext();
		node->setNext(this);
	}
	~LinkedListNode() {
		if(value != nullptr) {
			delete value;
		}
	}

	void setPrev(LinkedListNode<T>* node) {
		this->prev = node;
	}
	void setNext(LinkedListNode<T>* node) {
		this->next = node;
	}

	LinkedListNode<T>* getPrev() {
		return this->prev;
	}
	LinkedListNode<T>* getNext() {
		return this->next;
	}

	T getValue() {
		return this->value;
	}

	void setValue(T value) {
		this->value = value;
	}

	void deleteAndSetValue(T value) {
		delete this->value;
		this->value = value;
	}
};
