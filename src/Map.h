#pragma once

#include "Tank.h"

#include <Singletone.h>
#include <BoardBase.h>

#include <cstdint>
#include <assert.h>

constexpr static uint32_t mapWidth = 40;
constexpr static uint32_t mapHeight = 20;

struct Map : BoardBase {
	
	Map(uint32_t width, uint32_t height) : BoardBase(width, height) {}
	
	Map(const std::vector<std::vector<uint8_t>>& buffer) :
	BoardBase(buffer) {}
	
	~Map() = default;
	
	void setXY(uint32_t x, uint32_t y) noexcept;
	
	uint32_t getXOrigin() const noexcept;
	uint32_t getYOrigin() const noexcept;
	
	virtual bool allowMove(Direction direction, const Figure &figure) const override;
	
	
	private:
	uint32_t m_xOrigin = 0;
	uint32_t m_yOrigin = 0;
	
	
//	= {
//		{wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww},
//		{wee                             ee                                  eew},
//		{w                                                                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w                                                                     w},
//		{w                                                                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w               ###     ###     ###    ###    ###                     w},
//		{w                                                                     w},
//		{w                                                                     w},
//		{w                             #######                                 w},
//		{w                             #######                                 w},
//		{w                          uu ##ccc## uu                              w},
//		{wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww}};
	

};

enum class TileAmmoPenetrationType : uint32_t {
	TAP_DESTROYABLE = 0,
	TAP_NOT_DESTROYABLE,
	TAP_FLY_THROUGH,
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

enum class TileType : uint32_t {
	TT_BRICK = 0,
	TT_ARMOR,
	TT_GRASS,
	TT_WATER,
};

struct TileTypeHash
{
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

static std::unordered_map<TileType, Tile, TileTypeHash> tileByType {
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
	};

static Tile getTileByType(const TileType tileType) {
	auto it = tileByType.find(tileType);
	assert(it != tileByType.end());
	return it->second;
};
