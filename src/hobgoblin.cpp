#include <iostream>
#include <stdio.h>
#include "player.h"

using namespace std;

#include <GL/glut.h>

//Player player;

int main(int argc, char **argv) {

// Graphics initialization
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);

	int windowId = glutCreateWindow("Window title");

// Logging
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

// Prevent closing instantly
	getchar();

	glutDestroyWindow(windowId);
	cout << "Exiting..." << endl;
	cout << "Exited with exit code 0." << endl;

	getchar();

	return 0;
}
