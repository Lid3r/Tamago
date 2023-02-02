#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Inventory.h"
#include "Item.h"

#define SLEEP_TIME 400
using namespace std;

void clrscr() {
	cout << "\033[2J\033[1;1H";
}


class Tamagotchi {
	string name;
	int age = 0, evolution = 0, health = 10, hunger = 5, mood = 5, money = 0;
	Inventory<Item> inventory;

	static Tamagotchi* tamago_;

	Tamagotchi(string name, int evolution, Inventory<Item> inv): name(name), evolution(evolution), inventory(inv) {}
	
public:

	void setData(int age, int health, int hunger, int mood, int money, Inventory<Item> inv) {
		this->age = age;
		this->health = health;
		this->hunger = hunger;
		this->mood = mood;
		this->money = money;
		this->inventory = inv;
	}

	string getName() {
		return name;
	}

	int getHunger() {
		return hunger;
	}

	int getHealth() {
		return health;
	}

	int getMood() {
		return mood;
	}

	int getAge() {
		return age;
	}

	int getEvolution() {
		return evolution;
	}

	int getMoney() {
		return money;
	}

	void setHunger(int value) {
		hunger = value <= 10 ? value : hunger;
	}

	void setHealth(int value) {
		health = value <= 10 ? value : health;
	}

	void setMood(int value) {
		mood = value <= 10 ? value : mood;
	}

	void addMoney(int value) {
		money += value;
	}

	void subtractMoney(int value) {
		money -= value;
	}

	bool isCanBuy(int value) {
		return (money - value) >= 0;
	}

	auto getInv() {
		return inventory;
	}

	void status() {
		cout << name;
		switch (evolution) {
		case 1: cout << " [Egg]\n"; break;
		case 2: cout << " [Rabbit]\n"; break;
		case 3: cout << " [Potato]\n"; break;
		}
		cout << "Age: " << age << " Days old\n";
		cout << "Money: " << money << "$" << endl;

		//print health
		cout << "Health: ";
		for (int i = 0; i < health; i++)
			cout << "+ ";
		for (int i = 0; i < (10 - health); i++)
			cout << "_ ";
		cout << "(" << health << "/" << 10 << ")";

		//print hunger
		cout << "\nHunger: ";
		for (int i = 0; i < hunger; i++)
			cout << "+ ";
		for (int i = 0; i < (10 - hunger); i++)
			cout << "_ ";
		cout << "(" << hunger << "/10)";

		//print mood
		cout << "\nMood: ";
		for (int i = 0; i < mood; i++)
			cout << "+ ";
		for (int i = 0; i < (10 - mood); i++)
			cout << "_ ";
		cout << "(" << mood << "/10)";
	}

	void animate() {
		string x, y;
		
		if (evolution == 1) { // Egg
			x = "Sprites/egg.txt";
			y = "Sprites/egg2.txt";
		}
		else if (evolution == 2) { // Rabbit
			x = "Sprites/rabbit.txt";
			y = "Sprites/rabbit2.txt";
		}
		else { // Potato
			x = "Sprites/potato.txt";
			y = "Sprites/potato2.txt";
		}

		for (int i = 0; i < 3; i++) {
			Sleep(SLEEP_TIME);
			clrscr(); // Clear screen
			//char s[255];
			ifstream in1;
			in1.open(x.c_str());
			cout << in1.rdbuf();
			status(); // Print screen

			Sleep(SLEEP_TIME);
			clrscr(); // Clear screen
			ifstream in2;
			in2.open(y.c_str());
			cout << in2.rdbuf();
			status(); // Print screen
		}

		cout << endl;

	}

	void displayStatic() {
		clrscr();
		ifstream sprite;
		switch (evolution) {
		case 1:
			sprite.open("Sprites/egg.txt");
			break;
		case 2:
			sprite.open("Sprites/rabbit.txt");
			break;
		case 3:
			sprite.open("Sprites/potato.txt");
			break;
		case 4:
			sprite.open("Sprites/rip.txt");
			break;
		default:
			//Throw exception
			return;
		}
		cout << sprite.rdbuf();
		status();
		return;
	}

	//Singleton things
	static Tamagotchi* GetInstance(string name, int evolution, Inventory<Item> inv);

	Tamagotchi(Tamagotchi& other) = delete;

	void operator=(const Tamagotchi&) = delete;
};

Tamagotchi* Tamagotchi::tamago_ = nullptr;

Tamagotchi* Tamagotchi::GetInstance(string name, int evolution, Inventory<Item> inv) {
	if (tamago_ == nullptr) {
		tamago_ = new Tamagotchi(name, evolution, inv);
	}
	return tamago_;
}


