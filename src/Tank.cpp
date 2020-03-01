#include "Tank.h"
#include <iostream>
#include <enums.h>
#include <cassert>

void Tank::print() {
	for (uint32_t i = 0; i < points.size(); ++i) {
		for (uint32_t j = 0; j < points[0].size(); ++j) {
			std::cout << +points[i][j];
		}
		std::cout << std::endl;
	}
}

Tank::Tank(Type type) : m_type(type) {
	m_orientation = Orientation::First_0;
	points = getPoints(m_orientation);
	m_Color = m_type;
}

void Tank::move(const Direction direction) {
	switch (direction) {
		case Direction::Up:
			m_orientation = Orientation::First_0;
			--m_offsetY;
			break;
		case Direction::Down:
			m_orientation = Orientation::Third_180;
			++m_offsetY;
			break;
		case Direction::Left:
			--m_offsetX;
			m_orientation = Orientation::Fourth_270;
			break;
		case Direction::Right:
			m_orientation = Orientation::Second_90;
			++m_offsetX;
	}
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> Tank::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0:
			return
				{{2, 3},
				 {1, 1}};
		case Orientation::Second_90:
			return
				{{1, 3},
				 {1, 2}};
		case Orientation::Third_180:
			return
				{{1, 1},
				 {3, 2}};
		case Orientation::Fourth_270:
			return
				{{2, 1},
				 {3, 1}};
	}
}
