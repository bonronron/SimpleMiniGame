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

BigArrayECS::BigArrayECS(Game* game) : ECSArchitecture(game) {
}

void BigArrayECS::addEntity(std::shared_ptr<Entity> newEntity) {
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);
}

void BigArrayECS::update(float elapsed) {

	// Updating logic
	updateSystems(elapsed, logicSystems, entities);

	// Colliders
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

	// Deleting entities to be deleted
	it = entities.begin();
	while (it != entities.end()) {
		if ((*it)->isDeleted()) {
			it = entities.erase(it);
		}
		else
			it++;
	}
}