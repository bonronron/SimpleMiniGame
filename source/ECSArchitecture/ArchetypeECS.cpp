#include <cmath>
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/ECSArchitecture/Archetype.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/EntityPool.h"
#include "../../include/ECSArchitecture/ECSArchitecture.h"

ArchetypeECS::ArchetypeECS(Game* game) : ECSArchitecture(game) {}

void ArchetypeECS::addEntity(std::shared_ptr<Entity> newEntity) {
	// Adding entity to base class
	addToBase(newEntity);
	// Checking with existing archetypes
	bool isAdded = false;
	auto it = archetypes.begin();
	while (it != archetypes.end()) {
		if ((*it)->isEntityOfArchetype(*newEntity)) {
			(*it)->addEntity2Archetype(newEntity);
			isAdded = true;
			break;
		}
		it++;
	}
	// if failed creating new archetype
	if (!isAdded) {
		std::shared_ptr<Archetype> newArchetype = std::make_shared<Archetype>(newEntity);
		archetypes.push_back(newArchetype);
	}
}


void ArchetypeECS::update(float elapsed) {

	// Updating logic for archetypes
	auto systemIt = logicSystems.begin();
	while (systemIt != logicSystems.end()) {
		auto archetypeIt = archetypes.begin();
		while (archetypeIt != archetypes.end()) {
			if ((*archetypeIt)->validateSystem(*systemIt))
				updateSystem(elapsed, (*systemIt), (*archetypeIt)->getEntities());
			archetypeIt++;
		}
		systemIt++;
	}
	colliderAndDeleteBase();

	auto archetypeIt = archetypes.begin();
	while (archetypeIt != archetypes.end()) {
		(*archetypeIt)->deleteEntities();
		if ((*archetypeIt)->getEntities().size() == 0) {
			archetypeIt = archetypes.erase(archetypeIt);
		}
		else {
			archetypeIt++;
		}
	}
}