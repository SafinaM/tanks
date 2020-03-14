#pragma once

#include <Painter.h>
#include "Tank.h"

struct PainterTanks : Painter {
	
	void drawTank(const Tank& tank) const noexcept;
	void eraseTank(const Tank &tank) const noexcept;
	
	void drawAmmo(const Tank &tank, int color = -1) const noexcept;
	void eraseAmmo(const Tank& tank) const noexcept;
	
private:
	void drawFigure(const Figure &figure, int color = -1) const noexcept;
	void eraseFigure(const Figure& figure) const noexcept;
	
};

