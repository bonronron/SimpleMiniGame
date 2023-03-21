#include "../../include/core/Command.h"
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
	// <FEEDBACK> This needs to check if the player isAttacking.
	if (!game.getPlayer()->getPlayerStateComp()->isAttacking()) {
		game.getPlayer()->getPlayerStateComp()->setAttacking(true);
	}
}
void ShoutCommand::execute(Game& game) {
	// <FEEDBACK> This needs to check if the player isShouting.
	// And the requirment of having wood is already checked in Player::update(). Remove it from here.
	if (!game.getPlayer()->getPlayerStateComp()->isShouting()) {
		game.getPlayer()->getPlayerStateComp()->setShouting(true);
	}
}