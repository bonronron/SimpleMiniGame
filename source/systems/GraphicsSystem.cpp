#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"

GraphicsSystem::GraphicsSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
}
void GraphicsSystem::update(Game* game, Entity* entity, float elapsedTime) 
{
	auto graphicsComp = entity->getGraphicsComp();
	if (graphicsComp == nullptr) throw std::exception("No graphics component found");
	auto positionComp = entity->getPositionComp();
	if (positionComp == nullptr) throw std::exception("No position component found");

	if (graphicsComp->isSpriteSheet()) {
		graphicsComp->getSpriteSheet()->getSprite().setPosition(positionComp->getPosition().x, positionComp->getPosition().y);
		graphicsComp->getSpriteSheet()->update(elapsedTime);
	}
	else {
		graphicsComp->getSprite()->setPosition(positionComp->getPosition().x, positionComp->getPosition().y);
	}
}