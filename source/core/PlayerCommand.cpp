#include "../../include/core/Command.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/systems/Systems.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Vector2.h"
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

void MoveRightCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityX(1.0f);
}
void MoveLeftCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityX(-1.0f);
}
void MoveUpCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityY(-1.0f);
}
void MoveDownCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityY(1.0f);
}
void AttackCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::LOGIC));
	if (!playerLogic->isAttacking()) {
		playerLogic->setAttacking(true);
	}
}
void ShoutCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getECS()->getPlayer()->getComponent(ComponentID::LOGIC));
	if (!playerLogic->isShouting()) {
		playerLogic->setShouting(true);
	}
}