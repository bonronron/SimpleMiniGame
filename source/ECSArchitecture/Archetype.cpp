#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/ECSArchitecture/Archetype.h"

Archetype::Archetype(std::shared_ptr<Entity> newEntity, std::vector<std::shared_ptr<System>>* reference2LogicSystems) {
	entities.push_back(newEntity);
	bitmask = newEntity->getComponentSet();
	logicSystems = systems4Archetype(newEntity.get(), reference2LogicSystems);
}

//UNDEFINED = -1,
//INPUT = 0,
//POSITION = 1,
//VELOCITY = 2,
//HEALTH = 3,
//GRAPHICS = 4,
//LOGIC = 5,
//TTL = 6,
//COLLIDER = 7
// Adds the systems which are needed to operate in the specific entity
std::vector<std::shared_ptr<System>> Archetype::systems4Archetype(Entity* entity, std::vector<std::shared_ptr<System>>* reference2LogicSystems) {
	std::vector<std::shared_ptr<System>> archetypeLogicSystems;

	auto it = reference2LogicSystems->begin();
	while (it != reference2LogicSystems->end()) {
		if ((*it)->validate(entity))
			archetypeLogicSystems.push_back(*it);
		it++;
	}
	return archetypeLogicSystems;
}

void Archetype::addEntity2Archetype(std::shared_ptr<Entity> newEntity) {
	entities.push_back(newEntity);
}

bool Archetype::isEntityOfArchetype(Entity entity) {
	return bitmask.match(entity.getComponentSet());
}