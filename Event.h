#pragma once
#include <functional>
#include <iostream>
#include <vector>

template <typename... Args>
class Event
{
private:
	std::vector<std::function<void(Args...)>> listeners;
public:
	// Subscribe a function to the event
	void BindEvent(std::function<void(Args...)> callback)
	{
		// Add Listener to the list of Listeners
		listeners.push_back(callback);
	}
	// Invoke the listener
	void Call(Args... args)
	{
		// Loop trough each Listener and execute the Listener
		for (auto& listener : listeners)
		{
			listener(args...);
		}
	}
	// Unbind all functions linked with this Event
	void UnbindAllEvents()
	{
		listeners.clear();
	}
};

