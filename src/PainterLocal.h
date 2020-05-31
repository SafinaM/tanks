#pragma once

#include <Painter.h>
#include "Tank.h"
#include "Map.h"

struct PainterLocal : Painter {
	
	void drawTank(const Tank& tank) const noexcept;
	void eraseTank(const Tank& tank) const noexcept;
	
	void drawAmmo(const Tank &tank, int color = TC_DEFAULT) const noexcept;
	void eraseAmmo(const Tank& tank) const noexcept;
	
	void drawMap(const Map& map);
	
private:
	void drawFigure(const Figure &figure, int color = TC_DEFAULT) const noexcept;
	void eraseFigure(const Figure& figure) const noexcept;
	
};

