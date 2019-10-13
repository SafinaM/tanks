#pragma once
#include <vector>

#include <cstdint>

struct Tank {
	enum Direction: uint32_t {
		Left  = 0,
		Right = 1,
		Up    = 2,
		Down  = 3
	};
	
	std::vector<std::vector<uint8_t>> buffer =
		{{0, 1, 0},
		 {1, 1, 1},
		 {1, 2, 1},
		 {1, 1, 1}};
	
	void print();
	

};

