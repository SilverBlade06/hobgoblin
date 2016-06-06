#ifndef SRC_INVENTORY_H_
#define SRC_INVENTORY_H_

#include "Item.h"

class Inventory {
private:
	Item* items;

public:
	Inventory();
	virtual ~Inventory();
};

#endif /* SRC_INVENTORY_H_ */
