#pragma once


#include <enums.h>

#include <cstdint>
#include <cassert>

enum class TileType : uint32_t {
	TT_EMPTY = 0,
	TT_BRICK = 1,
	TT_ARMOR = 2,
	TT_GRASS = 3,
	TT_WATER = 4,
	TT_USER_TANK_PLACE_BIRTH = 5,
	TT_OPPSITE_TANK_PLACE_BIRTH = 6,
	TT_EAGLE = 7,
};

enum class TileAmmoPenetrationType : uint32_t {
	TAP_DESTROYABLE = 0,
	TAP_NOT_DESTROYABLE,
	TAP_FLY_THROUGH,
};

struct TileTypeHash {
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

struct Tile {
	BackgroundColor backgroundColor;
	TextColor textColor;
	char textSymb;
	bool tankPatency;
	TileAmmoPenetrationType ammoPenetration;
	
	Tile(
		BackgroundColor bcColor,
		TextColor tColor,
		char symb,
		bool canMove,
		TileAmmoPenetrationType amPenetraion) :
		backgroundColor(bcColor),
		textColor(tColor),
		textSymb(symb),
		tankPatency(canMove),
		ammoPenetration(amPenetraion) {}
};

static std::unordered_map<TileType, Tile, TileTypeHash> tileByType {
	
	{TileType::TT_EMPTY, Tile(
		BackgroundColor::BC_BLACK,
		TextColor::TC_BLACK,
		' ',
		true,
		TileAmmoPenetrationType::TAP_FLY_THROUGH)},
	{TileType::TT_BRICK, Tile(
		BackgroundColor::BC_GRAY,
		TextColor::TC_BLACK_BOLD,
		'-',
		false,
		TileAmmoPenetrationType::TAP_DESTROYABLE)},
	{TileType::TT_ARMOR, Tile(
		BackgroundColor::BC_GRAY,
		TextColor::TC_BLACK_BOLD,
		'#',
		false,
		TileAmmoPenetrationType::TAP_NOT_DESTROYABLE)},
	{TileType::TT_GRASS, Tile(
		BackgroundColor::BC_GREEN,
		TextColor::TC_GREEN_BOLD,
		'^',
		true,
		TileAmmoPenetrationType::TAP_FLY_THROUGH)},
	{TileType::TT_WATER, Tile(
		BackgroundColor::BC_BLUE,
		TextColor::TC_LIGHT_BLUE,
		'~',
		false,
		TileAmmoPenetrationType::TAP_FLY_THROUGH)},
	{TileType::TT_USER_TANK_PLACE_BIRTH, Tile(
		BackgroundColor::BC_BLACK,
		TextColor::TC_BLACK,
		' ',
		true,
		TileAmmoPenetrationType::TAP_FLY_THROUGH)},
	{TileType::TT_OPPSITE_TANK_PLACE_BIRTH, Tile(
		BackgroundColor::BC_BLACK,
		TextColor::TC_BLACK,
		' ',
		true,
		TileAmmoPenetrationType::TAP_FLY_THROUGH)},
	{TileType::TT_EAGLE, Tile(
		BackgroundColor::BC_RED,
		TextColor::TC_BLACK,
		'!',
		true,
		TileAmmoPenetrationType::TAP_DESTROYABLE)},
};

static Tile getTileByType(const TileType tileType) {
	auto it = tileByType.find(tileType);
	assert(it != tileByType.end());
	return it->second;
};


