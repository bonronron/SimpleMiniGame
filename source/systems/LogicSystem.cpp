#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/components/LogicComponent.h"
#include <exception>

LogicSystem::LogicSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::LOGIC));
}
void LogicSystem::update(Game* game, Entity* entity, float elapsedTime) {
	auto logic{ dynamic_cast<LogicComponent*>(entity->getComponent(ComponentID::LOGIC)) };
	if (logic == nullptr) throw std::exception("No Logic component found");

	logic->update(entity,game,elapsedTime);
}