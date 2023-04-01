#include "../../include/utils/Bitmask.h"
#include "../../include/components/Components.h"
#include "../../include/entities/Entity.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/entities/Player.h"
#include "../../include/core/Game.h"
#include "../../include/utils/Vector2.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"

//PlayerInputComponent::PlayerInputComponent() :input{ std::make_shared<PlayerInputHandler>() } {}
//
//void PlayerInputComponent::update(Game& game){
//
//	game.getPlayer()->getVelocityComp()->setVelocity(0.f, 0.f);
//	auto commands = input->handleInput();
//	auto it = commands.begin();
//	while (it != commands.end()) {
//		(*it)->execute(game);
//		it++;
//	}
//}