#pragma once

#include <vector>
#include <string>
#include <exception>
using namespace std;

char normal[] = { 0x1b,'[','0',';','3','9','m',0 };
char green[] = { 0x1b,'[','0',';','3', '2','m',0 };

template <class T>
class Inventory {
	vector<T> inventory;
	int head = 0;
	int tail = 0;
	int max_size = 0;
	int current_size = 0;
	T empty_value;

public:
	Inventory<T>(int max_size) : max_size(max_size)	{};

	void setInventory(vector<T> vec) {
		inventory = vec;
	}

	//push at tail
	void push(T item) {
		if (is_full()) {
			throw exception("inventory is full");
		}


		inventory.push_back(item);
		//if at max size, go to zero
		tail = (tail + 1) % max_size;

		current_size++;
	}

	//pop from head
	T pop() {
		if (is_empty()) {
			throw exception("inventory is empty");
		}

		//Get item at head
		T item = inventory[head];

		inventory[head] = empty_value;

		head = (head + 1) % max_size;

		current_size--;

		return item;
	}

	T at(int index) {
		if (index < 0) {
			throw exception("Access out of bounds");
		}
		int properIndex = index % inventory.size();
		return inventory[index];
	}

	void printWithSelect(int index) {
		for (int i = 0; i < inventory.size(); i++) {
			if (index == i) {
				cout << green << at(i) << normal << " ";
			}
			else {
				cout << normal << at(i) << " ";
			}
		}
		cout << endl;
	}

	void print() {
		for (auto it = inventory.begin(); it != inventory.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}

	int size() {
		return current_size;
	}

	auto begin() {
		return inventory.begin();
	}

	auto end() {
		return inventory.end();
	}

	bool is_full() {
		return current_size == max_size;
	}

	bool is_empty() {
		return current_size == 0;
	}
};