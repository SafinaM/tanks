#include "PainterTanks.h"
#include <Tank.h>

void PainterTanks::drawFigure(const Tank &tank, bool draw, char symbol) const noexcept {
	const auto& points = tank.getPoints();
	assert(!points.empty());
	const int xOffset = tank.getXOffset();
	const int yOffset = tank.getYOffset();
	uint32_t color = 0;
	uint32_t textColor = Board::textColor;
	if (draw) {
		color = tank.getColor();
		textColor = tank.getColor();
	}
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			assert(j + xOffset + xOffsetBoard >= 0);
			assert(i + yOffset +  yOffsetBoard >= 0);
			if (points[i][j] == 1) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbs::Empty,
					color,
					textColor);
			} else if (points[i][j] == 2) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbs::Cabin,
					color,
					textColor);
			} else if (points[i][j] == 3) {
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset + yOffsetBoard,
					Tank::TankSymbs::Gun,
					color,
					textColor);
			}
		}
		std::cout << std::endl;
	}
}