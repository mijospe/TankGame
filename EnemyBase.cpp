#include "EnemyBase.h"

// Default Constructor
EnemyBase::EnemyBase(
	const sf::Vector2f inSpawnLocation,
	const sf::Color inBodyColor,
	const sf::Color inTurretColor,
	Tank* inTarget ) : Tank(inSpawnLocation, inBodyColor, inTurretColor), target(inTarget)
{
	// Spawn tank in Random Location
	std::random_device rd;
	std::mt19937 floatGen(rd());
	std::uniform_real_distribution<float> distX(0, 1920);
	std::uniform_real_distribution<float> distY(0, 1080);
	float spawnX = distX(floatGen);
	float spawnY = distY(floatGen);
	
	tankBody.setPosition(sf::Vector2f(spawnX, spawnY));
	tankTurret.setPosition(sf::Vector2f(spawnX, spawnY));
}
// Executes every Tick
void EnemyBase::Update(sf::RenderWindow& window, const double deltaTime)
{
	if (isHit) return;
	timeSinceLastShot += (float)deltaTime;
	targetLocation = target->GetPosition();

	// Spawn projectile every interval
	if (timeSinceLastShot >= shootInterval)
	{
		timeSinceLastShot = 0.0f;
		Shoot()->collider.AddShapeToChecklist(&target->tankBody, target);
	}

	Tank::Update(window, deltaTime);
}

void EnemyBase::OnHit()
{
	isHit = true;
}