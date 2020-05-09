#pragma once

#include "Ammo.h"
#include "helpers.h"
#include <Figure.h>

#include <vector>
#include <cstdint>
#include <string>

struct Tank : BaseAmmoTankFigure {
	
	enum TankType: uint32_t {
		User1           = 0,
		User2           = 1,
		EnemySimple     = 2,
		EnemyFast       = 3,
		EnemyStrong     = 4,
		EnemyStrongFast = 5,
		Smart           = 6
	};
	
	Tank(TankType type = TankType::EnemySimple);
	enum TankSymbol : char {
		Empty = ' ',
		Left = '/',
		Right = '\\',
	};
//	using Figure::getPoints;
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const override;
	
	void shoot();
	
	void moveAmmo();
	
	void setNextAmmoType();
	
	void setAmmoType(Ammo::AmmoType ammoType);
	
	void move(const Direction direction) noexcept;
	
	void move() noexcept;
	
	void print();
	
	std::vector<Ammo> getAmmo() const noexcept;
	
	float getAmmoSpeed() const noexcept;
	
	float getTankSpeed() const noexcept;
	
	void verifyIntersection(Tank& tank) noexcept;
	
	void verifyIntersections(std::vector<Tank>& tank) noexcept;
	
	// speed of every type
	const static std::unordered_map<Tank::TankType, Ammo::AmmoType, std::hash<size_t>> ammoTypeByTankType;
	const static std::unordered_map<Tank::TankType, uint32_t, std::hash<size_t>> colorByTankType;
	
	const static std::unordered_map<Tank::TankType, float, std::hash<size_t>> tankSpeedByTankType;
	
	std::vector<Ammo> ammo;
	bool isAlive = true;
	bool isErased = false;
	
private:
	static uint32_t m_numberOfTanks;
	uint32_t m_id = 0;
	TankType m_tankType = EnemySimple;
	Ammo::AmmoType m_ammoType = Ammo::SlowSingle;
	int m_maxAmmoCurrent = 1;
	float m_tankSpeed = 1.f;
	float m_ammoSpeed = 1.f;
	Direction m_direction;
	
	void setMaxAmmoCurrent();
	void setTankSpeed();
};