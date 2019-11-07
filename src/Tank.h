#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>

#include <Figure.h>

struct Tank : Figure {
	
	enum TankSymbol : char {
		Empty = 0,
		Cabin = 'O',
		Gun = 'o',
	};
	
	using Figure::getPoints;
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	
	void move(const Direction direction);
	
	void print();

};