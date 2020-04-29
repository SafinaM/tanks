#include "PainterTanks.h"
#include "Tank.h"
#include <cassert>


void PainterTanks::drawTank(const Tank& tank) const noexcept {
	drawFigure(tank, 0);
}

void PainterTanks::eraseTank(const Tank& tank) const noexcept {
	eraseFigure(tank);
}

void PainterTanks::drawAmmo(const Tank &tank, int color) const noexcept {
	const auto& ammo = tank.getAmmo();
	const size_t size = ammo.size();
	
	for (auto i = 0; i < size; ++i) {
		if (ammo[i].isActive()) {
			drawFigure(ammo[i], color);
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

void PainterTanks::drawFigure(const Figure &figure, int color) const noexcept {
	const auto& points = figure.getPoints();
	assert(!points.empty());
	const int xOffset = figure.getXOffset();
	const int yOffset = figure.getYOffset();
	
	// by default we take color from figure, figureColor must be > 0
	uint32_t figureColor = figure.getColor();
	if (color > 0)
		figureColor = color;
	
	uint32_t textColor = TextColor::TC_BLACK;
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			assert(j + xOffset + xOffsetBoard >= 0);
			assert(i + yOffset + yOffsetBoard >= 0);
			if (points[i][j] == 1) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Empty,
					figureColor,
					textColor);
			} else if (points[i][j] == 2) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Left,
					figureColor,
					textColor);
			} else if (points[i][j] == 3) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbol::Right,
					figureColor,
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
	uint32_t color = BackgroundColor::BC_BLACK;
	uint32_t textColor = TextColor::TC_BLACK;
	
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