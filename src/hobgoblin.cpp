#include <iostream>
#include <stdio.h>
#include "player.h"

using namespace std;

Player player;

int main() {
	cout << "Hobgoblin starting..." << endl;
	cout << "Started!" << endl;
	cout << "Creating player..." << endl;
	cout << "Done!" << endl;
	cout << "Player location at" << endl;
	cout << "X: " << player.getLocationX() << endl;
	cout << "Y: " << player.getLocationY() << endl;
	cout << "HP: " << player.getHp() << endl;
	cout << "Inventory initialised to empty." << endl;
	cout << "Exiting..." << endl;
	cout << "Exited with exit code 0." << endl;

	return 0;
}
