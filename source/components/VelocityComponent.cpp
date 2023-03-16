#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Entity.h"

void VelocityComponent::update(Entity& entity, float elapsedTime) {
	//position->setPosition(position->getPosition().x + velocity.x * elapsed * speed, position->getPosition().y + velocity.y * elapsed * speed);
	
	entity.setPosition(entity.getPosition().x + (velocity.x * elapsedTime * speed),
		entity.getPosition().y + (velocity.y * elapsedTime * speed));
}