#include "Map.h"
#include "Tank.h"
#include "Ammo.h"

#include <iostream>
#include <deque>

void Map::setXY(uint32_t x, uint32_t y)  noexcept {
	m_xOrigin = x;
	m_yOrigin = y;
}

uint32_t Map::getXOrigin() const noexcept {
	return m_xOrigin;
}

uint32_t Map::getYOrigin() const noexcept {
	return m_yOrigin;
}

bool Map::allowMove(Direction direction, Figure &figure) const {
	const auto& points = figure.getPoints();
	int xOffset = figure.getXOffset();
	int yOffset = figure.getYOffset();
	
	incrementOrigins(direction, xOffset, yOffset);
	
	if (isCrossedFigureWithWalls(points, xOffset, yOffset))
		return false;
	
	return !isCrossedTankWithBuffer(points, xOffset, yOffset);
}

void Map::crossWithAmmo(Tank &tank) {
	for (auto& shell: tank.ammo) {
		if (!shell.isActive())
			continue;
		const auto& points = shell.getPoints();
		int xOffset = shell.getXOffset();
		int yOffset = shell.getYOffset();
		const Direction direction = shell.getDirection();
		incrementOrigins(direction, xOffset, yOffset);
		
		if (isCrossedFigureWithWalls(points, xOffset, yOffset)) {
			shell.setActiveFlag(false);
			continue;
		}
		crossAmmoWithBuffer(points, xOffset, yOffset, shell);
	}
}

bool
Map::isCrossedTankWithBuffer(
	const std::vector<std::vector<uint8_t>>& points,
	int xOffset,
	int yOffset) const {
	
	for (auto y = 0; y < points.size(); ++y) {
		for (auto x = 0; x < points[0].size(); ++x) {
			const auto& tile = getTileType(x + xOffset, y + yOffset);
			// if buffer points and figure points are intersected and tank can pass
			if (points[y][x] && buffer[y + yOffset][x + xOffset] && !tile.tankPatency) {
				return true;
			}
		}
	}
	return false;
}

void
Map::crossAmmoWithBuffer(
	const std::vector<std::vector<uint8_t>>& points,
	int xOffset,
	int yOffset,
	Ammo& shell) {
	for (auto y = 0; y < points.size(); ++y) {
		for (auto x = 0; x < points[0].size(); ++x) {
			const auto& tile = getTileType(x + xOffset, y + yOffset);
			// if buffer points and figure points are intersected and ammo can pass it
			if (points[y][x] && buffer[y + yOffset][x + xOffset]) {
				switch (tile.ammoPenetration) {
					case TileAmmoPenetrationType::TAP_DESTROYABLE:
						buffer[y + yOffset][x + xOffset] = 0;
						shell.setActiveFlag(false);
						break;
					case TileAmmoPenetrationType::TAP_NOT_DESTROYABLE:
						shell.setActiveFlag(false);
						break;
					case TileAmmoPenetrationType::TAP_FLY_THROUGH:
						continue;
				}
			}
		}
	}
}

Tile Map::getTileType(uint32_t x, uint32_t y) const {
	return getTileByType(static_cast<TileType>(buffer[y][x]));
}

// tmp
void Map::buildWave(const Point& startPoint, const Point& endPoint) {
	initWaveBuffer();
	fillWaveBuffer(startPoint);
	auto trace = findPath(startPoint, endPoint);
	std::cout << std::endl;

}

void Map::fillWaveBuffer(const Point& start) {
	// mark point as -1, we will not come there again
	waveBuffer[start.y][start.x] = -1;
	
	debugPrint(waveBuffer);
	std::deque<Point> deq;
	deq.push_back(start);
	uint32_t weight = 1;
	bool lastMarked = false;
	while(!deq.empty() && !lastMarked) {
		++weight;
		for (const auto& center: deq) {
			for (const auto& point: neumannPoints) {
				if (center.x + point.x >= 0 &&
					center.y + point.y >= 0 &&
					center.x + point.x < m_widthBoard &&
					center.y + point.y < m_heightBoard &&
					waveBuffer[center.y + point.y][center.x + point.x] == 1) {
						waveBuffer[center.y + point.y][center.x + point.x] = weight;
						deq.push_back(Point(center.x + point.x, center.y + point.y));
				}
			}
			
			debugPrint(waveBuffer);
			deq.pop_front();
		}
	}
	waveBuffer[start.y][start.x] = 1;
}

std::deque<Point> Map::findPath(const Point &start, const Point &finish) {
	std::deque<Point> trace;
	// init current point
	Point current = Point(finish.x, finish.y);
	
	while (waveBuffer[current.y][current.x] != 1) {
		for (const auto& point: neumannPoints) {
			const Point nextPoint(current.x + point.x, current.y + point.y);
			
			if (waveBuffer[current.y][current.x] &&
			waveBuffer[current.y][current.x] == waveBuffer[nextPoint.y][nextPoint.x] + 1) {
				trace.push_front(current);
				waveBuffer[current.y][current.x] = -1;
				current = Point(nextPoint.x, nextPoint.y);
				debugPrint(waveBuffer);
				break;
			}
		}
	}
	trace.push_front(Point(start.x, start.y));
	
	return trace;
}


void Map::initWaveBuffer() {
	for (uint8_t y = 0; y < m_heightBoard; ++y) {
		for (uint8_t x = 0; x < m_widthBoard; ++x) {
			waveBuffer[y][x] = buffer[y][x];
		}
	}
	
	for (uint8_t y = 0; y < m_heightBoard; ++y) {
		for (uint8_t x = 0; x < m_widthBoard; ++x) {
			const auto& tileType = static_cast<TileType>(waveBuffer[y][x]);
			if (!waveBuffer[y][x] ||
				tileType == TileType::TT_USER_TANK_PLACE_BIRTH ||
				tileType == TileType::TT_OPPSITE_TANK_PLACE_BIRTH)
				waveBuffer[y][x] = 1;
			else {
				waveBuffer[y][x] = 0;
			}
		}
		std::cout << std::endl;
	}
}



