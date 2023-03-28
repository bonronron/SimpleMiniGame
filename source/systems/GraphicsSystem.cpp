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
	if (entity->getGraphicsComp()->isSpriteSheet()) {
		entity->getGraphicsComp()->getSpriteSheet()->getSprite().setPosition(entity->getPosition().x, entity->getPosition().y);
		entity->getGraphicsComp()->getSpriteSheet()->update(elapsedTime);
	}
	else {
		entity->getGraphicsComp()->getSprite()->setPosition(entity->getPosition().x, entity->getPosition().y);
	}
}