#pragma once
#include <vector>

#include <cstdint>

struct Tank {
	int m_XOffset = 0;
	int m_yOffset = 0;
	enum Direction: uint32_t {
		Left  = 0,
		Right = 1,
		Up    = 2,
		Down  = 3
	};
	
	std::vector<std::vector<uint8_t>> buffer =
		{{0, 3, 0},
		 {1, 1, 1},
		 {1, 2, 1},
		 {1, 1, 1}};
	
	void move(const Direction direction) {
		
		switch (direction) {
			case Left:
				buffer =
					{{1, 1, 1, 0},
					 {1, 2, 1, 3},
					 {1, 1, 1, 0}};
				--m_XOffset;
				break;
			case Right:
				buffer =
					{{0, 1, 1, 1},
					 {3, 1, 2, 1},
					 {0, 1, 1, 1}};
				++m_XOffset;
			case Up:
				buffer =
					{{0, 3, 0},
					 {1, 1, 1},
					 {1, 2, 1},
					 {1, 1, 1}};
				--m_yOffset;
				break;
			case Down:
				buffer =
					{{1, 1, 1},
					 {1, 2, 1},
					 {1, 1, 1},
					 {0, 3, 0}};
				++m_yOffset;
				break;
		}
	}
	
	void print() {
	
	}
	

};

