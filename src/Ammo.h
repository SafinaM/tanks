#pragma once

#include <Figure.h>

#include <unordered_map>

// explosive artillery projectile or bomb.
struct Ammo : Figure {
	
	enum AmmoType : uint32_t {
		SlowSingle        = 0,
		FastSingle        = 1,
		FastDouble        = 2,
		FastDoubleStrong  = 3,
		SuperFastNStrong  = 4,
	};
	
	Ammo(AmmoType type = AmmoType::SlowSingle);
	
	uint32_t id = 0;
	
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const override;
	
	void setPoints(Orientation orientation) noexcept;
	
	void setAmmoType(const AmmoType type);
	
	void debugPrint() const;
	
	float getSpeed() const;
	
	float getNumber() const;
	
	bool isActive() const;
	
	void setActiveFlag(bool isActive);
	
	uint32_t getId() const;
	
	AmmoType ammoType = SlowSingle;
	
	// speed of every type
	static const std::unordered_map<Ammo::AmmoType, float, std::hash<size_t>> speedByType;
	
	// number of every type
	static const std::unordered_map<Ammo::AmmoType, uint32_t, std::hash<size_t>> numberByType;
	
	static constexpr uint32_t maxNumberOfAmmo = 4;
private:
	
	bool m_isActive = false;
};
