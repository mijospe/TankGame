#pragma once
#include "SFML/Graphics.hpp"
#include "IGameBehaviour.h"
#include "Event.h"
#include "BoxCollider.h"

class Projectile : public IGameBehaviour
{
public:
	// Default Constructor
	Projectile(
		const sf::Vector2f inSize = sf::Vector2f(10, 10),
		const float inLifeTime = 1.5f);
	// Initlize data
	void Init(
		const sf::Vector2f inSpawnLocation = sf::Vector2f(0, 0),
		const sf::Vector2f inShootDirection = sf::Vector2f(0, 0));
	// Executes every Tick
	void Update(sf::RenderWindow& window, const double deltaTime) override;
	void OnHit() override;

public:
	// Projectiles
	sf::RectangleShape projectileShape;
	sf::Vector2f shootDirection;
	float projectileSpeed = 500.0f;
	float lifeTime;
	float timeLived;

public:
	// Depsawn Event
	Event<Projectile*> onDespawn;
	BoxCollider collider{ &projectileShape, *this };
};

