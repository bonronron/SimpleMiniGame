
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

ECSArchitecture::ECSArchitecture(Game* gamePointer) : game{gamePointer}, entityID(0), inputHandler{ std::make_unique<InputHandler>() }, debugInfo{ true } {}

//template <typename T>
//std::shared_ptr<T> ECSArchitecture::buildEntityAt(const std::string& filename, int col, int row)
//{
//	auto ent = std::make_shared<T>();
//	float x = col * spriteWH * tileScale;
//	float y = row * spriteWH * tileScale;
//	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;
//
//	dynamic_cast<PositionComponent*>(ent->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
//	ent->init(filename, std::make_shared<SimpleSpriteGraphicsComponent>(itemScale));
//
//	return ent;
//}

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