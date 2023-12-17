#pragma once

using namespace std;

template<class T2>
struct Node {
	Node <T2>() {};
	Node <T2>(Node* n, T2 v) : next(n), value(v) {};
	Node* next;
	T2 value;
};

template <class T1, class T2>
class Map {
	Node<T2>** values;
	size_t size;
	size_t filledElements;
	void arrResize() {
		Node<T2>** newValues = new Node<T2>*[size * 2];
		for (int i = 0; i < size * 2; i++) {
			if (i < size) {
				newValues[i] = values[i];
			}
			else {
				newValues[i] = nullptr;
			}
		}
		delete[] values;
		values = newValues;
		size *= 2;
	}
public:
	Map<T1, T2>() {
		size = 8;
		values = new Node<T2>*[size];
		for (int i = 0; i < size; i++) {
			values[i] = nullptr;
		}
		filledElements = 0;
	}
	void insert(T1 key, T2 value) {
		size_t hashValue = hash<T1>{}(key);
		size_t index = hashValue % size;
		if (values[index] == nullptr) {
			filledElements++;
			values[index] = new Node<T2>(nullptr, value);
		}
		else {
			Node<T2>* currNode = values[index];
			while (currNode->next) {
				currNode = currNode->next;
			}
			Node<T2>* nextNode = new Node<T2>(nullptr, value);
			currNode->next = nextNode;
		}
		if ((float)filledElements / size >= 0.6) {
			arrResize();
		}
	}
	T2& operator [] (T1& key) {
		size_t hashValue = hash<T1>{}(key);
		size_t index = hashValue % size;
		return values[index]->value;
	}
	~Map() {
		for (int i = 0; i < size; i++) {
			Node<T2>* curr = values[i];
			while (curr) {
				Node<T2>* next = curr->next;
				delete curr;
				curr = next;
			}
		}
	}
};