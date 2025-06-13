#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::RectangleShape* inOwnerShape, IGameBehaviour& inOwner) : ownerShape(inOwnerShape), owner(inOwner)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Update(sf::RenderWindow& window, const double deltaTime)
{
	if (hasOverlapped) return;

	// Loop trough every target
	for (auto& pair : targets)
	{
		// If the collider overlaps with any of the linked shapes, execute OnHit
		if (&pair.second && &pair.first && ownerShape->getGlobalBounds().intersects(pair.first->getGlobalBounds()))
		{
			owner.OnHit();
			hasOverlapped = true;
			pair.second->OnHit();
		}
	}
}

void BoxCollider::AddShapeToChecklist(sf::RectangleShape* shape, IGameBehaviour* owner)
{
	targets.emplace_back(shape, owner);
}
void BoxCollider::ClearCheckList()
{
	targets.clear();
}