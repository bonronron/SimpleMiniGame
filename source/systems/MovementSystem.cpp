#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include <exception>

MovementSystem::MovementSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsedTime) {
	auto velocity{ entity->getVelocityComp()};
	if (velocity == nullptr) throw std::exception("No velocity component found");
	auto position{ entity->getPositionComp() };
	if (position == nullptr) throw std::exception("No position component found");

	entity->getPositionComp()->setPosition(position->getPosition().x + (velocity->getVelocity().x * elapsedTime * velocity->getSpeed()),
		position->getPosition().y + (velocity->getVelocity().y * elapsedTime * velocity->getSpeed()));
}

