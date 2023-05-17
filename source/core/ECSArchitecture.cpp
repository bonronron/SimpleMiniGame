
#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
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

ECSArchitecture::ECSArchitecture(std::shared_ptr<Game> gamePointer) : game{gamePointer}, entityID(0), inputHandler{ std::make_unique<InputHandler>() }, debugInfo{ true } {}

template <typename T>
std::shared_ptr<T> ECSArchitecture::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	dynamic_cast<PositionComponent*>(ent->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
	ent->init(filename, std::make_shared<SimpleSpriteGraphicsComponent>(itemScale));

	return ent;
}

