#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"

GraphicsSystem::GraphicsSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
}
void GraphicsSystem::update(Game* game, Entity* entity, float elapsedTime) 
{
	auto graphicsComp = dynamic_cast<GraphicsComponent*>(entity->getComponent(ComponentID::GRAPHICS));
	if (graphicsComp == nullptr) throw std::exception("No graphics component found");
	auto positionComp = dynamic_cast<PositionComponent*>(entity->getComponent(ComponentID::POSITION));
	if (positionComp == nullptr) throw std::exception("No position component found");

	auto window = game->getWindow();

	if (graphicsComp->isSpriteSheet()) {
		auto spriteSheet = graphicsComp->getSpriteSheet();
		spriteSheet->getSprite().setPosition(positionComp->getPosition().x, positionComp->getPosition().y);
		spriteSheet->update(elapsedTime);
		window->draw(spriteSheet->getSprite());
	}
	else {
		auto sprite = graphicsComp->getSprite();
		sprite->setPosition(positionComp->getPosition().x, positionComp->getPosition().y);
		window->draw(*sprite);
	}
}