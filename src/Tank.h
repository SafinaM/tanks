#pragma once

#include "Ammo.h"
#include "helpers.h"

#include <Figure.h>

#include <vector>
#include <cstdint>
#include <string>

struct Tank : Figure {
	
	enum TankType : uint32_t {
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
	using Figure::getPoints;
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const override;
	
	void shoot();
	
	void setNextAmmoType();
	
	void setAmmoType(Ammo::AmmoType ammoType);
	
	void move(const Direction direction);
	
	void print();
	
	// speed of every type
	const static std::unordered_map<Tank::TankType, Ammo::AmmoType, std::hash<size_t>> ammoTypeByTankType;
	const static std::unordered_map<Tank::TankType, uint32_t, std::hash<size_t>> colorByTankType;

private:
	static uint32_t m_numberOfTanks;
	uint32_t m_id = 0;
	TankType m_tankType = EnemySimple;
	std::vector<Ammo> m_ammo;
	Ammo::AmmoType m_ammoType = Ammo::SlowSingle;
	int m_maxAmmoCurrent = 1;
};