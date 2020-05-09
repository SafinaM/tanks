#include <iostream>
#include "BaseAmmoTankFigure.h"

void BaseAmmoTankFigure::setOrientationTypeAndDirection(Orientation orientation) {
	m_orientation = orientation;
	
	auto it = directionByOrientation.find(orientation);
	if (it != directionByOrientation.end())
		m_direction = it->second;
//	setPoints(m_orientation);
}

void BaseAmmoTankFigure::setDirectionAndOrientation(Direction direction) {
	m_direction = direction;
	
	auto it = orientationByDirection.find(direction);
	if (it != orientationByDirection.end())
		m_orientation = it->second;
//	std::cout << "setDirectionAndOrientation" << std::endl;
//	setPoints(m_orientation);
}

void BaseAmmoTankFigure::setPoints(Orientation orientation) noexcept {
	points = getPoints(orientation);
}

const std::unordered_map<Orientation, Direction, std::hash<std::size_t>> BaseAmmoTankFigure::directionByOrientation = {
	{Orientation::First_0,    Direction::Up},
	{Orientation::Second_90,  Direction::Right},
	{Orientation::Third_180,  Direction::Down},
	{Orientation::Fourth_270, Direction::Left},

};
const std::unordered_map<Direction, Orientation, std::hash<std::size_t>> BaseAmmoTankFigure::orientationByDirection = {
	{Direction::Up,    Orientation::First_0},
	{Direction::Right, Orientation::Second_90},
	{Direction::Down,  Orientation::Third_180},
	{Direction::Left,  Orientation::Fourth_270},
};