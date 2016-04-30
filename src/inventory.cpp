#include "inventory.h"

	Inventory::Inventory() {
	    this->items = new char*[10];
	    //int i = 0;
	    for (int i = 0; i < (sizeof(items)/sizeof(*items)); i++) {
		    this->items[i] = 0;
	    }
    }

	Inventory::~Inventory() {
	//	delete items;
	}

//
//Inventory::
//
//Inventory::
//
