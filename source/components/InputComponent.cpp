//#include "../core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/components/InputComponent.h"

PlayerInputComponent::PlayerInputComponent() :input{ std::make_unique<PlayerInputHandler>() } {}

void PlayerInputComponent::update(Game& game){

	game.getPlayer()->getVelocityComp()->setVelocity(0.f, 0.f);
	auto commands = input->handleInput();
	auto it = commands.begin();
	while (it != commands.end()) {
		(*it)->execute(game);
		it++;
	}
}