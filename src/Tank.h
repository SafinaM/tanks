#pragma once

#include "Ammo.h"
#include "helpers.h"
#include <Figure.h>

#include <vector>
#include <cstdint>
#include <string>

struct Tank : Figure {
	
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
	
	void print();
	
	std::vector<Ammo> getAmmo() const noexcept;
	
	float getAmmoSpeed() const noexcept;
	
	float getTankSpeed() const noexcept;
	
	// speed of every type
	const static std::unordered_map<Tank::TankType, Ammo::AmmoType, std::hash<size_t>> ammoTypeByTankType;
	const static std::unordered_map<Tank::TankType, uint32_t, std::hash<size_t>> colorByTankType;
	const static std::unordered_map<Tank::TankType, float, std::hash<size_t>> speedByTankType;

private:
	
	std::vector<Ammo> m_ammo;
	static uint32_t m_numberOfTanks;
	uint32_t m_id = 0;
	TankType m_tankType = EnemySimple;
	Ammo::AmmoType m_ammoType = Ammo::SlowSingle;
	int m_maxAmmoCurrent = 1;
	bool m_isAlive = true;
	float m_tankSpeed = 1;
	float m_ammoSpeed = 1;
	
	void setMaxAmmoCurrent();
	
	void setAmmoSpeed(float speed) noexcept;
	
	void setTankSpeed(float speed) noexcept;
};