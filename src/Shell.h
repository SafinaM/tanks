#pragma once

#include <Figure.h>


// explosive artillery projectile or bomb.
struct Shell : Figure {
	
	// speed, maybe it will be milliseconds
	enum Type : uint32_t {
		SlowSingle        = 0,
		FastSingle        = 1,
		FastDouble        = 2,
		FastDoubleStrong  = 3,
		SupberFastNStrong = 4,
	};
	
	Shell(Type type = Type::SlowSingle);
	enum GunSymbol : char {
		Empty = ' ',
		Left = '/',
		Right = '\\',
	};
	using Figure::getPoints;
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const override;
	
	void move(const Direction direction);
	
	void print();
	
	Type m_type = SlowSingle;
	
};
