#include "helpers.h"

namespace helper {
	uint32_t generateNumber(uint32_t downLimit, uint32_t upLimit) {
		std::random_device rd;
		std::uniform_int_distribution<uint32_t> distribution(downLimit, upLimit);
		return distribution(rd);
	}
	
}
