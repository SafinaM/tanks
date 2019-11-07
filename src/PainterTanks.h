#pragma once

#include <Painter.h>
#include "Tank.h"

struct PainterTanks: Painter {
	
	void drawTank(const Tank &figure, bool draw, char symbol) const noexcept;
};

