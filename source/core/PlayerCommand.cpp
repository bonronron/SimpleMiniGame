#include "../../include/core/Command.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/utils/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Vector2.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/InputHandler.h"

void MoveRightCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityX(1.0f);
}
void MoveLeftCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityX(-1.0f);
}
void MoveUpCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityY(-1.0f);
}
void MoveDownCommand::execute(Game& game) {
	dynamic_cast<VelocityComponent*>(game.getPlayer()->getComponent(ComponentID::VELOCITY))->setVelocityY(1.0f);
}
void AttackCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getPlayer()->getComponent(ComponentID::LOGIC));
	if (!playerLogic->isAttacking()) {
		playerLogic->setAttacking(true);
	}
}
void ShoutCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getPlayer()->getComponent(ComponentID::LOGIC));
	if (!playerLogic->isShouting()) {
		playerLogic->setShouting(true);
	}
}

void SwapControlsCommand::execute(Game& game) {
	auto inputComponent = dynamic_cast<InputComponent*>(game.getPlayer()->getComponent(ComponentID::INPUT));
	inputComponent->getInputHandler()->swapInputModes();
}