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

bool Map::allowMove(Direction direction, const Figure &figure) const {
	const auto& points = figure.getPoints();
	int xOffset = figure.getXOffset();
	int yOffset = figure.getYOffset();
	
	incrementOrigins(direction, xOffset, yOffset);
	
	if (isCrossedFigureWithWalls(points, xOffset, yOffset))
		return false;
	
	return !isCrossedTankWithBuffer(points, xOffset, yOffset);
}

bool Map::allowMoveAmmo(Direction direction, const std::unique_ptr<Figure> &figure) {
	const auto& points = figure->getPoints();
	int xOffset = figure->getXOffset();
	int yOffset = figure->getYOffset();
	
	incrementOrigins(direction, xOffset, yOffset);
	
	bool wallIntersectionResult = isCrossedFigureWithWalls(points, xOffset, yOffset);
	
	crossAmmoWithBuffer(figure, xOffset, yOffset);
	
	return wallIntersectionResult;
}

bool
Map::isCrossedTankWithBuffer(
	const std::vector<std::vector<uint8_t>>& points,
	int xOffset,
	int yOffset) const {
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			const auto& tile = getTileType(j + xOffset, i + yOffset);
			// if buffer points and figure points are intersected and tank can pass
			if (points[i][j] && buffer[i + yOffset][j + xOffset] && !tile.tankPatency) {
				return true;
			}
		}
	}
	return false;
}

void
Map::crossAmmoWithBuffer(
	const std::unique_ptr<Figure> &figure,
	int xOffset,
	int yOffset) {
	const auto& points = figure->getPoints();
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			const auto& tile = getTileType(j + xOffset, i + yOffset);
			// if buffer points and figure points are intersected and ammo can pass it
			assert(figure);
			Ammo* ammoPtr = dynamic_cast<Ammo*>(figure.get());
			assert(ammoPtr);
			if (points[i][j] && buffer[i + yOffset][j + xOffset]) {
				if (tile.ammoPenetration == TileAmmoPenetrationType::TAP_DESTROYABLE) {
					buffer[i + yOffset][j + xOffset] = 0;
					ammoPtr->setActiveFlag(false);
				}
				else if (tile.ammoPenetration == TileAmmoPenetrationType::TAP_NOT_DESTROYABLE) {
					ammoPtr->setActiveFlag(false);
				}
				else if (tile.ammoPenetration == TileAmmoPenetrationType::TAP_FLY_THROUGH) {
					continue;
				}
			} else
				continue;
		}
	}
}

Tile Map::getTileType(uint32_t x, uint32_t y) const {
	int val = buffer[y][x];
	return getTileByType(static_cast<TileType>(buffer[y][x]));
}
