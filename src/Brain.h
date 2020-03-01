#pragma once

#include "Tank.h"

struct Brain {
	Action chooseAction(Tank& tank);
	
	std::vector<Action> chooseActions(std::vector<Tank>& tanks);
	
	Direction chooseDirection();
	
};
