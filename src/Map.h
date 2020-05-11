#pragma once

#include "Tank.h"

#include <Singletone.h>
#include <BoardBase.h>

#include <cstdint>

constexpr static uint32_t mapWidth = 40;
constexpr static uint32_t mapHeight = 20;

struct Map : BoardBase {
	
	Map(uint32_t width, uint32_t height) : BoardBase(width, height) {}
	
	Map(
		uint32_t width,
		uint32_t height,
		const std::vector<std::vector<uint8_t>>& buffer) :
	BoardBase(width, height, buffer) {}
	
	~Map() = default;
	
	void setXY(uint32_t x, uint32_t y) noexcept;
	
	uint32_t getXOrigin() const noexcept;
	uint32_t getYOrigin() const noexcept;
	
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

struct Tile {
	BackgroundColor backgroundColor;
	TextColor textColor;
	char textSymb;
	bool tankPatency;
	uint32_t ammoPenetration;
	
};
