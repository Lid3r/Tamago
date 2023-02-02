#include <fstream>

#include "Tamagotchi.h"
#include <algorithm>
#include <map>
#include <conio.h>
constexpr int INV_SIZE = 5;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

using namespace std;

Item bread("Bread", 1, 1);
Item candy("Candy", 2, 3);
Item meat("Meat", 3, 5);
map<int, Item> items = { {1, bread}, {2, candy}, {3, meat} };

template <class T>
void printVector(vector<T>& vec) {
    for_each(vec.begin(), vec.end(), [](T element) {cout << element << " "; });

    cout << endl;
}

vector<Item> convertToItems(vector<string>& vec) {
    vector<Item> itemsForInv;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        Item currentItem = items[stoi(*it)];
        itemsForInv.push_back(currentItem);
    }
    return itemsForInv;
}

vector<string> split(string line, char delimiter) {
    vector<string> tokens;
    size_t pos = 0;

    while ((pos = line.find(delimiter)) != std::string::npos) {
        tokens.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    //last element
    tokens.push_back(line);
    return tokens;
}

void feed(Tamagotchi* tama) {
    tama->displayStatic(); 
    cout << endl;
    bool notEnter = true;
    int choice = 0;
    while (notEnter) {
        clrscr();
    tama->displayStatic(); 
        tama->getInv().printWithSelect(choice);
        int c = 0;
        switch ((c = _getch())) {
        case KEY_LEFT:
            choice = choice-- != 0 ? choice-- : 0;
            break;
        case KEY_RIGHT:
            choice++;
            cout << endl << "Right" << endl;  // key right
            break;
        case ENTER:
            notEnter = false;
            break;
        }


    }
}

void menu(Tamagotchi* tama) {
    bool breaker = true;
    while (breaker) {
        cout << "What would you like to do?" << endl;
        cout << "1. Feed" << endl;
        cout << "2. Play" << endl;
        cout << "3. Shop" << endl;
        cout << "4. Pass time" << endl;
        cout << "5. Close game" << endl;
        int choice = 0;
        cin >> choice;
        switch (choice)
        {
        case 1:
            feed(tama);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            breaker = false;
            break;

        default:
            break;
        }
    }
}

int main() {
    Inventory<Item> inv(INV_SIZE);
    fstream database("db.txt");

    if (database.good()) {
        string line;
        bool isFirstLine = true;
        vector<string> tokens;
        //No previous game has been saved
        getline(database, line);
        tokens = split(line, ',');
        
        if (tokens.size() != 3) {
            //throw exception
        }
        
        vector<string> inventoryFromFile = split(tokens[2], '|');

        if (inventoryFromFile.size() > INV_SIZE) {
            //Throw exception
        }

        inv.setInventory(convertToItems(inventoryFromFile));

        Tamagotchi* tama = Tamagotchi::GetInstance(tokens[0], stoi(tokens[1]), inv);
        tama->displayStatic();
        //inv = tama->getInv();

        //for (auto it = inv.begin(); it != inv.end(); it++) {
        //    cout << *it;
        //}
      
        menu(tama);

        cout << endl;
        getline(database, line);
        tokens = split(line, ',');

        
    }


}

