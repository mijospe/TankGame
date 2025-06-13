#include "InputManager.h"

// Deletes all the command pointers when InputManager is deleted
InputManager::~InputManager()
{
	for (auto& keyBind : pressedKeyBindings)
	{
		delete keyBind.second;
	}
	for (auto& keyBind : releasedKeyBindings)
	{
		delete keyBind.second;
	}
}

// Bind the key and command to the list of bindings
void InputManager::Bind(sf::Keyboard::Key key, Command* pressedCommand, Command* releasedCommand)
{
	pressedKeyBindings[key] = pressedCommand;
	releasedKeyBindings[key] = releasedCommand;
}
// Handles the input when it is pressed or released
void InputManager::HandleInput(sf::Event& eventRef)
{
	// If a key is pressed that is in the pressed keybindings
	if (eventRef.type == sf::Event::KeyPressed)
	{
		auto it = pressedKeyBindings.find(eventRef.key.code);
		if (it != pressedKeyBindings.end() && it->second) it->second->Execute(); // Execute if the key and command are both valid
	}
	// If a key is released that is in the released keybindings
	else if (eventRef.type == sf::Event::KeyReleased)
	{
		auto it = releasedKeyBindings.find(eventRef.key.code);
		if (it != releasedKeyBindings.end() && it->second) it->second->Execute(); // Execute if the key and command are both valid
	}
}