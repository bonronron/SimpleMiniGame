#include<iostream>
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/utils/Observer.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Game.h"
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
#include "../../include/utils/AudioLocator.h"
#include "../../include/utils/AudioService.h"

ECSArchitecture::ECSArchitecture(Game* gamePointer) : game{ gamePointer }, entityID(0), inputHandler{ std::make_unique<InputHandler>() }, debugInfo{ true },
logPool{ EntityPool<Log>("../img/log.png") }, potionPool{ EntityPool<Potion>("../img/potion.png") }, firePool{ EntityPool<Fire>("../img/fire.png") },
achievementsManager{ new AchievementManager() } {
	logicSystems.push_back(std::make_shared<TTLSystem>());
	logicSystems.push_back(std::make_shared<InputSystem>());
	logicSystems.push_back(std::make_shared<MovementSystem>());
	logicSystems.push_back(std::make_shared<ColliderSystem>());
	logicSystems.push_back(std::make_shared<LogicSystem>());

	graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
	if (debugInfo) {
		graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
	}
	AudioManager* audio = new AudioService();
	AudioLocator::provide(audio);
}

void ECSArchitecture::updateSystems(float elapsedTime, std::vector<std::shared_ptr<System>> systems, std::vector<std::shared_ptr<Entity>> entities) {
	auto it{ systems.begin() };
	while (it != systems.end()) {
		updateSystem(elapsedTime, (*it), entities);
		it++;
	}
}
void ECSArchitecture::updateSystem(float elapsedTime, std::shared_ptr<System> system, std::vector<std::shared_ptr<Entity>> entities) {
	auto iterEntity{ entities.begin() };
	while (iterEntity != entities.end()) {
		if ((!(*iterEntity)->isDeleted()) && system->validate((*iterEntity).get())) {
			system->update(game, (*iterEntity).get(), elapsedTime);
		}
		iterEntity++;
	}

}
void ECSArchitecture::addToBase(std::shared_ptr<Entity> newEntity) {
	++entityID;
	newEntity->setID(entityID);
	entities.push_back(newEntity);
}
void ECSArchitecture::render(float elapsed) {
	updateSystems(elapsed, graphicsSystems, entities);
}

void ECSArchitecture::positionSprite(Entity& entity, int row, int col, int spriteWH, float tileScale) {
	sf::Vector2f scaleV2f = dynamic_cast<GraphicsComponent*>(entity.getComponent(ComponentID::GRAPHICS))->getSpriteScale();
	sf::Vector2i textureSize = dynamic_cast<GraphicsComponent*>(entity.getComponent(ComponentID::GRAPHICS))->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally
	dynamic_cast<PositionComponent*>(entity.getComponent(ComponentID::POSITION))->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void ECSArchitecture::initPlayer(int row, int col, int spriteWH, float tileScale) {
	player = std::make_shared<Player>();
	player->init("../img/DwarfSpriteSheet_data.txt", std::make_shared<SpriteSheetGraphicsComponent>());
	positionSprite(*player, row, col, spriteWH, tileScale);
	dynamic_cast<VelocityComponent*>(player->getComponent(ComponentID::VELOCITY))->setVelocity(0.f, 0.f);
	addEntity(player);
}

std::shared_ptr<Entity> ECSArchitecture::getEntity(unsigned int idx)
{
	if (idx > entities.size() - 1) {
		throw std::runtime_error("ID OUT OF RANGE OF ENTITIES VECTOR");
		return nullptr;
	}
	return entities[idx];
}

void ECSArchitecture::colliderAndDeleteBase() {
	//Collision
	auto it = entities.begin();
	while (it != entities.end()) {
		if (dynamic_cast<ColliderComponent*>((*it)->getComponent(ComponentID::COLLIDER)) == nullptr || *it == player) {
			it++;
			continue;
		}
		if (player->collidesWith(*(*it).get())) {
			if (collisionCallbacks.find((*it)->getEntityType()) != collisionCallbacks.end())
				collisionCallbacks.at((*it)->getEntityType())(*(*it).get(), debugInfo);
		}
		it++;
	}

	// Deletion
	// Removing entities from active entities and adding back to entity pool
	it = entities.begin();
	while (it != entities.end()) {
		if ((*it)->isDeleted()) {
			auto type = (*it)->getEntityType();
			switch (type) {
			case EntityType::LOG:
				logPool.deleteEntity(std::dynamic_pointer_cast<Log>(*it));
				break;
			case EntityType::POTION:
				potionPool.deleteEntity(std::dynamic_pointer_cast<Potion>(*it));
				break;
			case EntityType::FIRE:
				firePool.deleteEntity(std::dynamic_pointer_cast<Fire>(*it));
				break;
			default:
				std::cout <<"Failed delete"<<std::endl;
				break;
			}
			it = entities.erase(it);
		}
		else
			it++;
	}
}

