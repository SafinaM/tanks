#pragma once

#include <Painter.h>
#include "Tank.h"

struct PainterTanks: Painter {
	
	void drawTank(const Tank &tank) const noexcept;
	void eraseTank(const Tank &figure) const noexcept;
};

