#pragma once
#include <random>
#include "Tank.h"
#include "Event.h"

class EnemyBase : public Tank
{
	Tank* target;

public:
	// Default Constructor
	EnemyBase(
		const sf::Vector2f inSpawnLocation = sf::Vector2f(0, 0),
		const sf::Color inBodyColor = sf::Color::Red,
		const sf::Color inTurretColor = sf::Color::Red,
		Tank* inTarget = nullptr);
	// Executes every Tick
	void Update(sf::RenderWindow& window, const double deltaTime) override;
	void OnHit();
	
protected:
	float timeSinceLastShot = 0.0f;
	float shootInterval = 2.0f;
	bool isHit = false;
};

