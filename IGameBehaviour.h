#pragma once
#include "SFML/Graphics.hpp"

class IGameBehaviour
{
public:
	virtual ~IGameBehaviour() = default;

	virtual void Update(sf::RenderWindow& window, const double deltaTime) = 0;
	virtual void OnHit() { };
};

