#include "PainterTanks.h"
#include "Tank.h"
#include <cassert>

void PainterTanks::drawTank(const Tank &tank) const noexcept {
	const auto& points = tank.getPoints();
	assert(!points.empty());
	const int xOffset = tank.getXOffset();
	const int yOffset = tank.getYOffset();
	uint32_t color = tank.getColor();
	uint32_t textColor = 0;

	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			assert(j + xOffset + xOffsetBoard >= 0);
			assert(i + yOffset + yOffsetBoard >= 0);
			if (points[i][j] == 1) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Empty,
					color,
					textColor);
			} else if (points[i][j] == 2) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Left,
					color,
					textColor);
			} else if (points[i][j] == 3) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Right,
					color,
					textColor);
			}
		}
		std::cout << std::endl;
	}
}

void PainterTanks::eraseTank(const Tank &tank) const noexcept {
	const auto& points = tank.getPoints();
	assert(!points.empty());
	const int xOffset = tank.getXOffset();
	const int yOffset = tank.getYOffset();
	uint32_t color = 0;
	uint32_t textColor = 0;
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			assert(j + xOffset + xOffsetBoard >= 0);
			assert(i + yOffset +  yOffsetBoard >= 0);
			drawPoint(
				j + xOffset + xOffsetBoard,
				i + yOffset + yOffsetBoard,
				Tank::TankSymbol::Empty,
				color,
				textColor);
		}
		std::cout << std::endl;
	}
}