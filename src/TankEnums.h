#pragma once

#include <cstdint>

enum struct Action: uint32_t {
	Move = 0,
	Shoot,
	ChooseDirection
};

enum struct OpponentMode: uint32_t {
	Random = 0,
	User,
	ChooseDirection,
};
