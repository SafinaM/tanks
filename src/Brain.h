#pragma once

#include "Tank.h"

struct Brain {
	Action chooseAction(Tank& tank);
	
	Action chooseAction(std::vector<Tank>& tanks);
	
	Direction chooseDirection();
	
};
