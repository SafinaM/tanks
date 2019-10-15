#include "Tank.h"
#include <iostream>

void Tank::print() {
	for (uint32_t i = 0; i < buffer.size(); ++i) {
		for (uint32_t j = 0; j < buffer[0].size(); ++j) {
			std::cout << +buffer[i][j];
		}
		std::cout << std::endl;
	}
}

void move();
