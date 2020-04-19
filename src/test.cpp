#include "Map.h"
#include "Stages.h"

#include <Painter.h>

int main() {
	
	Map map(40, 20, stageTest);
	map.debugPrint();
	
	const uint32_t xOrigin = 40;
	const uint32_t yOrigin = 10;
	Painter painter;
	painter.clearScreen();
	const uint32_t x = 10;
	const uint32_t y = 10;
	const uint32_t width = 10;
	const uint32_t height = 10;
	
	painter.setXY(xOrigin, yOrigin);
	painter.drawRectangle(
		x,
		y,
		width,
		height,
		'!',
		BackgroundColor::BC_BLUE,
		TextColor::TC_GREEN_BOLD);

	for (uint32_t i = 0; i < map.getHeight(); ++i) {
		for (uint32_t j = 0; j < map.getWidth(); ++j) {
			painter.drawPoint(
				j + xOrigin,
				i + yOrigin,
				' ',
				map.buffer[i][j],
				TextColor::TC_YELLOW);
		}
	}
	
	return 0;
}

