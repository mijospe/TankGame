#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tank.h"
#include "Player.h"
#include "InputManager.h"
#include "EnemyBase.h"

using std::cout;

int main()
{
	// Create Window
	sf::RenderWindow window{sf::VideoMode(1920, 1080), "Tanki Tanki"};
	window.setKeyRepeatEnabled(false); // Disable holding key presses

	// Delta time for FPS support
	sf::Clock clock{};
	double deltaTime = 0.0f;

	// Create Music
	sf::Music music{};

	// Enemy list
	std::vector<std::unique_ptr<Tank>> enemies;

	// Spawn in player
	Player player{ sf::Vector2f(1000,100), sf::Color(0,0,255), sf::Color(0,0,100), enemies};
	InputManager input;
	// Bind input
	input.Bind(sf::Keyboard::W, new MoveCommand(player, 1), new MoveCommand(player, 0));
	input.Bind(sf::Keyboard::A, new TurnCommand(player, -1), new TurnCommand(player, 0));
	input.Bind(sf::Keyboard::S, new MoveCommand(player, -1), new MoveCommand(player, 0));
	input.Bind(sf::Keyboard::D, new TurnCommand(player, 1), new TurnCommand(player, 0));
	input.Bind(sf::Keyboard::Space, new ShootCommand(player));

	// Spawn Tank Enemies
	for (int i = 0; i < 2; ++i)
	{
		std::unique_ptr<EnemyBase> tempEnemy = std::make_unique<EnemyBase>(sf::Vector2f(0, 0), sf::Color(255, 0, 0), sf::Color(100, 0, 0), &player);
		enemies.push_back(std::move(tempEnemy));
	}

	// Play Tank Music
	if (music.openFromFile("TankMusic.mp3"))
	{
		music.setLoop(true);
		music.play();
	}

	// Main Gameplay Loop
	while (window.isOpen())
	{
		// Calculate the Delta Time
		deltaTime = clock.restart().asSeconds();

		// Events for the window
		sf::Event windowEvent{};
		while (window.pollEvent(windowEvent))
		{
			// Input handling
			input.HandleInput(windowEvent);
			// Events for the window
			switch (windowEvent.type)
			{
				// If the close button is pressed, close the window
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		// Clear Window
		window.clear();
		// Update enemies
		for (std::unique_ptr<Tank>& enemy : enemies)
		{
			enemy->Update(window, deltaTime);
		}
		// Update Player
		player.Update(window, deltaTime);
		// Draw Window
		window.display();
	}
	return 0;
}