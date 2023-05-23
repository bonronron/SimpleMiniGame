#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
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

BigArrayECS::BigArrayECS(Game* game) : ECSArchitecture(game) {}

void BigArrayECS::addEntity(std::shared_ptr<Entity> newEntity) {
	addToBase(newEntity);
}

void BigArrayECS::update(float elapsed) {
	// Updating logic
	updateSystems(elapsed, logicSystems, entities);
	colliderAndDeleteBase();
}