#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include <exception>

ColliderSystem::ColliderSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
}

void ColliderSystem::update(Game* game, Entity* entity, float elapsedTime) {
	auto collider{ entity->getColliderComp() };
	if (collider == nullptr) throw std::exception("No Collider component found");
	collider->setBoundingBox(entity->getPosition());
	while (false);
}

