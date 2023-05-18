#include <cmath>


#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/ECSArchitecture.h"
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

ArchetypeECS::ArchetypeECS(Game* game) : ECSArchitecture(game) {

}

void ArchetypeECS::addEntity(std::shared_ptr<Entity> newEntity) {
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);

	int bitmask = bitmask2Int(newEntity->getComponentSet());

	if (archetypes.count(bitmask)) {
		archetypes[bitmask].push_back(newEntity);
	}
	else {
		std::vector<std::shared_ptr<Entity>> newArchetype;
		newArchetype.push_back(newEntity);
		archetypes.insert({ bitmask, newArchetype });

		std::vector<std::shared_ptr<System>> newArchetypeLogicSystems = systems4Archetype(newEntity->getComponentSet());
		archetypeLogicSystems.insert({ bitmask,newArchetypeLogicSystems });
	}
}

int ArchetypeECS::bitmask2Int(Bitmask bitmask) {
	int intValue = 0;
	for (int i = 0; i < 8; i++) {
		if (bitmask.getBit(i))
			intValue = intValue + (int)pow(2,i);
	}
	return intValue;
}
std::vector<std::shared_ptr<System>> ArchetypeECS::systems4Archetype(Bitmask bitmask) {
	std::vector<std::shared_ptr<System>> archetypeLogicSystems;
	if(bitmask[])
	archetypeLogicSystems.push_back(std::make_shared<TTLSystem>());
	archetypeLogicSystems.push_back(std::make_shared<MovementSystem>());
	archetypeLogicSystems.push_back(std::make_shared<InputSystem>());
	archetypeLogicSystems.push_back(std::make_shared<ColliderSystem>());
	archetypeLogicSystems.push_back(std::make_shared<LogicSystem>());

	return archetypeLogicSystems;
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

void ArchetypeECS::update(float elapsed) {
	auto mapIt = archetypes.begin();
	while (mapIt != archetypes.end()) {
		updateSystemsForEntities(elapsed, archetypeLogicSystems.at((*mapIt).first), (*mapIt).second);
		mapIt++;
	}
	auto it = entities.begin();
	while (it != entities.end()) {
		if (dynamic_cast<ColliderComponent*>((*it)->getComponent(ComponentID::COLLIDER)) == nullptr) {
			it++;
			continue;
		}
		auto player = getPlayer();
		if (player->collidesWith(*(*it).get())) {
			switch ((*it)->getEntityType()) {
			case EntityType::POTION:
			{
				Potion* potion = dynamic_cast<Potion*>((*it).get());
				dynamic_cast<HealthComponent*>(player->getComponent(ComponentID::HEALTH))->changeHealth(potion->getHealth());
				potion->deleteEntity();
				break;
			}
			case EntityType::LOG:
			{
				Log* log = dynamic_cast<Log*>((*it).get());
				auto playerGraphics = dynamic_cast<SpriteSheetGraphicsComponent*>(dynamic_cast<GraphicsComponent*>(player->getComponent(ComponentID::GRAPHICS)));
				auto playerLogic = dynamic_cast<PlayerStateComponent*>(player->getComponent(ComponentID::LOGIC));
				if (playerGraphics->getSpriteSheet()->getCurrentAnim()->isInAction()
					&& playerGraphics->getSpriteSheet()->getCurrentAnim()->getName() == "Attack")
				{
					playerLogic->addWood(log->getWood());
					log->deleteEntity();
				}
				break;
			}

			}
		}
		it++;
	}

	it = entities.begin();
	while (it != entities.end()) {
		if ((*it)->isDeleted()) {
			it = entities.erase(it);
		}
		else
			it++;
	}
}

std::shared_ptr<Entity> ArchetypeECS::getEntity(unsigned int idx)
{
	if (idx > entities.size() - 1) {
		throw std::runtime_error("ID OUT OF RANGE OF ENTITIES VECTOR");
		return nullptr;
	}
	return entities[idx];
}