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

Tank::Tank(TankType type) : m_tankType(type), BaseAmmoTankFigure(Orientation::First_0) {
	
	points = getPoints(m_orientation);
	
	auto colorIt = colorByTankType.find(m_tankType);
	assert(colorIt != colorByTankType.end());
	m_Color = colorIt->second;
	
	m_id = ++m_numberOfTanks;
	
	auto it = ammoTypeByTankType.find(m_tankType);
	assert(it != ammoTypeByTankType.end());
	m_ammoType = it->second;
	
	// for user tanks we take max == 4, for opposite tanks we always take 1
	const uint32_t size = m_tankType == (User1 || m_tankType == User2) ? Ammo::maxNumberOfAmmo : 1;
	
	ammo.resize(size);
	for (uint32_t i = 0; i < size; ++i) {
		Ammo am(m_ammoType);
		ammo.emplace_back(std::move(am));
	}
	assert(!ammo.empty());
	
	m_ammoSpeed = ammo[0].getSpeed();
	setTankSpeed();
}

void Tank::move() noexcept {
	move(m_direction);
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
//			std::cerr << "Error direction is not set!" << std::endl;
			break;
	}
	points = getPoints(m_orientation);
}

void Tank::shoot() {
	setMaxAmmoCurrent();
	for (uint32_t i = 0; i < m_maxAmmoCurrent; ++i) {
		if (ammo[i].isActive()) {
			continue;
		}
		ammo[i].setAmmoType(m_ammoType);
		ammo[i].setOrientationTypeAndDirection(m_orientation);
		ammo[i].setPoints(m_orientation);
		ammo[i].setXY(getXOffset(), getYOffset());
//		ammo[i].setColor(getColor());
		ammo[i].setActiveFlag(true);
		m_ammoSpeed = ammo[i].getSpeed();
		break;
	}
}

void Tank::moveAmmo() {
	setMaxAmmoCurrent();
	for (uint32_t i = 0; i < m_maxAmmoCurrent; ++i) {
		if (ammo[i].isActive()) {
			const auto direction = ammo[i].getDirection();
			ammo[i].move(direction);
		}
	}
}

void Tank::setNextAmmoType() {
	switch(m_ammoType) {
		case Ammo::SlowSingle:
			setAmmoType(Ammo::FastSingle);
			break;
		case Ammo::FastSingle:
			setAmmoType(Ammo::FastDouble);
			break;
		case Ammo::FastDouble:
			setAmmoType(Ammo::FastDoubleStrong);
			break;
		case Ammo::FastDoubleStrong:
			setAmmoType(Ammo::SuperFastNStrong);
			break;
		default:
			std::cerr << "do not have such ammo type" << std::endl;
			exit(EXIT_FAILURE);
	}
}

void Tank::setAmmoType(Ammo::AmmoType ammoType) {
	m_ammoType = ammoType;
}

std::vector<Ammo> Tank::getAmmo() const noexcept {
	return ammo;
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

const std::unordered_map<Tank::TankType, float, std::hash<size_t>> Tank::tankSpeedByTankType = {
	{Tank::User1,           0.1f},
	{Tank::User2,           0.1f},
	{Tank::EnemySimple,     0.1f},
	{Tank::EnemyFast,       0.05f},
	{Tank::EnemyStrong,     0.1f},
	{Tank::EnemyStrongFast, 0.05f},
	{Tank::Smart,           0.1f},
};

uint32_t Tank::m_numberOfTanks = 0;

void Tank::setMaxAmmoCurrent() {
	auto it = Ammo::numberByType.find(m_ammoType);
	assert(it != Ammo::numberByType.end());
	m_maxAmmoCurrent = it->second;
}

void Tank::setTankSpeed() {
	auto speedIt = tankSpeedByTankType.find(m_tankType);
	assert(speedIt != tankSpeedByTankType.end());
	m_tankSpeed = speedIt->second;
}

float Tank::getAmmoSpeed() const noexcept {
	return m_ammoSpeed;
}

float Tank::getTankSpeed() const noexcept {
	return m_tankSpeed;
}

void Tank::verifyIntersection(Tank& tank) noexcept {
	
	// check ammo intersection
	for (auto& ammoItem1: tank.ammo) {
		for (auto& ammoItem2: this->ammo) {
			if (ammoItem1.isActive() && ammoItem2.isActive() &&
			areCrossedFigures(ammoItem1, ammoItem2)) {
				ammoItem1.setActiveFlag(false);
				ammoItem2.setActiveFlag(false);
			}
		}
	}
	
	// check intersection of ammo and this tank
	for (auto& ammoItem: tank.ammo) {
		if (ammoItem.isActive() && areCrossedFigures(ammoItem, *this)) {
			ammoItem.setActiveFlag(false);
			this->isAlive = false;
			std::cout << "User tank is killed!" << std::endl;
		}
	}
	
	// check intersection of ammo and other tank
	for (auto& ammoItem: ammo) {
		if (ammoItem.isActive() && areCrossedFigures(ammoItem, tank)) {
			ammoItem.setActiveFlag(false);
			tank.isAlive = false;
		}
	}
}

void Tank::verifyIntersections(std::vector<Tank>& tanks) noexcept {
	for (auto& tank: tanks) {
		if (!tank.isAlive)
			continue;
		verifyIntersection(tank);
	}
}


