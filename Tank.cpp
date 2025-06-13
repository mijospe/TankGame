#include "Tank.h"

// Default constructor
Tank::Tank(sf::Vector2f inSpawnLocation, const sf::Color inBodyColor, const sf::Color inTurretColor)
{
	// Set the correct values for the body and turret
	tankBody.setFillColor(inBodyColor);
	tankTurret.setFillColor(inTurretColor);
	tankBody.setOrigin(scale * 0.5f);
	tankTurret.setOrigin(scale * 0.25f);
	tankBody.setPosition(inSpawnLocation);
	tankTurret.setPosition(inSpawnLocation);
}

Tank::~Tank()
{
	for (auto* projectile : projectiles)
	{
		onProjectileDespawn(projectile);
	}
}

// Called every tick
void Tank::Update(sf::RenderWindow& window, const double deltaTime)
{
	// Convert Degrees to Radians, calculate the direction and move
	float radians = (tankBody.getRotation() - 90) * 3.1415926535f / 180;
	float dirX = std::cos(radians) * movementDirection * movementSpeed * (float)deltaTime;
	float dirY = std::sin(radians) * movementDirection * movementSpeed * (float)deltaTime;
	tankBody.move(dirX, dirY);
	tankTurret.move(dirX, dirY);

	// Rotate tank body
	tankBody.setRotation(tankBody.getRotation() + rotationDirection * rotationSpeed * (float)deltaTime);
	
	// Draw body and turret on window
	window.draw(tankBody);
	window.draw(tankTurret);

	// Rotate turret to target location
	sf::Vector2f turretDirection = targetLocation - tankTurret.getPosition();
	float turretRadians = std::atan2(turretDirection.y, turretDirection.x);
	float turretDegree = turretRadians * 180 / 3.1415926535f;
	tankTurret.setRotation(turretDegree + 90);

	// Update all owned projectiles
	for (Projectile* projectile : projectiles)
	{
		projectile->Update(window, deltaTime);
	}
}

// Spawn a projectile from the projectile pool
Projectile* Tank::Shoot()
{
	float radians = (tankTurret.getRotation() - 90) * 3.1415926535f / 180;
	float dirX = std::cos(radians);
	float dirY = std::sin(radians);
	if (Projectile* requestedProjectile = projectilePool.RequestPoolItem())
	{
		requestedProjectile->Init(tankBody.getPosition(), sf::Vector2f(dirX, dirY));
		requestedProjectile->onDespawn.BindEvent([this, requestedProjectile](Projectile*)
			{
				this->onProjectileDespawn(requestedProjectile);
			});
		projectiles.push_back(requestedProjectile);

		return requestedProjectile;
	}
	return nullptr;
}

// Get position of Tank
sf::Vector2f Tank::GetPosition()
{
	return tankBody.getPosition();
}

// Despawn Projectile after projectile lifetime has exceeded
void Tank::onProjectileDespawn(Projectile* projectileToDespawn)
{
	projectilePool.ReturnPoolItem(projectileToDespawn);
	// Loop trough projectiles and delete the correct one from the projectiles list
	auto it = std::find(projectiles.begin(), projectiles.end(), projectileToDespawn);
	if (it != projectiles.end())
	{
		projectiles.erase(it);
	}
}