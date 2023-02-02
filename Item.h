#pragma once
#include <string>
using namespace std;

class Item
{
	string itemName = "";
	int effectID = 0;
	int effectValue = 0;
public:
	Item(string name, int ID, int value) : itemName(name), effectID(ID), effectValue(value) {};
	Item() {};


	string getName() {
		return itemName;
	}

	pair<int, int> getEffect() {
		return make_pair(effectID, effectValue);
	}

	friend ostream& operator<<(ostream& os, const Item& item);
};

ostream& operator<<(ostream& os, const Item& item)
{
	os << item.itemName << "     ";
	return os;
}
