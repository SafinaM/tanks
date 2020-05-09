#include "Brain.h"
#include "helpers.h"
#include <enums.h>
#include <cstdint>
#include <iostream>

Action Brain::chooseAction(Tank& tank) {
	uint32_t numAction = helper::generateNumber(0, 2);
	return static_cast<Action>(numAction);
}

void Brain::chooseActions(std::vector<Tank>& tanks) {
	for (auto i = 0; i < tanks.size(); ++i ) {
		if (!tanks[i].isAlive)
			continue;
		const uint32_t shootNumber = helper::generateNumber(0, 16);
		// probability is about 1/16
		if (shootNumber == 1) {
			tanks[i].shoot();
		}
		
		auto direction = chooseDirection();
		tanks[i].setDirectionAndOrientation(direction);
	}
}

Direction Brain::chooseDirection() {
	auto num = helper::generateNumber(0, 3);
	return static_cast<Direction>(num);
}
