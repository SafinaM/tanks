#include "Map.h"
#include "Tank.h"
#include "Ammo.h"

#include <iostream>

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
