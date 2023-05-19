#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/ECSArchitecture/Archetype.h"

Archetype::Archetype(std::shared_ptr<Entity> newEntity) {
	entities.push_back(newEntity);
	bitmask = newEntity->getComponentSet();
}

void Archetype::addEntity2Archetype(std::shared_ptr<Entity> newEntity) {
	entities.push_back(newEntity);
}

bool Archetype::isEntityOfArchetype(Entity entity) {
	return bitmask.contains(entity.getComponentSet());
}
bool Archetype::validateSystem(std::shared_ptr<System> system) {
	return system->validate((*entities.begin()).get());
}
void Archetype::deleteEntities() {
	auto entityIt = entities.begin();
	while (entityIt != entities.end()) {
		if ((*entityIt)->isDeleted()) {
			entityIt = entities.erase(entityIt);
		}
		else
			entityIt++;
	}
}