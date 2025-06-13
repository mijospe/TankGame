#pragma once
#include <iostream>
#include <vector>

template <typename T>
class ObjectPool
{
private:
	// All objects in pool
	std::vector<std::unique_ptr<T>> pool;
	std::vector<bool> inUse;
	// The max size of the pool
	int maxPoolSize = 0;

public:
	// Constructor
	ObjectPool(int inPoolSize) : maxPoolSize(inPoolSize)
	{
		// Reserving an resizing lists for memory optimization
		pool.reserve(maxPoolSize);
		inUse.resize(maxPoolSize, false);
		// Construct all the Entities at the start of the game
		for (int i = 0; i < maxPoolSize; i++)
		{
			pool.push_back(std::make_unique<T>());
		}
	}

	// Request and Return to Pool
	T* RequestPoolItem()
	{
		// Check if pool is valid
		if (pool.size() != inUse.size())
		{
			std::cout << "Pool and inUse size mismatch!" << std::endl;
			return nullptr;
		}

		// If there are objects left in the pool, give the requested object
		for (size_t i = 0; i < pool.size(); i++)
		{
			if (!inUse[i])
			{
				inUse[i] = true;
				return pool[i].get();
			}
		}
		return nullptr; // Return null if pool is empty
	}

	// Return item back to pool
	void ReturnPoolItem(T* returnItem)
	{
		for (size_t i = 0; i < pool.size(); i++)
		{
			// If the item being returned is looped in the correct slot
			if (pool[i].get() == returnItem)
			{
				inUse[i] = false;
				return;
			}
		}
		std::cout << "Error: Pool is full, can't add any more items to pool\n";
	}
};