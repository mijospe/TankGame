#include "Player.h"

Player::Player(
	const sf::Vector2f inSpawnLocation,
	const sf::Color inBodyColor,
	const sf::Color inTurretColor,
	const std::vector<std::unique_ptr<Tank>>& inTargets) : targets(inTargets), Tank(inSpawnLocation, inBodyColor, inTurretColor)
{
	movementSpeed = 100.0f;
}
// Set movement direction
void Player::SetMovement(float moveDirection)
{
	movementDirection = moveDirection;
}
// Set rotation
void Player::SetTurning(float rotateDirection)
{
	rotationDirection = rotateDirection;
}
// Executes every Tick
void Player::Update(sf::RenderWindow& window, const double deltaTime)
{
	// Set the target location to the mouse position
	targetLocation = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	Tank::Update(window, deltaTime);
}

void Player::OnHit()
{
	exit(0);
}

void Player::PlayerShoot()
{
	auto* spawnedProjectile = Shoot();
	for (auto& target : targets)
	{
		spawnedProjectile->collider.AddShapeToChecklist(&target.get()->tankBody, target.get());
	}
}

void Player::OnProjectileHit(sf::RectangleShape* shape)
{
	std::cout << "Hit Enemy";
}