#include "inventory.h"
#include "player.h"

	short Player::getHp(){
		return hp;
	}

	void Player::setHp(short hp) {
		this->hp = hp;
	}

	Inventory* Player::getInventory(){
		return inventory;
	}

	void Player::setInventory(Inventory &inventory) {
		this->inventory = &inventory;
	}

	int Player::Player::getLocationX(){
		return locationX;
	}

	void Player::setLocationX(int locationX) {
		this->locationX = locationX;
	}

	int Player::getLocationY(){
		return locationY;
	}

	void Player::setLocationY(int locationY) {
		this->locationY = locationY;
	}

	Player::Player() : inventory(){
			this->hp = 100;
			this->locationX = 0;
			this->locationY = 0;
//			this->inventory = new Inventory();
	}

	Player::Player(short hp, int locationX, int locationY, Inventory &inventory) {
		this->hp = hp;
		this->locationX = locationX;
		this->locationY = locationY;
		this->inventory = &inventory;
	}
