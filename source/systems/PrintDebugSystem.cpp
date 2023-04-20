#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/graphics/Window.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include <exception>

PrintDebugSystem::PrintDebugSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
}
void PrintDebugSystem::update(Game* game, Entity* entity, float elapsedTime) {
	auto collider{ dynamic_cast<ColliderComponent*>(entity->getComponent(ComponentID::COLLIDER)) };
	if (collider == nullptr) throw std::exception("No Logic component found");

	auto window = game->getWindow();
	window->draw(collider->getBoundingBox().getDrawableRect());
}