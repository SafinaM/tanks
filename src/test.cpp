#include "Map.h"
#include "Stages.h"

#include <Painter.h>

int main() {
	
	Map map(stageTest);
	map.debugPrint(map.buffer);
	
	const uint32_t xOrigin = 40;
	const uint32_t yOrigin = 10;
	Painter painter;
	painter.clearScreen();
	const uint32_t x = 10;
	const uint32_t y = 10;
	const uint32_t width = 5;
	const uint32_t height = 5;
	
	painter.setXY(xOrigin, yOrigin);
	painter.drawRectangle(
		x + 20,
		y + 20,
		width,
		height,
		'~',
		BackgroundColor::BC_BLUE,
		TextColor::TC_LIGHT_BLUE);
	
	painter.drawRectangle(
		x + 30,
		y,
		width,
		height,
		'|',
		BackgroundColor::BC_GREEN,
		TextColor::TC_GREEN_BOLD);
	
	painter.drawRectangle(
		x + 40,
		y + 20,
		width,
		height,
		'-',
		BackgroundColor::BC_GRAY,
		TextColor::TC_BLACK_BOLD);
	
	painter.drawRectangle(
		x + 50,
		y + 20,
		width,
		height,
		'#',
		BackgroundColor::BC_GRAY,
		TextColor::TC_BLACK_BOLD);
	
	painter.drawRectangle(
		x + 60,
		y + 20,
		width,
		height,
		'^',
		BackgroundColor::BC_GREEN,
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

