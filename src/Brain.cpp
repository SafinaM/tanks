#include "Brain.h"
#include "helpers.h"
#include <enums.h>
#include <cstdint>

Action Brain::chooseAction(Tank& tank) {
	uint32_t numAction = helper::generateNumber(0, 1);
	Action action = static_cast<Action>(numAction);
}

Action Brain::chooseAction(std::vector<Tank>& tanks) {

}

Direction Brain::chooseDirection() {
	
	auto num = helper::generateNumber(0, 3);
	return static_cast<Direction>(num);
}
