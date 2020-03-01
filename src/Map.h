#pragma once

struct Map {
	constexpr static uint32_t width = 400;
	constexpr static uint32_t height = 400;
	
	constexpr static uint32_t textColor = 15;

	
	uint8_t buffer[height][width] = {};
};

struct Stage {
	const char MAP_DATA[] =
		"#############"
		"#   @     . #"
		"#      .    #"
		"#############";
};