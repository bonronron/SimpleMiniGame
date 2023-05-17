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

	logicSystems.push_back(std::make_shared<TTLSystem>());
	logicSystems.push_back(std::make_shared<MovementSystem>());
	logicSystems.push_back(std::make_shared<InputSystem>());
	logicSystems.push_back(std::make_shared<ColliderSystem>());
	logicSystems.push_back(std::make_shared<LogicSystem>());

	graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
	if (debugInfo) {
		graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
	}
}

void BigArrayECS::addEntity(std::shared_ptr<Entity> newEntity) {
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);
}

void BigArrayECS::update(float elapsed) {

	bigArray(elapsed, logicSystems);

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

void BigArrayECS::render(float elapsed) {
	bigArray(elapsed, graphicsSystems);
}

void BigArrayECS::bigArray(float elapsedTime, std::vector<std::shared_ptr<System>> systems) {
	auto it{ systems.begin() };
	while (it != systems.end()) {
		auto iterEntity{ entities.begin() };
		while (iterEntity != entities.end()) {
			if ((!(*iterEntity)->isDeleted()) && (*it)->validate((*iterEntity).get())) {
				(*it)->update(game, (*iterEntity).get(), elapsedTime);
			}
			iterEntity++;
		}
		it++;
	}
}
std::shared_ptr<Entity> BigArrayECS::getEntity(unsigned int idx)
{
	if (idx > entities.size() - 1) {
		throw std::runtime_error("ID OUT OF RANGE OF ENTITIES VECTOR");
		return nullptr;
	}
	return entities[idx];
}