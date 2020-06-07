#pragma once

#include <Figure.h>

#include <unordered_map>

struct BaseAmmoTankFigure : Figure {
	
	BaseAmmoTankFigure(Orientation orientation) : Figure(orientation) {};
	
	void setDirectionAndOrientation(Direction direction);
	void setPoints(Orientation orientation) noexcept;
	
	const static std::unordered_map<Direction, Orientation, std::hash<size_t>> orientationByDirection;
};


