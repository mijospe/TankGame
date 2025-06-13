#include "Projectile.h"
// Default Constructor
Projectile::Projectile(const sf::Vector2f inSize, const float inLifeTime) : lifeTime(inLifeTime), collider(&projectileShape, *this)
{
	projectileShape.setSize(inSize);
	projectileShape.setOrigin(inSize * 0.5f);
}
// Initiliaze data for when object is pulled from pool
void Projectile::Init(const sf::Vector2f inSpawnLocation, const sf::Vector2f inShootDirection)
{
	shootDirection = inShootDirection;
	projectileShape.setPosition(inSpawnLocation);
	timeLived = 0.0f;
}
// Executes every Tick
void Projectile::Update(sf::RenderWindow& window, const double deltaTime)
{
	collider.Update(window, deltaTime);
	// Increase the lived time and check if need to despawn
	timeLived += (float)deltaTime;
	if (timeLived > lifeTime)
	{
		onDespawn.Call(this);
		onDespawn.UnbindAllEvents();
	}
	// Move the projectile and draw it
	projectileShape.move(shootDirection * projectileSpeed * (float)deltaTime);
	window.draw(projectileShape);
}

void Projectile::OnHit()
{
	collider.ClearCheckList();
}