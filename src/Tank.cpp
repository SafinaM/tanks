#include "Tank.h"
#include <iostream>
#include <enums.h>
#include <cassert>

void Tank::print() {
	for (uint32_t i = 0; i < points.size(); ++i) {
		for (uint32_t j = 0; j < points[0].size(); ++j) {
			std::cout << +points[i][j];
		}
		std::cout << std::endl;
	}
}

Tank::Tank(TankType type) : m_tankType(type), Figure(Orientation::First_0) {
	
	points = getPoints(m_orientation);
	
	auto colorIt = colorByTankType.find(m_tankType);
	assert(colorIt != colorByTankType.end());
	m_Color = colorIt->second;
	
	m_id = ++m_numberOfTanks;
	
	auto it = ammoTypeByTankType.find(m_tankType);
	assert(it != ammoTypeByTankType.end());
	m_ammoType = it->second;
	// for user tanks we take max == 4, for opposite tanks we always take 1
	const uint32_t size = m_tankType == User1 || m_tankType == User2 ? Ammo::maxNumberOfAmmo: 1;
	m_ammo.resize(size);
	for (uint32_t i = 0; i < size; ++i) {
		Ammo am(m_ammoType);
		m_ammo.emplace_back(std::move(am));
	}
	assert(!m_ammo.empty());
	
	m_ammoSpeed = m_ammo[0].getSpeed();
	setTankSpeed();
}

void Tank::move(const Direction direction) noexcept {
	switch (direction) {
		case Direction::Up:
			m_orientation = Orientation::First_0;
			--m_offsetY;
			break;
		case Direction::Down:
			m_orientation = Orientation::Third_180;
			++m_offsetY;
			break;
		case Direction::Left:
			m_orientation = Orientation::Fourth_270;
			--m_offsetX;
			break;
		case Direction::Right:
			m_orientation = Orientation::Second_90;
			++m_offsetX;
		default:
			break;
	}
	points = getPoints(m_orientation);
}

void Tank::shoot() {
	// set m_maxAmmoCurrent
	setMaxAmmoCurrent();
	
	for (uint32_t i = 0; i < m_maxAmmoCurrent; ++i) {
		if (m_ammo[i].isActive()) {
//			std::cout << "Shell is flying!" << std::endl;
			continue;
		}
//		std::cout << "Shoot!" << std::endl;
		// change type
		m_ammo[i].setAmmoType(m_ammoType);
//		std::cout << "orientation = "<< static_cast<int>(m_orientation) << std::endl;
		m_ammo[i].setOrientationTypeAndDirection(m_orientation);
		m_ammo[i].setPoints(m_orientation);
		m_ammo[i].setXY(getXOffset(), getYOffset());
		m_ammo[i].setColor(getColor());
		m_ammo[i].setActiveFlag(true);
		m_ammoSpeed = m_ammo[i].getSpeed();
	}
}

void Tank::moveAmmo() {
	// set m_maxAmmoCurrent
	setMaxAmmoCurrent();
	for (uint32_t i = 0; i < m_maxAmmoCurrent; ++i) {
		if (m_ammo[i].isActive()) {
			const auto direction = m_ammo[i].getDirection();
			m_ammo[i].move(direction);
//			std::cout << "Shell is moving!" << std::endl;
			continue;
		}
	}
}

void Tank::setNextAmmoType() {
	if (m_ammoType == Ammo::SlowSingle) {
		setAmmoType(Ammo::FastSingle);
	} else if (m_ammoType == Ammo::FastSingle) {
		setAmmoType(Ammo::FastDouble);
	} else if (m_ammoType == Ammo::FastDouble) {
		setAmmoType(Ammo::FastDoubleStrong);
	} else if (m_ammoType == Ammo::FastDoubleStrong) {
		setAmmoType(Ammo::SuperFastNStrong);
	} else {
		std::cerr << "do not have such ammotype" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Tank::setAmmoType(Ammo::AmmoType ammoType) {
	m_ammoType = ammoType;
}

std::vector<Ammo> Tank::getAmmo() const noexcept {
	return m_ammo;
}

std::vector<std::vector<uint8_t>> Tank::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0:
			return
				{{2, 3},
				 {1, 1}};
		case Orientation::Second_90:
			return
				{{1, 3},
				 {1, 2}};
		case Orientation::Third_180:
			return
				{{1, 1},
				 {3, 2}};
		case Orientation::Fourth_270:
			return
				{{2, 1},
				 {3, 1}};
	}
}

const std::unordered_map<Tank::TankType, Ammo::AmmoType, std::hash<size_t>> Tank::ammoTypeByTankType = {
	{Tank::User1,           Ammo::SlowSingle},
	{Tank::User2,           Ammo::SlowSingle},
	{Tank::EnemySimple,     Ammo::SlowSingle},
	{Tank::EnemyFast,       Ammo::FastSingle},
	{Tank::EnemyStrong,     Ammo::SlowSingle},
	{Tank::EnemyStrongFast, Ammo::FastSingle},
	{Tank::Smart,           Ammo::SlowSingle},
};

const std::unordered_map<Tank::TankType, uint32_t, std::hash<size_t>> Tank::colorByTankType = {
	{Tank::User1,           2},
	{Tank::User2,           3},
	{Tank::EnemySimple,     1},
	{Tank::EnemyFast,       4},
	{Tank::EnemyStrong,     5},
	{Tank::EnemyStrongFast, 4},
	{Tank::Smart,           4},
};

const std::unordered_map<Tank::TankType, float, std::hash<size_t>> Tank::speedByTankType = {
	{Tank::User1,           0.1f},
	{Tank::User2,           0.1f},
	{Tank::EnemySimple,     0.1f},
	{Tank::EnemyFast,       0.05f},
	{Tank::EnemyStrong,     0.1f},
	{Tank::EnemyStrongFast, 0.5f},
	{Tank::Smart,           0.1f},
};

uint32_t Tank::m_numberOfTanks = 0;

void Tank::setMaxAmmoCurrent() {
	auto it = Ammo::numberByType.find(m_ammoType);
	assert(it != Ammo::numberByType.end());
	m_maxAmmoCurrent = it->second;
}

void Tank::setTankSpeed() {
	auto speedIt = speedByTankType.find(m_tankType);
	assert(speedIt != speedByTankType.end());
	m_tankSpeed = speedIt->second;
}

float Tank::getAmmoSpeed() const noexcept {
	return m_ammoSpeed;
}

float Tank::getTankSpeed() const noexcept {
	return m_tankSpeed;
}
