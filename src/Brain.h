#pragma once

#include "Tank.h"
#include "TankEnums.h"

struct Brain {
	Action chooseAction(Tank& tank);
	
	void chooseActions(std::vector<Tank>& tanks);
	
	bool checkShoot(ShootProb upLimit);
	
	Direction chooseDirection();
	
};
