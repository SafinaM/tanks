#include "Brain.h"
#include "helpers.h"
#include <enums.h>
#include <cstdint>

Action Brain::chooseAction(Tank& tank) {
	uint32_t numAction = helper::generateNumber(0, 2);
	return static_cast<Action>(numAction);
}

std::vector<Action> Brain::chooseActions(std::vector<Tank>& tanks) {

}

Direction Brain::chooseDirection() {
	
	auto num = helper::generateNumber(0, 3);
	return static_cast<Direction>(num);
}
