#include "../../include/core/Command.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Vector2.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/LogicComponent.h"

void MoveRightCommand::execute(Game& game) {
	game.getPlayer()->getVelocityComp()->setVelocityX(1.0f);
}
void MoveLeftCommand::execute(Game& game) {
	game.getPlayer()->getVelocityComp()->setVelocityX(-1.0f);
}
void MoveUpCommand::execute(Game& game) {
	game.getPlayer()->getVelocityComp()->setVelocityY(-1.0f);
}
void MoveDownCommand::execute(Game& game) {
	game.getPlayer()->getVelocityComp()->setVelocityY(1.0f);
}
void AttackCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getPlayer()->getLogicComp().get());
	if (!playerLogic->isAttacking()) {
		playerLogic->setAttacking(true);
	}
}
void ShoutCommand::execute(Game& game) {
	auto playerLogic = dynamic_cast<PlayerStateComponent*>(game.getPlayer()->getLogicComp().get());
	if (!playerLogic->isShouting()) {
		playerLogic->setShouting(true);
	}
}