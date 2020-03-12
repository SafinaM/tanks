#include "Ammo.h"
#include "Tank.h"
#include <enums.h>

#include <iostream>
#include <cassert>

void Ammo::debugPrint() const {
	for (uint32_t i = 0; i < points.size(); ++i) {
		for (uint32_t j = 0; j < points[0].size(); ++j) {
			std::cout << +points[i][j];
		}
		std::cout << std::endl;
	}
}

Ammo::Ammo(AmmoType type) : ammoType(type), Figure(m_orientation) {
	m_Color = ammoType;
}

//void Ammo::move(const Direction direction) {
//	switch (direction) {
//		case Direction::Up:
//			m_orientation = Orientation::First_0;
//			--m_offsetY;
//			break;
//		case Direction::Down:
//			m_orientation = Orientation::Third_180;
//			++m_offsetY;
//			break;
//		case Direction::Left:
//			--m_offsetX;
//			m_orientation = Orientation::Fourth_270;
//			break;
//		case Direction::Right:
//			m_orientation = Orientation::Second_90;
//			++m_offsetX;
//	}
//	points = getPoints(m_orientation);
//}

std::vector<std::vector<uint8_t>> Ammo::getPoints(Orientation orientation) const {
	switch (m_orientation) {
		case Orientation::First_0:
			return
				{{2, 3}};
		case Orientation::Second_90:
			return
				{{3},
				 {2}};
		case Orientation::Third_180:
			return
				{{3, 2}};
		case Orientation::Fourth_270:
			return
				{{2},
				 {3}};
	}
}

void Ammo::setAmmoType(const AmmoType type) {
	ammoType = type;
}

float Ammo::getSpeed() const {
	return speedByType.at(ammoType);
}

float Ammo::getNumber() const {
	return numberByType.at(ammoType);
}

uint32_t Ammo::getId() const {
	return id;
}

bool Ammo::isActive() const {
	return m_isActive;
}

void Ammo::setActiveFlag(bool isActive) {
	m_isActive = isActive;
}

const std::unordered_map<uint32_t, float> Ammo::speedByType = {
	{static_cast<uint32_t>(Ammo::SlowSingle), 0.3f},
	{static_cast<uint32_t>(Ammo::FastSingle), 0.2f},
	{static_cast<uint32_t>(Ammo::FastDouble), 0.2f},
	{static_cast<uint32_t>(Ammo::FastDoubleStrong), 0.2f},
	{static_cast<uint32_t>(Ammo::SuperFastNStrong), 0.15f}};

const std::unordered_map<uint32_t, uint32_t> Ammo::numberByType = {
	{static_cast<uint32_t>(Ammo::SlowSingle), 1},
	{static_cast<uint32_t>(Ammo::FastSingle), 1},
	{static_cast<uint32_t>(Ammo::FastDouble), 2},
	{static_cast<uint32_t>(Ammo::FastDoubleStrong), 2},
	{static_cast<uint32_t>(Ammo::SuperFastNStrong), 4}};

