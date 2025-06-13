#pragma once
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "IGameBehaviour.h"
#include "Projectile.h"
#include "ObjectPool.h"

using std::cout;

class Tank : public IGameBehaviour
{
protected:
	// Tank Movement and Display
	float movementSpeed = 100.0f;
	float rotationSpeed = 50.0f;
	float movementDirection = 0;
	float rotationDirection = 0;
	sf::Vector2f scale{ 50,100 };

public:
	// Render Shapes
	sf::RectangleShape tankBody{ scale };
	sf::RectangleShape tankTurret{ scale * 0.5f };

protected:
	// Shooting
	sf::Vector2f targetLocation{ 0,0 };
	ObjectPool<Projectile> projectilePool{ 20 };
	std::vector<Projectile*> projectiles;

public:
	// Constructor
	Tank(const sf::Vector2f inSpawnLocation = sf::Vector2f(0, 0), const sf::Color inBodyColor = sf::Color::Blue, const sf::Color inTurretColor = sf::Color::Yellow);
	~Tank();

	virtual void Update(sf::RenderWindow& window, const double deltaTime) override; // Exectues every Tick
	virtual Projectile* Shoot(); // Shoot projectile from pool
	sf::Vector2f GetPosition(); // Get position of Tank
	void onProjectileDespawn(Projectile* projectileToDespawn); // Event for despawning projectile (return it to the pool)
};