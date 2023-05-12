#include "../../include/core/Command.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"

void PauseCommand::execute(Game& game) {
	game.togglePause();
}