#include "../../include/utils/Vector2.h"
#include "../../include/components/Components.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Entity.h"

void VelocityComponent::update(Entity& entity, float elapsedTime) {
	entity.setPosition(entity.getPosition().x + (velocity.x * elapsedTime * speed),
		entity.getPosition().y + (velocity.y * elapsedTime * speed));
}