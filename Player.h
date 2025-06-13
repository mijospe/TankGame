#pragma once
#include "Tank.h"
#include "Command.h"
#include "EnemyBase.h"

class Player : public Tank
{
public:
	// Default Constructor
	Player(
		const sf::Vector2f inSpawnLocation,
		const sf::Color inBodyColor,
		const sf::Color inTurretColor,
		const std::vector<std::unique_ptr<Tank>>& inTargets
	);
	void SetMovement(float moveDirection); // Set the movement direction
	void SetTurning(float rotateDirection); // Set the rotation of the tank
	void Update(sf::RenderWindow& window, const double deltaTime) override; // Executes every Tick
	void OnHit() override;
	void PlayerShoot();
	void OnProjectileHit(sf::RectangleShape* shape);

private:
	const std::vector<std::unique_ptr<Tank>>& targets;
};

// Commands for input //
// Turn tank command
class TurnCommand : public Command
{
private:
	Player& playerRef;
	float direction;
public:
	TurnCommand(Player& inPlayer, const float inDirection) : playerRef(inPlayer), direction(inDirection) {};
	void Execute() override { playerRef.SetTurning(direction); }
};
// Move tank command
class MoveCommand : public Command
{
private:
	Player& playerRef;
	float direction;

public:
	MoveCommand(Player& inPlayer, const float inDirection) : playerRef(inPlayer), direction(inDirection) {};
	void Execute() override { playerRef.SetMovement(direction); }
};

// Inputs
class ShootCommand : public Command
{
private:
	Player& playerRef;
public:
	ShootCommand(Player& inPlayer) : playerRef(inPlayer) {};
	void Execute() override { playerRef.PlayerShoot(); }
};