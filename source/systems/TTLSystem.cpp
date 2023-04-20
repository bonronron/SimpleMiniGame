#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/components/TTLComponent.h"
#include <exception>

TTLSystem::TTLSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
}

void TTLSystem::update(Game* game, Entity* entity, float elapsedTime) {
	auto ttl{ dynamic_cast<TTLComponent*>(entity->getComponent(ComponentID::TTL)) };
	if (ttl == nullptr) throw std::exception("No TTL component found");
	ttl->decrementTTL();
	if (ttl->getTTL() <= 0) {
		entity->deleteEntity();
	}
}

