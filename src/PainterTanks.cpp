#include "PainterTanks.h"
#include "Tank.h"
#include <cassert>


void PainterTanks::drawTank(const Tank& tank) const noexcept {
	drawFigure(tank);
}

void PainterTanks::eraseTank(const Tank& figure) const noexcept {
	eraseFigure(figure);
}

void PainterTanks::drawAmmo(const Tank& tank) const noexcept {
	const auto& ammo = tank.getAmmo();
	const size_t size = ammo.size();
	
	for (auto i = 0; i < size; ++i) {
		if (ammo[i].isActive()) {
			drawFigure(ammo[i]);
		}
	}
}

void PainterTanks::eraseAmmo(const Tank& tank) const noexcept {
	const auto& ammo = tank.getAmmo();
	const size_t size = ammo.size();
	
	for (auto i = 0; i < size; ++i) {
		if (ammo[i].isActive()) {
			eraseFigure(ammo[i]);
		}
	}
}

void PainterTanks::drawFigure(const Figure& figure) const noexcept {
	const auto& points = figure.getPoints();
	assert(!points.empty());
	const int xOffset = figure.getXOffset();
	const int yOffset = figure.getYOffset();
	uint32_t color = figure.getColor();
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

void PainterTanks::eraseFigure(const Figure &figure) const noexcept {
	const auto& points = figure.getPoints();
	assert(!points.empty());
	const int xOffset = figure.getXOffset();
	const int yOffset = figure.getYOffset();
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