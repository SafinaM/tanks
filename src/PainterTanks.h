#pragma once

#include <Painter.h>

class PainterTanks: Painter {
	
	void drawTank(const Figure &figure, bool draw, char symbol) const noexcept;
};

