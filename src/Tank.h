#pragma once

#include "Shell.h"

#include <Figure.h>

#include <vector>
#include <cstdint>
#include <string>

struct Tank : Figure {
	
	enum Type : uint32_t {
		User1           = 2, // background color
		User2           = 3,
		EnemySimple     = 1,
		EnemyFast       = 4,
		EnemyStrong     = 5,
		EnemyStrongFast = 4,
		Smart           = 4
	};
	
	Tank(Type type = Type::EnemySimple);
	enum TankSymbol : char {
		Empty = ' ',
		Left = '/',
		Right = '\\',
	};
	using Figure::getPoints;
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const override;
	
	void shoot() {
	
	
	}
	
	void move(const Direction direction);
	
	void print();
	
	Type m_type = EnemySimple;
	std::vector<Shell> shells;
};