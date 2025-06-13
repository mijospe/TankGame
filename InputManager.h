#pragma once
#include "Command.h"
#include <map>
#include <SFML/Window.hpp>

class InputManager
{
private:
	std::map<sf::Keyboard::Key, Command*> pressedKeyBindings;
	std::map<sf::Keyboard::Key, Command*> releasedKeyBindings;

public:
	~InputManager();
	void Bind(sf::Keyboard::Key key, Command* pressedCommand, Command* releasedCommand = nullptr);
	void HandleInput(sf::Event& eventRef);
};

