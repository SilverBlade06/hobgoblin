#include "Inventory.h"

#include "stdio.h"

	Inventory::Inventory() {
	    this->items = new Item[10];
	    Item* item;
		for (int i = 0; i < (sizeof(items)/sizeof(*items)); i++) {
			item = new Item();
			this->items[i] = *item;
	    }
    }

	Inventory::~Inventory() {
//		delete items;
	}
