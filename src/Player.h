#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Inventory.h"

class Player {
private:
	short hp;
	int locationX;
	int locationY;
	Inventory* inventory;

public:
	short getHp();
	void setHp(short hp);
	Inventory* getInventory();
	void setInventory(Inventory &inventory);
	int getLocationX();
	void setLocationX(int locationX);
	int getLocationY();
	void setLocationY(int locationY);

	Player();
	Player(short hp, int locationX, int locationY, Inventory &inventory);
};


#endif /* SRC_PLAYER_H_ */
