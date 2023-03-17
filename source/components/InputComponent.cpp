#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/components/InputComponent.h"

PlayerInputComponent::PlayerInputComponent() :input{ std::make_unique<PlayerInputHandler>() } {}

void PlayerInputComponent::update(Game& game){

	game.getPlayer()->setVelocity(Vector2f(0.0f, 0.0f));
	auto commands = input->handleInput();
	auto it = commands.begin();
	while (it != commands.end()) {
		(*it)->execute(game);
		it++;
	}
}