#include "Tank.h"
#include <iostream>
#include <enums.h>

void Tank::print() {
	for (uint32_t i = 0; i < points.size(); ++i) {
		for (uint32_t j = 0; j < points[0].size(); ++j) {
			std::cout << +points[i][j];
		}
		std::cout << std::endl;
	}
}

void Tank::move(const Direction direction) {
	{
		switch (direction) {
			case Direction::Left:
				points =
					{{1, 1, 1},
					 {3, 2, 1},
					 {1, 1, 1}};
				--m_offsetX;
				break;
			case Direction::Right:
				points =
					{{1, 1, 1},
					 {1, 2, 3},
					 {1, 1, 1}};
				++m_offsetX;
			case Direction::Up:
				points =
					{{1, 3, 1},
					 {1, 2, 1},
					 {1, 0, 1}};
				--m_offsetY;
				break;
			case Direction::Down:
				points =
					{{1, 1, 1},
					 {1, 2, 1},
					 {1, 3, 1}};
				++m_offsetY;
				break;
		}
	}
}

std::vector<std::vector<uint8_t>> Tank::getPoints(Orientation orientation) const {

}

