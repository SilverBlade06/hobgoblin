#include <iostream>
#include <stdio.h>
#include "player.h"

using namespace std;

#include <GL/glut.h>

//Player player;

//void drawBox(void) {
//	int i;
//
//	for (i = 0; i < 6; i++) {
//		glBegin(GL_QUADS);
//		glNormal3fv(&n[i][0]);
//		glVertex3fv(&v[faces[i][0]][0]);
//		glVertex3fv(&v[faces[i][1]][0]);
//		glVertex3fv(&v[faces[i][2]][0]);
//		glVertex3fv(&v[faces[i][3]][0]);
//		glEnd();
//	}
//}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	drawBox();
	glutSwapBuffers();
}

void init() {

}

int main(int argc, char **argv) {

// Graphics initialization
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);

//	int windowId =
//			glutCreateWindow("Window title");

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("red 3D lighted cube");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
// Prevent closing instantly
//	getchar();

//	glutDestroyWindow(windowId);
//	cout << "Exiting..." << endl;
//	cout << "Exited with exit code 0." << endl;
//
//	getchar();

	return 0;
}
