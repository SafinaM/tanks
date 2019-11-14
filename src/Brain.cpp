#include "Brain.h"
#include "helpers.h"
#include <enums.h>
#include <cstdint>

void Brain::chooseAction(Tank& tank) {

}

void Brain::chooseAction(std::vector<Tank>& tanks) {

}

void Brain::chooseDirection() {
	
	auto num = helper::generateNumber(0, 3);
	Direction direction = static_cast<Direction>(num);
}
