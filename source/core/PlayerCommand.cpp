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
	game.getPlayer()->setAttacking(true);
}
void ShoutCommand::execute(Game& game) {
	if (game.getPlayer()->getWood() >= 0) {
		game.getPlayer()->setShouting(true);
	}
}