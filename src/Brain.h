#pragma once

#include "Tank.h"

struct Brain {
	void chooseAction(Tank& tank);
	
	void chooseAction(std::vector<Tank>& tanks);
	
	void chooseDirection();
	
};
