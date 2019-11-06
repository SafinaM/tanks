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
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	std::vector<std::vector<uint8_t>> points =
		{{1, 3, 1},
		 {1, 2, 1},
		 {1, 1, 1}};
	
	void move(const Direction direction);
	
	void print();

};