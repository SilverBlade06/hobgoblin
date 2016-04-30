#include <iostream>
#include <stdio.h>
#include "player.h"

using namespace std;

//Player player;

int main() {
	cout << "Hobgoblin starting..." << endl;
	cout << "Started!" << endl;
	cout << "Creating player..." << endl;
	Player* player = new Player();
	cout << "Done!" << endl;
	cout << "Player location at" << endl;
	cout << "X: " << player->getLocationX() << endl;
	cout << "Y: " << player->getLocationY() << endl;
	cout << "HP: " << player->getHp() << endl;
	cout << "Inventory initialized to empty." << endl;
	cout << "Exiting..." << endl;
	cout << "Exited with exit code 0." << endl;

	return 0;
}
