#include "../../include/core/Command.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/Player.h"
#include "../../include/core/Game.h"

void PauseCommand::execute(Game& game) {
	game.togglePause();
}