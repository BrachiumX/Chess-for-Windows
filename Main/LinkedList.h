#pragma once

#include "LinkedListNode.h"
#include "Iterator.h"

template <class T>
class LinkedList {
private:
	LinkedListNode<T>* head;
	LinkedListNode<T>* tail;
	int size;

public:
	LinkedList() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~LinkedList() {
		LinkedListNode<T>* curr = head;
		LinkedListNode<T>* next;

		for(int i = 0; i < size; i++) {
			next = curr->getNext();
			delete curr;
			curr = next;
		}
	}

	void add(T value) {
		LinkedListNode<T>* temp;

		if(tail != nullptr) {
			temp = new LinkedListNode<T>(value, tail);
		}
		else {
			temp = new LinkedListNode<T>(value);
			head = temp;
		}

		tail = temp;
		size++;
	}

	void add(T value, int index) {
		LinkedListNode<T>* prev = this->getNode(index);

		LinkedList<T>* curr = new LinkedListNode(value, prev);

		size++;
	}

	void deleteNode(LinkedListNode<T>* node) {
		if(node == nullptr) {
			return;
		}

		if(size == 1) {
			tail = nullptr;
			head = nullptr;
		}

		else if(node == head) {
			head = node->getNext();
			node->getNext()->setPrev(nullptr);
		}

		else if(node == tail) {
			tail = node->getPrev();
			node->getPrev()->setNext(nullptr);
		}

		else {
			node->getPrev()->setNext(node->getNext());
			node->getNext()->setPrev(node->getPrev());
		}

		size--;
		delete node;
	}

	void deleteValue(T value) {
		LinkedListNode<T>* node = this->getValue(value);
		deleteNode(node);
	}

	bool contains(T value) {
		if(find(value) == -1) {
			return false;
		}
		return true;
	}

	bool contains(LinkedListNode<T>* node) {
		if(find(node) == -1) {
			return false;
		}
		return true;
	}

	int find(T value) {
		LinkedListNode<T>* curr = head;

		for(int i = 0; i < size; i++) {

			if(curr->getValue() == value) {
				return i;
			}

			curr = curr->getNext();
		}

		return -1;
	}

	int find(LinkedListNode<T>* node) {

		LinkedListNode<T>* curr = head;

		for(int i = 0; i < size; i++) {

			if(curr == node) {
				return i;
			}

			curr = curr->getNext();
		}

		return -1;
	}

	T get(int index) {
		if(index < 0 || index > size) {
			return nullptr;
		}

		LinkedListNode<T>* curr = head;

		for(int i = 0; i < index; i++) {
			curr = curr->getNext();
		}

		return curr->getValue();
	}

	LinkedListNode<T>* getNode(int index) {
		LinkedListNode<T>* curr = head;

		for(int i = 0; i < index; i++) {
			curr = curr->getNext();
		}

		return curr;
	}

	LinkedListNode<T>* getValue(T value) {

		LinkedListNode<T>* curr = head;

		for(int i = 0; i < size; i++) {

			if(curr->getValue() == value) {
				return curr;
			}

			curr = curr->getNext();
		}

		return nullptr;
	}

	int getSize() {
		return this->size;
	}

	Iterator<T>* getIterator() {
		Iterator<T>* iterator = new Iterator<T>(head);
		return iterator;
	}
};