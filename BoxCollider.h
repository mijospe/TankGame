#pragma once
#include "Event.h"
#include "IGameBehaviour.h"

class BoxCollider : public IGameBehaviour
{
public:
	using CollisionCallback = std::function<void(sf::RectangleShape* collidedShape)>;

	BoxCollider(sf::RectangleShape* inOwnerShape, IGameBehaviour& inOwner);
	~BoxCollider();

	void Update(sf::RenderWindow& window, const double deltaTime) override;
	void AddShapeToChecklist(sf::RectangleShape* shape, IGameBehaviour* owner);
	void ClearCheckList();

private:
	IGameBehaviour& owner;
	sf::RectangleShape* ownerShape;
	std::vector<std::pair<sf::RectangleShape*, IGameBehaviour*>> targets;

	bool hasOverlapped = false;
};

