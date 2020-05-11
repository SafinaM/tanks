#include <iostream>
#include "BaseAmmoTankFigure.h"

void BaseAmmoTankFigure::setDirectionAndOrientation(Direction direction) {
	m_direction = direction;
	
	auto it = orientationByDirection.find(direction);
	if (it != orientationByDirection.end())
		m_orientation = it->second;
}

void BaseAmmoTankFigure::setPoints(Orientation orientation) noexcept {
	points = getPoints(orientation);
}

const std::unordered_map<Direction, Orientation, std::hash<std::size_t>> BaseAmmoTankFigure::orientationByDirection = {
	{Direction::Up,    Orientation::First_0},
	{Direction::Right, Orientation::Second_90},
	{Direction::Down,  Orientation::Third_180},
	{Direction::Left,  Orientation::Fourth_270},
};