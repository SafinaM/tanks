#include "Map.h"
#include "Tank.h"
#include "Ammo.h"

#include <iostream>

void Map::setXY(uint32_t x, uint32_t y)  noexcept {
	m_xOrigin = x;
	m_yOrigin = y;
}

uint32_t Map::getXOrigin() const noexcept {
	return m_xOrigin;
}

uint32_t Map::getYOrigin() const noexcept {
	return m_yOrigin;
}

bool Map::areCrossedFigures(Figure* figure1, Figure* figure2) {
	
	Tank* ptrTank1 = dynamic_cast<Tank*>(figure1);
	Tank* ptrTank2 = dynamic_cast<Tank*>(figure2);
	if (ptrTank1 && ptrTank2)
		return false;
	
	Ammo* ammoPtr1 = dynamic_cast<Ammo*>(figure1);
	Ammo* ammoPtr2 = dynamic_cast<Ammo*>(figure2);
	
	const auto& points1 = figure1->getPoints();
	const auto& points2 = figure2->getPoints();
	
	
	areCrossedBuffers(points1, points2);
}
