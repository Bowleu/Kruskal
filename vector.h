#pragma once

template <class Number>
class vector
{
	int size;
	int capacity;
	Number* values;
	void resize();
public:
	vector();
	vector(int size);
	vector(const vector<Number>& v);
	Number& operator [] (int index);
	vector& operator = (const vector<Number>& v);
	bool isInArr(Number value);
	void push(Number value);
	int getLength();
	~vector();
};

template <class Number>
vector<Number>::vector() {
	size = 0;
	capacity = 4;
	values = new Number[capacity];
}


template <class Number>
vector<Number>::vector(int size) {
	this->size = size;
	capacity = size * 2;
	values = new Number[capacity];
}

template <class Number>
vector<Number>::~vector() {
	delete[] values;
}

template <class Number>
Number& vector<Number>::operator[] (int index) {
	return values[index];
}

template <class Number>
vector<Number>& vector<Number>::operator= (const vector<Number>& v) {
	if (&v != this) {
		this->~vector();
		size = v.size;
		capacity = v.capacity;
		values = new Number[capacity];
		for (int i = 0; i < size; i++)
			values[i] = v.values[i];
	}
	return *this;
}

template <class Number>
bool vector<Number>::isInArr(Number value) {
	for (int i = 0; i < size; i++) {
		if (values[i] == value)
			return 1;
	}
	return 0;
}

template <class Number>
void vector<Number>::resize() {
	Number* newValues = new Number[capacity * 2];
	for (int i = 0; i < size; i++) {
		newValues[i] = values[i];
	}
	delete[] values;
	capacity *= 2;
	values = newValues;
}

template <class Number>
void vector<Number>::push(Number value) {
	values[size] = value;
	size++;
	if (size == capacity)
		resize();
}

template <class Number>
vector<Number>::vector(const vector& v) {
	size = v.size;
	capacity = v.capacity;
	values = new Number[capacity];
	for (int i = 0; i < size; i++) {
		values[i] = v.values[i];
	}
}

template <class Number>
int vector<Number>::getLength() {
	return size;
}

