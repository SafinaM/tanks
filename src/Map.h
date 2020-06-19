#pragma once

#include "Tank.h"
#include "Tile.h"

#include <Point.h>
#include <Singletone.h>
#include <BoardBase.h>

#include <cstdint>
#include <assert.h>
#include <deque>

constexpr static uint32_t mapWidth = 40;
constexpr static uint32_t mapHeight = 20;

struct Map : BoardBase {
	
	Map(uint32_t width, uint32_t height) : BoardBase(width, height),
	waveBuffer(m_heightBoard, std::vector<int>(m_widthBoard, 0)) {
		std::cout << std::endl;
	}
	
	Map(const std::vector<std::vector<uint8_t>>& buffer) :
	BoardBase(buffer),
	waveBuffer(m_heightBoard, std::vector<int>(m_widthBoard, 0)) {}
	
	~Map() = default;
	
	void setXY(uint32_t x, uint32_t y) noexcept;
	
	uint32_t getXOrigin() const noexcept;
	uint32_t getYOrigin() const noexcept;
	
	bool allowMove(Direction direction, Figure &figure) const;
	
	void crossWithAmmo(Tank &tank);
	
	bool
	isCrossedTankWithBuffer(
		const std::vector<std::vector<uint8_t>>& points,
		int xOffset,
		int yOffset) const;
	
	void
	crossAmmoWithBuffer(const std::vector<std::vector<uint8_t>> &points,
		int xOffset,
		int yOffset,
		Ammo& shell);
	
	Tile getTileType(uint32_t x, uint32_t y) const;
	
	// temp methods
	void buildWave(const Point& startPoint, const Point& endPoint);
	
	void fillWaveBuffer(const Point& start);
	
	std::deque<Point> findPath(const Point &start, const Point &finish);
	
	void initWaveBuffer();
	
	private:
	uint32_t m_xOrigin = 0;
	uint32_t m_yOrigin = 0;
	std::vector<std::vector<int>> waveBuffer;
	




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

