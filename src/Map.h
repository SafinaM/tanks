#pragma once

#include "Tank.h"
#include "Tile.h"

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
	
	bool allowMove(Direction direction, const Figure &figure) const;
	
	bool allowMoveAmmo(Direction direction, const std::unique_ptr<Figure> &figure);
	
	bool
	isCrossedTankWithBuffer(
		const std::vector<std::vector<uint8_t>>& points,
		int xOffset,
		int yOffset) const;
	
	void
	crossAmmoWithBuffer(
		const std::unique_ptr<Figure> &figure,
		int xOffset,
		int yOffset);
	
	Tile getTileType(uint32_t x, uint32_t y) const;
	
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

