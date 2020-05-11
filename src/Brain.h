#pragma once

#include "Tank.h"

struct Brain {
	Action chooseAction(Tank& tank);
	
	void chooseActions(std::vector<Tank>& tanks);
	
	bool checkShoot();
	
	Direction chooseDirection();
	
};
