#include "../../include/core/Command.h"
#include "../../include/core/Game.h"

void MoveRightCommand::execute(Game& game) {
	game.getPlayer()->setVelocityX(1.0f);
}
void MoveLeftCommand::execute(Game& game) {
	game.getPlayer()->setVelocityX(-1.0f);
}
void MoveUpCommand::execute(Game& game) {
	game.getPlayer()->setVelocityY(-1.0f);
}
void MoveDownCommand::execute(Game& game) {
	game.getPlayer()->setVelocityY(1.0f);
}
void AttackCommand::execute(Game& game) {
	// <FEEDBACK> This needs to check if the player isAttacking.
	game.getPlayer()->setAttacking(true);
}
void ShoutCommand::execute(Game& game) {
	// <FEEDBACK> This needs to check if the player isShouting.
	// And the requirment of having wood is already checked in Player::update(). Remove it from here.
	if (game.getPlayer()->getWood() >= 0) {
		game.getPlayer()->setShouting(true);
	}
}